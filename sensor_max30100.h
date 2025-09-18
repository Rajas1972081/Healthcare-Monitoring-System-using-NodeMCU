// sensor_max30100.h
// Header file for the MAX30100 pulse oximeter sensor

#ifndef SENSOR_MAX30100_H
#define SENSOR_MAX30100_H

#include <Wire.h>

class MAX30100 {
public:
    MAX30100();
    bool begin();
    int getHeartRate();
    float getSpO2();

private:
    void writeRegister(uint8_t reg, uint8_t value);
    uint8_t readRegister(uint8_t reg);
    
};

#endif