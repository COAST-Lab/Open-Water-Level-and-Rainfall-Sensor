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

Log.info("Establishing UART connection to rainfall sensor");//Trying to see where code stops

// UART version (use Boron hardware serial pins)
DFRobot_RainfallSensor_UART rainfallSensor(Serial1);

Log.info("About to enter setup");

void setup() {
    Serial1.begin(9600);
    delay(1000);

    Log.info("About to initialize rainfall sensor");

    while (!rainfallSensor.begin()) {
        Log.info("Rainfall sensor init failed (UART)!");
        delay(3000);
    }
    Log.info("Rainfall sensor (UART) init success!");

    Log.info("Firmware version: %s\n", rainfallSensor.getFirmwareVersion().c_str());
    // Log.info("VID: 0x%X\n", rainfallSensor.vid);
    // Log.info("PID: 0x%X\n", rainfallSensor.pid);
    delay(1000);
}

void loop() {
    Log.info("Working time: %.2f h\n", rainfallSensor.getSensorWorkingTime());
    Log.info("Rainfall total: %.2f mm\n", rainfallSensor.getRainfall());
    //Log.info("1-hour rainfall: %.2f mm\n", rainfallSensor.getRainfallTime(1));
    Log.info("Raw bucket counts: %lu\n", rainfallSensor.getRawData());
    Log.info("-----------------------------");
    delay(1000);
}
