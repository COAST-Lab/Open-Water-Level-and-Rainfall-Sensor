/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"

// DFR's library for the rainfall sensor
#include "DFRobot_RainfallSensor.h"

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(SEMI_AUTOMATIC);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

//------------ DFRobot rainfall read adapted to Particle Boron--------//

DFRobot_RainfallSensor_I2C Sensor(&Wire);

void setup() {
    Cellular.off(); // Disable cellular modem to save power

    // Serial1.begin(9600);  // UART to sensor
    //Serial.begin(115200); // USB debugging
    delay(5000);

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
