// HRXL-MaxSonar-WR ADC demo
// Prints raw ADC counts only

const int sonarPin = A0;

void setup() {
    Serial.begin(9600);
    waitFor(Serial.isConnected, 5000);

    pinMode(sonarPin, INPUT);
}

void loop() {
    int adcValue = analogRead(sonarPin);  // 0–4095 on Boron

    Serial.print("ADC Counts: ");
    Serial.println(adcValue);

    // Optional: publish for logging
    Particle.publish("sonar_ADC", String(adcValue), PRIVATE);

    delay(1000);
}