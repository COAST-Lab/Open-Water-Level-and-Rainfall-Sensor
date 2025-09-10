#include "Particle.h"

// Rainfall sensor via digital tipping bucket
const int RAIN_PIN = D2;        // digital pin connected to tipping bucket
volatile uint32_t rainfall_tips = 0;
float rainfall_mm = 0.0;
const float MM_PER_TIP = 0.2794; // mm per tip

// ISR triggered on tipping bucket
void rainfallISR() {
    rainfall_tips++;
}

void setup() {
    Serial.begin(9600);

    // LED pin
   // pinMode(led, OUTPUT);

    // Rainfall sensor ISR
    pinMode(RAIN_PIN, INPUT_PULLUP);
    attachInterrupt(RAIN_PIN, rainfallISR, FALLING);

    Log.info("Setup complete");
}

void loop() {
    // Compute total rainfall
    rainfall_mm = rainfall_tips * MM_PER_TIP;

    // Log rainfall
    Log.info("Rainfall: %.2f mm", rainfall_mm);
    
    delay(1000);
}




//------------ DFRobot rainfall read adapted to Particle Boron--------//

// #include "Particle.h"
// #include "DFRobot_RainfallSensor.h"

// // Pointer for the UART rainfall sensor (???)
// DFRobot_RainfallSensor_UART* rainfallSensor;

// void setup() {
//     Serial1.begin(9600);
//     delay(1000); 

//     Log.info("Starting rainfall sensor setup...");

    
//     rainfallSensor = new DFRobot_RainfallSensor_UART(Serial1);

//     // Attempt sensor initialization
//     while (!rainfallSensor->begin()) {
//         Log.info("Rainfall sensor init failed (UART)!");
//         delay(3000); 
//     }

//     Log.info("Rainfall sensor initialized successfully!");
//     Log.info("Firmware version: %s", rainfallSensor->getFirmwareVersion().c_str());

//     delay(1000);
// }

// void loop() {

//     Log.info("Rainfall total: %.2f mm", rainfallSensor->getRainfall());
//     Log.info("Sensor working time: %.2f h", rainfallSensor->getSensorWorkingTime());
//     Log.info("Raw bucket counts: %lu", rainfallSensor->getRawData());
//     Log.info("-----------------------------");

//     delay(1000);
// }
