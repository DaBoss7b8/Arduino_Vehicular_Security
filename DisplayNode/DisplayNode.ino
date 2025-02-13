/**********************************************
This code serves to read the incoming messages coming from the CANBus, break it down and understand it, and then display the values on the OLED Screen
Reference code from Arduino_CAN and the graphics test for the ILI9341 will be used for command syntax and best practices. 

Code written by Srivatsan Mukunthraj on 1/30/2024

**********************************************/

// Libraries for running the display
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// Library for interfacing with CAN
#include <Arduino_CAN.h>

// Defining the Chip Select, Reset, and Data/Command pin, which just take on Digital Pins
#define TFT_CS     10
#define TFT_RST    9
#define TFT_DC     8

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);     // Adafruit command to create the tft object which will reference the display

void setup() {
  
  // CAN Setup
  Serial.begin(115200);     //Set the serial baud rate to 115200

  while (!Serial) { }       // Constantly checks if the Serial is running, basically pausing the program until the connection has been established

  if (!CAN.begin(CanBitRate::BR_500k))            // This initializes CAN and also checks if it fails to initialize and serial prints that, currently set to 500 kbps
  {
    Serial.println("CAN.begin(...) failed.");     // Prints that CAN initialization has failed in Serial (Might want to consider making it an LED somehow)
    for (;;) {}                                   // Pauses moving forward in the code until CAN communication has been initialized 
  }

  tft.begin();              // Initializing the screen (tft stands for Thin Film Transistor)

}

void loop() {

  if (CAN.available())
  {
    CanMsg const msg = CAN.read();        // Assigning the reading taken from the CAN Bus into the variable msg

    

  }

  
  

}
