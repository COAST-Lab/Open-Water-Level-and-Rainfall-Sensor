#include "Particle.h"
#include "DFRobot_RainfallSensor.h" // Make sure this matches your library file name

DFRobot_RainfallSensor_UART sensor(D9);  // RX pin, TX pin

void setup() {
    //Serial.begin(115200);  // USB serial for debugging
    Serial1.begin(9600);   // Sensor UART baud rate (check your datasheet)

    delay(2000); // give serial monitor time to connect

    // Try to initialize sensor
    while (sensor.begin()) {
        Serial.println("Sensor initialize failed!!");
        delay(1000);
    }
    Serial.println("Sensor initialize success!!");

    // Print sensor info
    Serial.print("Version: ");
    Serial.println(sensor.get_firmware_version());

    Serial.printf("VID: 0x%X\n", sensor.vid);
    Serial.printf("PID: 0x%X\n", sensor.pid);

    // Optional: set tipping bucket accumulated value (mm per tip)
    // sensor.set_rain_accumulated_value(0.2794);
}

void loop() {
    // Get operating time (hours)
    float workingTime = sensor.get_sensor_working_time();
    
    // Get rainfall (mm)
    float rainfall = sensor.get_rainfall();

    // Get rainfall in the last hour (mm)
    float oneHourRainfall = sensor.get_rainfall_time(1);

    // Get raw tipping bucket count
    uint16_t rainfallRaw = sensor.get_raw_data();

    // Print results
    Serial.printf("Working time: %.2f H\n", workingTime);
    Serial.printf("Rainfall: %.2f mm\n", rainfall);
    Serial.printf("One-hour rainfall: %.2f mm\n", oneHourRainfall);
    Serial.printf("Raw tipping count: %u\n", rainfallRaw);
    Serial.println("------------------------------------------------");

    delay(1000); // wait 1 second
}
