//-------------Adapted from Particle Boron Logic------------------//
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
    Serial.begin(115200);
    Serial1.begin(9600);

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





