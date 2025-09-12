#pragma once
#include "Particle.h"

class DFRobot_RainfallSensor {
  public:
    virtual bool begin() { return false; }
    virtual String getFirmwareVersion() { return "N/A"; }
    virtual float getRainfall() { return 0.0f; }
    virtual float getRainfall(uint8_t hour) { return 0.0f; }
    virtual uint32_t getRawData() { return 0; }
    virtual uint8_t setRainAccumulatedValue(float accumulatedValue = 0.2794f) { return 0; }
    virtual float getSensorWorkingTime() { return 0.0f; }
};

class DFRobot_RainfallSensor_UART : public DFRobot_RainfallSensor {
  public:
    explicit DFRobot_RainfallSensor_UART(Stream &serial);
    bool begin() override;
    String getFirmwareVersion() override;
    float getRainfall() override;
    float getRainfall(uint8_t hour) override;
    uint32_t getRawData() override;
    uint8_t setRainAccumulatedValue(float accumulatedValue = 0.2794f) override;
    float getSensorWorkingTime() override;

  private:
    Stream &_serial;
    uint16_t readRegister(uint16_t reg);
    uint16_t writeRegister(uint16_t reg, uint16_t data);
};
