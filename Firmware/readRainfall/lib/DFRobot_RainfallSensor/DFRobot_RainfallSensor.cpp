/#include "DFRobot_RainfallSensor.h"

DFRobot_RainfallSensor_UART::DFRobot_RainfallSensor_UART(Stream &serial)
  : _serial(serial) {}

bool DFRobot_RainfallSensor_UART::begin() {
  // If your sensor needs init commands, send here.
  return true;
}

String DFRobot_RainfallSensor_UART::getFirmwareVersion() {
  // Example: query sensor over UART
  _serial.println("AT+VER?");
  delay(50);
  String response = "";
  while (_serial.available()) {
    response += (char)_serial.read();
  }
  return response.length() ? response : "Unknown";
}

float DFRobot_RainfallSensor_UART::getRainfall() {
  // TODO: implement proper protocol for your sensor
  return 0.0f;
}

float DFRobot_RainfallSensor_UART::getRainfall(uint8_t hour) {
  // TODO: hourly history if supported
  return 0.0f;
}

uint32_t DFRobot_RainfallSensor_UART::getRawData() {
  // TODO: raw counter from sensor
  return 0;
}

uint8_t DFRobot_RainfallSensor_UART::setRainAccumulatedValue(float accumulatedValue) {
  // TODO: send accumulated value reset if supported
  return 1;
}

float DFRobot_RainfallSensor_UART::getSensorWorkingTime() {
  // TODO: query uptime if supported
  return 0.0f;
}

uint16_t DFRobot_RainfallSensor_UART::readRegister(uint16_t reg) {
  // Placeholder – implement if your sensor supports reg read over UART
  return 0;
}

uint16_t DFRobot_RainfallSensor_UART::writeRegister(uint16_t reg, uint16_t data) {
  // Placeholder – implement if your sensor supports reg write over UART
  return 0;
}
float DFRobot_RainfallSensor::getRainfall(void)
{
  uint32_t rainfall=0;
  if(_mode == IIC_MODE){
    uint8_t buff[4]={0};
    readRegister( I2C_REG_CUMULATIVE_RAINFALL, (void*)buff, 4 );
    rainfall = buff[0] | ( ( (uint32_t)buff[1] ) << 8 ) | ( ( (uint32_t)buff[2] ) << 16 ) | ( ( (uint32_t)buff[3]) << 24 );
  }else{
    rainfall = readRegister( eInputRegCumulativeRainFallHSEN0575 );
    rainfall = rainfall << 16 | readRegister( eInputRegCumulativeRainFallLSEN0575 );
  }
  return rainfall / 10000.0;
}

float DFRobot_RainfallSensor::getRainfall(uint8_t hour)
{
  uint32_t rainfall = 0 ;
  if(_mode == IIC_MODE){
    writeRegister(I2C_REG_RAIN_HOUR, (void*)&hour, 1);
    uint8_t buff[4] = {0};
    if( readRegister(I2C_REG_TIME_RAINFALL, (void*)buff, 4 ) == 0 ){
      return -1;
    }
    rainfall = buff[0] | ( ( (uint32_t)buff[1] ) << 8 ) | ( ( (uint32_t)buff[2]) << 16 ) | ( ( (uint32_t)buff[3] ) << 24 );
  }else{
    writeRegister( eHoldingRegRainHourSEN0575, hour );
    rainfall = readRegister( eInputRegTimeRainFallHSEN0575 );
    rainfall = rainfall << 16 | readRegister( eInputRegTimeRainFallLSEN0575 );
  }
  return rainfall / 10000.0;
}

uint32_t DFRobot_RainfallSensor::getRawData(void)
{
  uint32_t rawdata = 0;
  if(_mode == IIC_MODE){
    uint8_t buff[4] = { 0 };
    readRegister( I2C_REG_RAW_DATA, (void*)buff, 4 );
    rawdata = buff[0] | ( ( (uint32_t)buff[1] ) << 8 ) | ( ( (uint32_t)buff[2] ) << 16 ) | ( ( (uint32_t)buff[3]) << 24 );
  }else{
    rawdata = readRegister( eInputRegRawDataHSEN0575 );
    rawdata = rawdata << 16 | readRegister( eInputRegRawDataLSEN0575 );
  }
  return rawdata;
}

uint8_t DFRobot_RainfallSensor::setRainAccumulatedValue(float value)
{
  uint8_t ret = 0;
  uint16_t data = value * 10000;
  if(_mode == IIC_MODE){
    uint8_t buff[2] = { 0 };
    buff[0] = ( data & 0xFF );
    buff[1] = ( data >> 8 );
    ret = writeRegister( I2C_REG_BASE_RAINFALL, (void*)buff, 2 );
  }else{
    ret = writeRegister( eHoldingRegBaseRainFallSEN0575, data );
  }
  return ret;
}

float DFRobot_RainfallSensor::getSensorWorkingTime(void)
{
  uint16_t WorkingTime = 0 ;
  if(_mode == IIC_MODE){
    uint8_t buff[2] = { 0 };
    readRegister( I2C_REG_SYS_TIME, (void*)buff, 2 );
    WorkingTime = buff[0] | ( ( (uint32_t)buff[1] ) << 8 );
  }else{
    WorkingTime = readRegister( eInputRegSysWorkingTimeSEN0575 );
  }
  return WorkingTime / 60.0;
}

DFRobot_RainfallSensor_UART::DFRobot_RainfallSensor_UART(Stream *s)
:DFRobot_RainfallSensor(UART_MODE),DFRobot_RTU(s)
{
  _deviceAddr = 0xC0;
}
bool DFRobot_RainfallSensor_UART::begin(void)
{
  
  return DFRobot_RainfallSensor::begin();
}
uint16_t DFRobot_RainfallSensor_UART::readRegister(uint16_t reg)
{
  setTimeoutTimeMs(1000);
  return readInputRegister( (uint8_t)_deviceAddr, (uint16_t)reg );
}

uint16_t DFRobot_RainfallSensor_UART::writeRegister(uint16_t reg,uint16_t data)
{
  uint16_t ret=writeHoldingRegister( _deviceAddr, reg, data );
  delay(30);
  return ret;
}

DFRobot_RainfallSensor_I2C::DFRobot_RainfallSensor_I2C(TwoWire *pWire)
:DFRobot_RainfallSensor(IIC_MODE),_pWire(pWire)
{
  _deviceAddr = 0x1D;
}
bool DFRobot_RainfallSensor_I2C::begin(void)
{
  _pWire->begin();
  return DFRobot_RainfallSensor::begin();
}

uint8_t DFRobot_RainfallSensor_I2C::writeRegister(uint8_t reg, void* pBuf, size_t size)
{
  if(pBuf == NULL){
	  return 1;
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(reg);
  for( uint16_t i = 0; i < size; i++ ){
    _pWire->write(_pBuf[i]);
  }
  _pWire->endTransmission();
  delay(100);
  return 0;
}

uint8_t DFRobot_RainfallSensor_I2C::readRegister(uint8_t reg, void* pBuf, size_t size)
{
  if(pBuf == NULL){
    return 0;
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(reg);
  if(_pWire->endTransmission() != 0 ){
    return 0;
  }
  _pWire->requestFrom(_deviceAddr, (uint8_t)size );
  for( uint8_t i=0; i<size; i++ ){
    _pBuf[i] = _pWire->read();
  }
  return size;
}
