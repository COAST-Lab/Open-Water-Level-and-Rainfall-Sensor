// //------------ DFRobot rainfall read adapted to Particle Boron--------//

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