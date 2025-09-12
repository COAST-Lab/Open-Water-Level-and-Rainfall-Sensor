#ifndef DFRobot_RAINFALLSENSOR_H
#define DFRobot_RAINFALLSENSOR_H

#include "Particle.h"
#include <stdint.h>
#include <Wire.h>

// Base class
class DFRobot_RainfallSensor {
public:
    DFRobot_RainfallSensor() {}

    // Pure virtual functions to be implemented by subclasses
    virtual float getRainfall() = 0;
    virtual float getRainfall(uint8_t hour) = 0;
    virtual uint32_t getRawData() = 0;
    virtual uint8_t setRainAccumulatedValue(float accumulatedValue = 0.2794f) = 0;
    virtual float getSensorWorkingTime() = 0;

    virtual bool begin() { return true; }  // optional default
};

// UART subclass
class DFRobot_RainfallSensor_UART : public DFRobot_RainfallSensor {
public:
    DFRobot_RainfallSensor_UART(Stream &serial);

    bool begin() override;
    float getRainfall() override;
    float getRainfall(uint8_t hour) override;
    uint32_t getRawData() override;
    uint8_t setRainAccumulatedValue(float accumulatedValue = 0.2794f) override;
    float getSensorWorkingTime() override;

    uint16_t readRegister(uint16_t reg);
    uint16_t writeRegister(uint16_t reg, uint16_t data);

private:
    Stream* _serial;
};

// I2C subclass
class DFRobot_RainfallSensor_I2C : public DFRobot_RainfallSensor {
public:
    DFRobot_RainfallSensor_I2C(TwoWire *pWire = &Wire, uint8_t deviceAddr = 0x08);

    bool begin() override;
    float getRainfall() override;
    float getRainfall(uint8_t hour) override;
    uint32_t getRawData() override;
    uint8_t setRainAccumulatedValue(float accumulatedValue = 0.2794f) override;
    float getSensorWorkingTime() override;

    uint8_t writeRegister(uint8_t reg, void* pBuf, size_t size);
    uint8_t readRegister(uint8_t reg, void* pBuf, size_t size);

private:
    TwoWire* _pWire;
    uint8_t _deviceAddr;
};

#endif // DFRobot_RAINFALLSENSOR_H

