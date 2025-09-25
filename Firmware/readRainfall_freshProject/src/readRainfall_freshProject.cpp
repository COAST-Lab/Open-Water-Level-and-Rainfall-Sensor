#include "Particle.h"

// Pin where reed switch is connected
#define RAIN_PIN D0

// Counter for tips
volatile unsigned long tipCount = 0;

// For debouncing
volatile unsigned long lastTipTime = 0;
const unsigned long debounceDelay = 1000; // 1 second

void tipISR() {
    unsigned long now = millis();
    if (now - lastTipTime > debounceDelay) {
        tipCount++;
        lastTipTime = now;
    }
}

void setup() {
    pinMode(RAIN_PIN, INPUT_PULLUP);
    attachInterrupt(RAIN_PIN, tipISR, FALLING);
    Serial.begin(9600);
}

void loop() {
    // Copy volatile value to local var for safe use
    unsigned long tips;
    noInterrupts();
    tips = tipCount;
    interrupts();

    // Each tip = X mm rain (check your sensor’s calibration)
    float mmPerTip = 0.2;
    float rainfall = tips * mmPerTip;

    Serial.print("Tips: ");
    Serial.print(tips);
    Serial.print("  Rainfall (mm): ");
    Serial.println(rainfall);

    delay(2000);
}
