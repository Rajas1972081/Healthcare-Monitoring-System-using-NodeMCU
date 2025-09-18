// IoT_Patient_Monitor.ino
// Main sketch for Healthcare Monitoring System with NodeMCU

#include <BlynkSimpleEsp8266.h> 
#include "sensor_max30100.h"    
#include "sensor_ds18b20.h"     


#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN_HERE" 
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "WiFi_SSID";      
char pass[] = "WiFi_Password"; 

// Sensor objects
MAX30100 sensorHR;
DS18B20 sensorTemp(D4); // DS18B20 data pin connected to NodeMCU's D4

// Timing for sensor readings
unsigned long previousMillis = 0;
const long interval = 2000; // Read sensors every 2 seconds

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("Initializing Patient Monitoring System...");

  // Initialize sensors
  if(sensorHR.begin()) {
    Serial.println("MAX30100 sensor initialized");
  } else {
    Serial.println("MAX30100 sensor failed!");
  }
  
  if(sensorTemp.begin()) {
    Serial.println("DS18B20 sensor initialized");
  } else {
    Serial.println("DS18B20 sensor failed!");
  }

  // Connect to Blynk
  Blynk.begin(auth, ssid, pass);
  Serial.println("Connecting to Blynk...");
}

void loop() {
  Blynk.run(); // Maintain Blynk connection

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Read sensor data
    int heartRate = sensorHR.getHeartRate();
    float spO2 = sensorHR.getSpO2();
    float temperature = sensorTemp.getTemperatureC();

    // Display values on Serial Monitor
    Serial.print("HR: "); Serial.print(heartRate); Serial.print(" bpm");
    Serial.print(" | SpO2: "); Serial.print(spO2); Serial.print("%");
    Serial.print(" | Temp: "); Serial.print(temperature); Serial.println(" °C");

    // Send data to Blynk app (use Virtual Pins V1, V2, V3)
    Blynk.virtualWrite(V1, heartRate);
    Blynk.virtualWrite(V2, spO2);
    Blynk.virtualWrite(V3, temperature);

    // Check for critical values and trigger Blynk alerts
    if (heartRate > 120) {
      Blynk.logEvent("high_heart_rate", "Warning: High Heart Rate detected!");
    }
    if (temperature > 38.5) {
      Blynk.logEvent("high_temperature", "Warning: Patient has a fever!");
    }
  }
}