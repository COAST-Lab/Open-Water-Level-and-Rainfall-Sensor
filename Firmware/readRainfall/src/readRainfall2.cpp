//------------ DFRobot rainfall read adapted to Particle Boron--------//

#include "Particle.h"
//#include "Arduino.h"
#include "DFRobot_RainfallSensor.h"


DFRobot_RainfallSensor_I2C Sensor(&Wire);

void setup() {
    Serial1.begin(9600);  // UART to sensor
    //Serial.begin(115200); // USB debugging
    delay(1000);

    // Initialize sensor
    while (!Sensor.begin()) {
        Log.info("Sensor init err!!!");
        delay(1000);
    }

    // Log.info("Firmware Version:\t");
    // Log.info(Sensor.getFirmwareVersion());
}

void loop() {
    // Log via Particle console
    Log.info("Sensor WorkingTime: %.2f H", Sensor.getSensorWorkingTime());
    Log.info("Rainfall: %.2f mm", Sensor.getRainfall());
    Log.info("1 Hour Rainfall: %.2f mm", Sensor.getRainfall(1));
    Log.info("Raw Tipping Counts: %lu", Sensor.getRawData());

    // Also print via USB for debugging
    Log.info("Sensor WorkingTime: %.2f H", Sensor.getSensorWorkingTime());
    Log.info("Rainfall: %.2f mm", Sensor.getRainfall());
    Log.info("1 Hour Rainfall: %.2f mm", Sensor.getRainfall(1));
    Log.info("Raw Tipping Counts: %lu", Sensor.getRawData());

    delay(1000);
}




