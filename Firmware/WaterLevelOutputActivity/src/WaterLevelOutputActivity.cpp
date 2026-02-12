#include "Particle.h"
#include "oled-wing-adafruit.h"

SYSTEM_MODE(MANUAL); 
SYSTEM_THREAD(ENABLED);

//------------------Maxbotix sensor
int j;
float dist_in_sum;
float dist_in_avg;
float range_cm;

long real_time;
int millis_now;

float filterArray[200]; // array to store data samples from sensor
float distance_unconverted; // store the distance from sensor

OledWingAdafruit display;

void setup() {
    display.setup();

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Hello, MSA!");
    display.display(); 
    delay(1000); // Wait for the user to see it

    display.clearDisplay(); // Clear display for new data  
}

void loop() {
    //display.loop();
    display.clearDisplay(); // Clear display for new data  
    // Take multiple measurements and store in array
    for (int sample = 0; sample < 200; sample++) {
      filterArray[sample] = (analogRead(A1));
      delay(100); // to avoid untrasonic interfering
    }
    // Sort; TODO: this looks inefficient. Investigate options to improve (or reject) sorting
    for (int i = 0; i < 199; i++) {
      for (int j = i + 1; j < 200; j++) {
        if (filterArray[i] > filterArray[j]) { //takes highest value
          float swap = filterArray[i];
          filterArray[i] = filterArray[j];
          filterArray[j] = swap; //puts highest number on top
        }
      }
    }

    // Filter noise by excluding 10 smallest and 10 largest samples 
    double sum = 0;
    for (int sample = 10; sample < 190; sample++) {
      sum += filterArray[sample];
    }

    // Get average of the middle samples (from 10 to 190)
    distance_unconverted = sum / 180;

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("ADC Value:");
    display.println(distance_unconverted);
    display.display(); 
    delay(100); 
}

