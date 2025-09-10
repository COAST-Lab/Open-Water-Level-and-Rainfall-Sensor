//------------ DFRobot rainfall read adapted to Particle Boron--------//

#include "Particle.h"
#include "DFRobot_RainfallSensor.h"

// Pointer for the UART rainfall sensor (???)
DFRobot_RainfallSensor_UART* rainfallSensor;

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);

    delay(1000); 

    Log.info("Starting rainfall sensor setup...");

    
    rainfallSensor = new DFRobot_RainfallSensor_UART(Serial1);

    // Attempt sensor initialization
    while (!rainfallSensor->begin()) {
        Log.info("Rainfall sensor init failed (UART)!");
        delay(3000); 
    }

    Log.info("Rainfall sensor initialized successfully!");
    Log.info("Firmware version: %s", rainfallSensor->getFirmwareVersion().c_str());

    delay(1000);
}

void loop() {

    // Log.info("Rainfall total: %.2f mm", rainfallSensor->getRainfall());
    // Log.info("Sensor working time: %.2f h", rainfallSensor->getSensorWorkingTime());
    // Log.info("Raw bucket counts: %lu", rainfallSensor->getRawData());
    // Log.info("-----------------------------");

    // delay(1000);

  //Get the sensor working time, unit: hour
  Log.info("Sensor WorkingTime:\t");
  Log.info("%lu H", rainfallSensor->getSensorWorkingTime());
  //Get the accumulated rainfall during the sensor working time
  Log.info("Rainfall:\t");
  Log.info("%.2f mm", rainfallSensor->getRainfall());
  //Get the accumulated rainfall within 1 hour of the system (function parameter optional 1-24)
  Log.info("1 Hour Rainfall:\t");
  Log.info("%.2f mm", rainfallSensor->getRainfall(1));
  //Get the raw data, the number of tipping buckets for rainfall, unit: times
  Log.info("rainfall raw:\t");
  Log.info("%lu", rainfallSensor->getRawData());
  delay(1000);
}