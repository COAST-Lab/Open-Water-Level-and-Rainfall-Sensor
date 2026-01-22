#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SdFat.h>
#include <Wire.h>
#include <SPI.h>

//------------------SD SPI Configuration Details--------------------------------
const int SD_CHIP_SELECT = 10; // Pin 10
SdFat sd;

//------------------Display Configuration----------------------------------------
Adafruit_SSD1306 display(128, 32, &Wire); // Declare at global scope
float filterArray[100]; // array to store data samples from sensor

//------------------LED Setup---------------------------------------------------
int led = 13; // Using onboard LED for Arduino
bool led_state = HIGH; // Starting state

//------------------Maxbotix Sensor---------------------------------------------
float distance_unconverted; // Raw analog read
float range_cm;

unsigned long real_time;
char data[120];

void setup() {
  pinMode(led, OUTPUT);

  Serial.begin(9600);
  Serial.println("Open Water Level - Fast Update Mode");

  // Initialize SD card
  // if (!sd.begin(SD_CHIP_SELECT)) {
  //   Serial.println("SD card initialization failed!");
  // } else {
  //   Serial.println("SD card initialized.");
  // }

  // Initialize display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 initialization failed!");
    while (true); // Halt if the display initialization fails
  }
  // Rotate display 180 degrees
  display.setRotation(2); 

  // Show startup screen
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("SEAS the");
  display.println("  day!");
  display.display(); // Show splash screen
  delay(1000); // Wait for the user to see it

  display.clearDisplay(); // Clear display for new data
}

void loop() {
  // Read sensor
  //distance_unconverted = analogRead(A1);
  //range_cm = distance_unconverted * 0.25;
    for (int i = 0; i < 100; i++) {
    filterArray[i] = analogRead(A1);  // read A0
    delay(5); // small delay to avoid interference
  }

  //----------------- Sort the array -------------------------------
  for (int i = 0; i < 99; i++) {
    for (int j = i + 1; j < 100; j++) {
      if (filterArray[i] > filterArray[j]) {
        int16_t swap = filterArray[i];
        filterArray[i] = filterArray[j];
        filterArray[j] = swap;
      }
    }
  }

  //----------------- Average middle samples -----------------------
  double sum = 0;
  for (int i = 10; i < 90; i++) {
    sum += filterArray[i];
  }

  delay (100);
  distance_unconverted = sum / float(80);


//   // Save to SD
//   // snprintf(data, sizeof(data), "%lu,%.5f", real_time, range_cm);
//   // File dataFile = sd.open("distance.csv", FILE_WRITE);
//   // if (dataFile) {
//   //   dataFile.println(data);
//   //   dataFile.close();
//   //   Serial.println("Data saved to SD:");
//   //   Serial.println(data);
//   // } else {
//   //   Serial.println("Error opening distance.csv");
//   // }

  // Update OLED display
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("ADC:");
  display.println(distance_unconverted, 1); // 1 decimal place
  display.display();

  // Optional: blink LED to show activity
  digitalWrite(led, led_state);
  led_state = !led_state;

  // Wait 1 second before next read
  delay(1000);
}

