#include "DFRobot_RainfallSensor.h"

//#define MODE_UART
#ifdef MODE_UART //UART communication

   #include "SoftwareSerial.h"
   SoftwareSerial mySerial(/*rx =*/10, /*tx =*/11);
   DFRobot_RainfallSensor_UART Sensor(/*Stream *=*/&mySerial);

#else //I2C communication
  DFRobot_RainfallSensor_I2C Sensor(&Wire);
#endif

void setup(void)
{
#ifdef MODE_UART
    mySerial.begin(9600);
#endif 
  Serial.begin(115200);

  delay(1000);
  while(!Sensor.begin()){
    Serial.println("Sensor init err!!!");
    delay(1000);
  }
  Serial.print("vid:\t");
  Serial.println(Sensor.vid,HEX);
  Serial.print("pid:\t");
  Serial.println(Sensor.pid,HEX);
  Serial.print("Version:\t");
  Serial.println(Sensor.getFirmwareVersion());
  //Set the rain accumulated value, unit: mm
  //Sensor.setRainAccumulatedValue(0.2794);
}

void loop()
{
  //Get the sensor working time, unit: hour
  Serial.print("Sensor WorkingTime:\t");
  Serial.print(Sensor.getSensorWorkingTime());
  Serial.println(" H");
  //Get the accumulated rainfall during the sensor working time
  Serial.print("Rainfall:\t");
  Serial.println(Sensor.getRainfall());
  //Get the accumulated rainfall within 1 hour of the system (function parameter optional 1-24)
  Serial.print("1 Hour Rainfall:\t");
  Serial.print(Sensor.getRainfall(1));
  Serial.println(" mm");
  //Get the raw data, the number of tipping buckets for rainfall, unit: times
  Serial.print("rainfall raw:\t");
  Serial.println(Sensor.getRawData());
  delay(1000);
}