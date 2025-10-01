//------------ DFRobot rainfall read adapted to Particle Boron--------//

#include "Particle.h"
#include "DFRobot_RainfallSensor.h"

SYSTEM_MODE(SEMI_AUTOMATIC);

DFRobot_RainfallSensor_I2C Sensor(&Wire);

SerialLogHandler logHandler(LOG_LEVEL_INFO);

void setup() {
    Cellular.off();
    Serial1.begin(9600);  // UART to sensor
    delay(3000);

    Log.info("anything?");

    // Initialize sensor
    while (!Sensor.begin()) {
        Log.info("Sensor init err!!!");
        delay(1000);
    }

    Log.info("Firmware Version:\t");
    Log.info(Sensor.getFirmwareVersion());
}

void loop() {
    // Log via Particle console
    Log.info("Sensor WorkingTime: %.2f H", Sensor.getSensorWorkingTime());
    Log.info("Rainfall: %.2f mm", Sensor.getRainfall());
    Log.info("1 Hour Rainfall: %.2f mm", Sensor.getRainfall(1));
    Log.info("Raw Tipping Counts: %lu", Sensor.getRawData());

    Log.info("looping");
    delay(1000);
}