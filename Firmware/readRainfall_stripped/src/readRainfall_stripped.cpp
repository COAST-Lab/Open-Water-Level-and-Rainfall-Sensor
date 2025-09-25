// /* 
//  * Project myProject
//  * Author: Your Name
//  * Date: 
//  * For comprehensive documentation and examples, please visit:
//  * https://docs.particle.io/firmware/best-practices/firmware-template/
//  */

// // Include Particle Device OS APIs
#include "Particle.h"

// // Let Device OS manage the connection to the Particle Cloud
//SYSTEM_MODE(SEMI_AUTOMATIC);

// // Run the application and system concurrently in separate threads
//SYSTEM_THREAD(ENABLED);

SYSTEM_MODE(MANUAL); // uncomment for prelim testing
//SYSTEM_MODE(SEMI_AUTOMATIC); // uncomment for deployment
SYSTEM_THREAD(ENABLED);
//WiFi.off();

// // Show system, cloud connectivity, and application logs over USB
// // View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);


// void setup() {
//   Cellular.off();
//   Log.info("Setup started");
//   Wire.begin();              // join i2c bus as master

//   while(!Wire.available()) {
//     Log.info("Waiting for I2C"); //stuck here!!
//     delay(500);
//   }
// }

// void loop() {
//   Log.info("Loop started");
//   Wire.requestFrom(0x1D, 2, true);
//   Log.info("Requested from 0x1D"); // request 2 bytes from slave device #4
//   delay(500); 

//   while(Wire.available()){  
//     Log.info("Wire available"); // slave may send less than requested
//     delay(500);
//   }

//   delay(500);
// }


// // --------------------------------------
// // i2c_scanner
// //
// // http://playground.arduino.cc/Main/I2cScanner
// //
// // Version 1
// //    This program (or code that looks like it)
// //    can be found in many places.
// //    For example on the Arduino.cc forum.
// //    The original author is not know.
// // Version 2, Juni 2012, Using Arduino 1.0.1
// //     Adapted to be as simple as possible by Arduino.cc user Krodal
// // Version 3, Feb 26  2013
// //    V3 by louarnold
// // Version 4, March 3, 2013, Using Arduino 1.0.3
// //    by Arduino.cc user Krodal.
// //    Changes by louarnold removed.
// //    Scanning addresses changed from 0...127 to 1...119,
// //    according to the i2c scanner by Nick Gammon
// //    http://www.gammon.com.au/forum/?id=10896
// // Version 5, March 28, 2013
// //    As version 4, but address scans now to 127.
// //    A sensor seems to use address 120.
// //
// //
// // This sketch tests the standard 7-bit addresses
// // Devices with higher bit address might not be seen properly.
// //

// #include "Particle.h"

// SYSTEM_MODE(MANUAL);

// void setup()
// {
//     Serial.begin(9600);

//     waitFor(Serial.isConnected, 15000);
//     delay(1000);

//     pinMode(CAN_PWR, OUTPUT);
//     digitalWrite(CAN_PWR, HIGH);
//     delay(500);

//     Wire3.begin();

//     Serial.println("\nI2C Scanner");
// }


void loop()
{
    byte error, address;
    int nDevices;

    Log.info("Scanning...");

    nDevices = 0;
    for(address = 1; address < 127; address++ )
    {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0)
        {
            Log.info("I2C device found at address 0x");
            if (address<16)
                Log.info("0");
            char buf[5];
            snprintf(buf, sizeof(buf), "%02X", address);
            Log.info(buf);
            Log.info("  !");

            nDevices++;
        }
        else if (error==4)
        {
            Log.info("Unknown error at address 0x");
            if (address<16)
                Log.info("0");
            char addrBuf[5];
            snprintf(addrBuf, sizeof(addrBuf), "%02X", address);
            Log.info(addrBuf);
        }
    }
    if (nDevices == 0)
        Log.info("No I2C devices found\n");
    else
        Log.info("done\n");

    delay(5000);           // wait 5 seconds for next scan
}