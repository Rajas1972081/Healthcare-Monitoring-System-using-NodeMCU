// sensor_ds18b20.h
// Header file for the DS18B20 temperature sensor

#ifndef SENSOR_DS18B20_H
#define SENSOR_DS18B20_H

#include <OneWire.h>
#include <DallasTemperature.h>

class DS18B20 {
public:
    DS18B20(uint8_t pin);
    bool begin();
    float getTemperatureC();

private:
    uint8_t _pin;
    OneWire _oneWire;
    DallasTemperature _sensors;
};

#endif