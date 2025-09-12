#include "DFRobot_RainfallSensor.h"

// -------------------- UART --------------------
DFRobot_RainfallSensor_UART::DFRobot_RainfallSensor_UART(Stream &serial) {
    _serial = &serial;
}

bool DFRobot_RainfallSensor_UART::begin() {
    // Initialize UART if needed
    return true;
}

float DFRobot_RainfallSensor_UART::getRainfall() {
    // Example: replace with real sensor code
    return 0.0f;
}

float DFRobot_RainfallSensor_UART::getRainfall(uint8_t hour) {
    return 0.0f;
}

uint32_t DFRobot_RainfallSensor_UART::getRawData() {
    return 0;
}

uint8_t DFRobot_RainfallSensor_UART::setRainAccumulatedValue(float accumulatedValue) {
    return 0;
}

float DFRobot_RainfallSensor_UART::getSensorWorkingTime() {
    return 0.0f;
}

uint16_t DFRobot_RainfallSensor_UART::readRegister(uint16_t reg) {
    return 0;
}

uint16_t DFRobot_RainfallSensor_UART::writeRegister(uint16_t reg, uint16_t data) {
    return 0;
}

// -------------------- I2C --------------------
DFRobot_RainfallSensor_I2C::DFRobot_RainfallSensor_I2C(TwoWire *pWire, uint8_t deviceAddr) {
    _pWire = pWire;
    _deviceAddr = deviceAddr;
}

bool DFRobot_RainfallSensor_I2C::begin() {
    if (_pWire) _pWire->begin();
    return true;
}

float DFRobot_RainfallSensor_I2C::getRainfall() {
    return 0.0f;
}

float DFRobot_RainfallSensor_I2C::getRainfall(uint8_t hour) {
    return 0.0f;
}

uint32_t DFRobot_RainfallSensor_I2C::getRawData() {
    return 0;
}

uint8_t DFRobot_RainfallSensor_I2C::setRainAccumulatedValue(float accumulatedValue) {
    return 0;
}

float DFRobot_RainfallSensor_I2C::getSensorWorkingTime() {
    return 0.0f;
}

uint8_t DFRobot_RainfallSensor_I2C::writeRegister(uint8_t reg, void* pBuf, size_t size) {
    if (!_pWire) return 0;
    _pWire->beginTransmission(_deviceAddr);
    _pWire->write(reg);
    _pWire->write((uint8_t*)pBuf, size);
    return _pWire->endTransmission();
}

uint8_t DFRobot_RainfallSensor_I2C::readRegister(uint8_t reg, void* pBuf, size_t size) {
    if (!_pWire) return 0;
    _pWire->beginTransmission(_deviceAddr);
    _pWire->write(reg);
    _pWire->endTransmission(false);
    _pWire->requestFrom(_deviceAddr, (uint8_t)size);
    for (size_t i = 0; i < size; i++) {
        ((uint8_t*)pBuf)[i] = _pWire->read();
    }
    return size;
}
