//--------------------Creation from OWL data + DF Robot functions-----

// #include "Particle.h"
// #include "SdFat.h"

// //------------------Rainfall Sensor via digital tipping bucket
// const int RAIN_PIN = RX;        // digital pin connected to tipping bucket
// volatile uint32_t rainfall_tips = 0;
// float rainfall_mm = 0.0;
// const float MM_PER_TIP = 0.2794; // mm per tip

// void rainfallISR() {
//     rainfall_tips++;

//     delay (3000);

//     rainfall_mm = rainfall_tips * MM_PER_TIP;
// }

// void setup() {
//     Serial.begin(9600);
    
//     // LED pin
//     pinMode(led, OUTPUT);

//     // Rainfall sensor ISR
//     pinMode(RAIN_PIN, INPUT_PULLUP);
//     //attachInterrupt(RAIN_PIN, rainfallISR, FALLING);
// }

// Log.info(rainfall_mm);



//------------ DFRobot rainfall read adapted to Particle Boron--------//

#include "Particle.h"
#include "DFRobot_RainfallSensor.h"

// Pointer for the UART rainfall sensor
DFRobot_RainfallSensor_UART* rainfallSensor;

void setup() {
    // Start Serial1 for UART communication with the sensor
    Serial1.begin(9600);
    delay(1000); // allow Serial1 to stabilize

    Log.info("Starting rainfall sensor setup...");

    // Initialize the sensor object after Serial1 is ready
    rainfallSensor = new DFRobot_RainfallSensor_UART(Serial1);

    // Attempt sensor initialization
    while (!rainfallSensor->begin()) {
        Log.info("Rainfall sensor init failed (UART)!");
        delay(3000); // wait and retry
    }

    Log.info("Rainfall sensor initialized successfully!");
    Log.info("Firmware version: %s", rainfallSensor->getFirmwareVersion().c_str());

    delay(1000);
}

void loop() {

    // Read and log sensor data
    Log.info("Rainfall total: %.2f mm", rainfallSensor->getRainfall());
    Log.info("Sensor working time: %.2f h", rainfallSensor->getSensorWorkingTime());
    Log.info("Raw bucket counts: %lu", rainfallSensor->getRawData());
    Log.info("-----------------------------");

    delay(1000);
}
