#include "Particle.h"


const int reedPin = D2;     
const int vccPin  = D3;     

const unsigned long debounce = 1000; 
const float bucketValue = 0.2794;    

// ----------- Global Variables ----------- //
volatile float rainCounter = 0.0;    
volatile unsigned long previousRain = 0; 

void gotRain(); 

void setup() {
    Cellular.off();
    Serial.begin(9600);
    pinMode(vccPin, OUTPUT);
    digitalWrite(vccPin, HIGH);

  
    pinMode(reedPin, INPUT_PULLDOWN);

  
    attachInterrupt(reedPin, gotRain, RISING);

    Serial.println("Rainfall sensor initialized...");
}



void loop() {
    
    static unsigned long lastPrint = 0;

    if (millis() - lastPrint >= 10000) {
        lastPrint = millis();
        Serial.printf("Rainfall so far: %.2f mm\n", rainCounter);
    }
}

void gotRain() {
    unsigned long currentTime = millis();

 
    if (currentTime - previousRain >= debounce) {
        rainCounter += bucketValue;
        previousRain = currentTime;
    }
}