#include "Particle.h"

// Pin where reed switch is connected
#define RAIN_PIN D0

// Counter for tips
// volatile unsigned long tipCount = 0;

// // For debouncing
// volatile unsigned long lastTipTime = 0;
// const unsigned long debounceDelay = 1000; // 1 second

// void tipISR() {
//     unsigned long now = millis();
//     if (now - lastTipTime > debounceDelay) {
//         tipCount++;
//         lastTipTime = now;
//     }
// }

// void setup() {
//     pinMode(RAIN_PIN, INPUT_PULLUP);
//     attachInterrupt(RAIN_PIN, tipISR, FALLING);
//     Serial.begin(9600);
// }

// void loop() {
//     // Copy volatile value to local var for safe use
//     unsigned long tips;
//     noInterrupts();
//     tips = tipCount;
//     interrupts();

//     // Each tip = X mm rain (check your sensor’s calibration)
//     float mmPerTip = 0.2;
//     float rainfall = tips * mmPerTip;

//     Serial.print("Tips: ");
//     Serial.print(tips);
//     Serial.print("  Rainfall (mm): ");
//     Serial.println(rainfall);

//     delay(2000);
// }


//    Connect Reed Switch to D2 (0V) and D3 (3.3V).  Use a current limiting resistor
// Declare variables used in gotRain()
// Include Particle Device OS APIs
//#include "Particle.h"

// ----------- User Configuration ----------- //
const int reedPin = D2;     // Reed switch connected to D2
const int vccPin  = D3;     // Pin to supply 3.3V to the sensor

// Debounce and tipping bucket calibration
const unsigned long debounce = 1000; // ms (1 second to avoid double counts)
const float bucketValue = 0.2794;    // mm per tip (adjust for your tipping bucket)

// ----------- Global Variables ----------- //
volatile float rainCounter = 0.0;    // Stores rainfall total
volatile unsigned long previousRain = 0; // For debounce

// ----------- Function Prototypes ----------- //
//void gotRain(); // ISR for reed switch


// ----------- Setup ----------- //
void setup() {
    Serial.begin(9600);

    // Power the sensor from D3
    pinMode(vccPin, OUTPUT);
    digitalWrite(vccPin, HIGH);

    // Set up reed switch input with internal pulldown
    pinMode(reedPin, INPUT_PULLDOWN);

    // Attach interrupt on reed switch (rising edge = bucket tip)
    attachInterrupt(reedPin, gotRain, RISING);

    Serial.println("Rainfall sensor initialized...");
}


// ----------- Main Loop ----------- //
void loop() {
    // Just print the current rainfall value every 10 seconds
    static unsigned long lastPrint = 0;

    if (millis() - lastPrint >= 10000) {
        lastPrint = millis();
        Serial.printf("Rainfall so far: %.2f mm\n", rainCounter);
    }
}


// ----------- Interrupt Service Routine ----------- //
void gotRain() {
    unsigned long currentTime = millis();

    // Debounce so a single tip doesn’t get counted multiple times
    if (currentTime - previousRain >= debounce) {
        rainCounter += bucketValue;
        previousRain = currentTime;
    }
}