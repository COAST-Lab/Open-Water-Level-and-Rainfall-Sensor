//------------ DFRobot rainfall read adapted to Particle Boron--------//

#include "Particle.h"
#include "DFRobot_RainfallSensor.h"

DFRobot_RainfallSensor_UART Sensor(Serial1);  // Pass Serial1 by reference, not pointer


void setup() {
    Log.info("Setup started");
    Serial1.begin(9600);

    while(!Sensor.begin()) {
        Log.error("Sensor init err!!!");
        delay(1000);
    }

    Log.info("Version:\t");
    Log.info(Sensor.getFirmwareVersion());
}

void loop() {

    Log.info("Sensor WorkingTime: %lu H", Sensor.getSensorWorkingTime());
    Log.info("Rainfall: %.2f mm", Sensor.getRainfall());
    Log.info("1 Hour Rainfall: %.2f mm", Sensor.getRainfall(1));
    Log.info("Raw Tipping Counts: %lu", Sensor.getRawData());

    delay(1000);
}


