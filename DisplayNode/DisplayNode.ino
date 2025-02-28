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

  Serial.println("Success");

  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  tft.setRotation(2);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  
  tft.setTextSize(2);
  tft.println("Display Test");
  delay(1000);
  tft.fillScreen(ILI9341_BLACK);


}

  uint32_t ToF1 = 0;
  uint32_t ToF2 = 0;
  uint32_t ToF3 = 0;

void loop() {

  if (CAN.available())
  {
    Serial.println("CAN Message available to read");
    CanMsg const msg = CAN.read();        // Assigning the reading taken from the CAN Bus into the variable msg
    Serial.println(msg);
    
    int id;                                // Starting a variable id, which will hold the message ID
    id = msg.getExtendedId();              // Get the message ID from the msg variable

    uint32_t data;                           // data variable to hold the data from message
    memcpy(&data, (void*)(msg.data + 4), sizeof(data));

    if(id == 0x10){
      ToF1 = data;
      Serial.println("ToF1 Updated");
    }

    if(id == 0x11){
      ToF2 = data;
      Serial.println("ToF2 Updated");
    }

    if(id == 0x12){
      ToF3 = data;
      Serial.println("ToF3 Updated");
    }

    printScreen(ToF1, ToF2, ToF3);
    Serial.println("Display time");

  } 
  else{
    Serial.println("Error");
  }

}


unsigned long printScreen(uint32_t ToF1, uint32_t ToF2, uint32_t ToF3){

  unsigned long start = micros();

  // Set text size and background color
  tft.setTextSize(2);

  // Update ToF1 value
  tft.setCursor(0, 60);
  tft.setTextColor(ILI9341_YELLOW, ILI9341_BLACK);  // Yellow text with black background
  tft.print("ToF 1 Distance: ");
  tft.print(ToF1);
  tft.print(" mm");

  // Update ToF2 value
  tft.setCursor(0, 100);
  tft.setTextColor(ILI9341_RED, ILI9341_BLACK);  // Red text with black background
  tft.print("ToF 2 Distance: ");
  tft.print(ToF2);
  tft.print(" mm");

  // Update ToF3 value
  tft.setCursor(0, 140);
  tft.setTextColor(ILI9341_GREEN, ILI9341_BLACK);  // Green text with black background
  tft.print("ToF 3 Distance: ");
  tft.print(ToF3);
  tft.print(" mm");

  return micros() - start;
}

// unsigned long printScreen(uint32_t ToF1, uint32_t ToF2, uint32_t ToF3){

//   unsigned long start = micros();
//   tft.setCursor(0, 0);
//   tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
//   tft.println("Sri's Vehicle");
//   tft.println();
  
//   tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
//   tft.println("ToF 1 Distance: ");
//   tft.println(ToF1);
//   tft.print(" mm");
//   tft.println();
//   tft.setTextColor(ILI9341_RED); tft.setTextSize(2);
//   tft.println("ToF 2 Distance: ");
//   tft.println(ToF2);
//   tft.print(" mm");
//   tft.println();
//   tft.setTextColor(ILI9341_GREEN); tft.setTextSize(2);
//   tft.println("ToF 3 Distance: ");
//   tft.println(ToF3);
//   tft.print(" mm");
//   return micros() - start;

// }
