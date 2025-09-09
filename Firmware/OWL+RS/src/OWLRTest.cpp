/******************************************************/
//       OWLRTest.cpp - Boron Compatible             //
/******************************************************/

#include "Particle.h"
#include "SdFat.h"

//------------------SD SPI Configuration Details--------------------------------
const int SD_CHIP_SELECT = D5;
SdFat sd;

//------------------LED Setup
int led = D7; // blink to let us know you're alive
bool led_state = HIGH; // starting state

//------------------Maxbotix sensor
float filterArray[200]; // array to store data samples from sensor
float distance_unconverted; // store the distance from sensor
float range_cm;
long real_time;
int millis_now;

//------------------State variables
enum State {
  DATALOG_STATE,
  PUBLISH_STATE,
  SLEEP_STATE
};
State state = DATALOG_STATE;

// Define whether (1) or not (0) to publish
#define PUBLISHING 0

unsigned long stateTime = 0;
char data[120];

//------------------Battery
FuelGauge batteryMonitor;

//------------------Rainfall Sensor via digital tipping bucket
const int RAIN_PIN = RX;        // digital pin connected to tipping bucket
volatile uint32_t rainfall_tips = 0;
float rainfall_mm = 0.0;
const float MM_PER_TIP = 0.2794; // mm per tip

void rainfallISR() {
    rainfall_tips++;

    delay (3000);

    rainfall_mm = rainfall_tips * MM_PER_TIP;
}

// Various timing constants
const unsigned long MAX_TIME_TO_PUBLISH_MS = 60000; // 1 min
const unsigned long TIME_AFTER_PUBLISH_MS = 4000; 
const unsigned long SECONDS_BETWEEN_MEASUREMENTS = 120; 

const char * eventName = "waterLevel";
SerialLogHandler logHandler;

int secondsUntilNextEvent();

void setup() {
    Serial.begin(9600);
    
    // LED pin
    pinMode(led, OUTPUT);

    // Rainfall sensor ISR
    pinMode(RAIN_PIN, INPUT_PULLUP);
    //attachInterrupt(RAIN_PIN, rainfallISR, FALLING);

    // SD card setup
    if (!sd.begin(SD_CHIP_SELECT, SPI_FULL_SPEED)) {
        Log.info("Failed to initialize SD card");
    }

    // Particle connection
    if (PUBLISHING == 0) {
        Particle.connect();
    } else {
        Cellular.off();
    }

    Log.info("Setup complete");
}

void loop() {
    switch (state) {
        case DATALOG_STATE: {
            Log.info("DATALOG_STATE");

            // Take multiple readings from Maxbotix sensor
            for (int sample = 0; sample < 200; sample++) {
                filterArray[sample] = analogRead(A1);
                delay(50);
            }

            // Sort to remove outliers
            for (int i = 0; i < 199; i++) {
                for (int j = i + 1; j < 200; j++) {
                    if (filterArray[i] > filterArray[j]) {
                        float temp = filterArray[i];
                        filterArray[i] = filterArray[j];
                        filterArray[j] = temp;
                    }
                }
            }

            // Average middle 180 values
            double sum = 0;
            for (int sample = 10; sample < 190; sample++) {
                sum += filterArray[sample];
            }
            distance_unconverted = sum / 180;
            range_cm = distance_unconverted * 0.25; // conversion factor

            real_time = Time.now();
            millis_now = millis();

            float cellVoltage = batteryMonitor.getVCell();
            float stateOfCharge = batteryMonitor.getSoC();

            snprintf(data, sizeof(data), "%li,%.5f,%.2f,%.2f,%.2f",
                real_time,
                range_cm,
                cellVoltage,
                stateOfCharge,
                rainfall_mm
            );

            Log.info("Distance: %.2f cm, Rainfall: %.2f mm", range_cm, rainfall_mm);

            // Save to SD
            File myFile;
            if (myFile.open("distance.csv", O_RDWR | O_CREAT | O_AT_END)) {
                myFile.print(data);
                myFile.print("\n");
                myFile.close();
            } else {
                Log.info("Failed to open distance.csv");
            }

            state = (PUBLISHING == 1) ? PUBLISH_STATE : SLEEP_STATE;
        }
        break;

        case PUBLISH_STATE: {
            Log.info("PUBLISH_STATE");
            stateTime = millis();
            bool isMaxTime = false;

            while (!isMaxTime) {
                if (!Particle.connected()) {
                    Particle.connect();
                }
                if (Particle.connected()) {
                    bool success = Particle.publish(eventName, data, 60, PRIVATE, WITH_ACK);
                    Log.info("Publish result: %d", success);
                    isMaxTime = true;
                    state = SLEEP_STATE;
                } else if (millis() - stateTime >= MAX_TIME_TO_PUBLISH_MS) {
                    isMaxTime = true;
                    state = SLEEP_STATE;
                    Log.info("Max publish time reached, going to sleep");
                }
                delay(500);
            }
        }
        break;

        case SLEEP_STATE: {
            Log.info("SLEEP_STATE");

            int wakeInSeconds = secondsUntilNextEvent();

            SystemSleepConfiguration config;
            config.mode(SystemSleepMode::ULTRA_LOW_POWER)
                  .gpio(D2, FALLING)
                  .duration(wakeInSeconds * 1000L);

            SystemSleepResult result = System.sleep(config);
            Log.info("Woke up, returning to DATALOG_STATE");

            state = DATALOG_STATE;
        }
        break;
    }
}

int secondsUntilNextEvent() {

  int current_seconds = Time.now();
  int seconds_to_sleep = SECONDS_BETWEEN_MEASUREMENTS - (current_seconds % SECONDS_BETWEEN_MEASUREMENTS);

  Log.info("Sleeping for %i", seconds_to_sleep);

  return seconds_to_sleep;
}