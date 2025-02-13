/* 
This program is for the first Time of Flight node in the CAN testbench.
A quick overview of the code, the Time of Flight sensor will collect 50 samples a second, 
in line with the typical sample speed of a sensor in an actual production vehicle. 
This data will then be packaged in a CAN message, and sent into the Bus. 

Ideally, the display node (or whichever node is looking for a message with the ID set below)
will read this transmission and act accordingly

This code has been fully created by Srivatsan Mukunthraj, and modified last on 1/30/2025
Example code from vl53l0X-arduino and Arduino_CAN was used to understand syntax and process. Everything else is original

*/


#include <Wire.h>         // Used for I2C communication, which the sensor uses
#include <VL53L0X.h>      // Library specific to used sensor for Time of Flight
#include <Arduino_CAN.h>  // Arduino's CAN Library !!

VL53L0X sensor;  
static uint32_t const CAN_ID = 0x10;      // Setting the CAN ID of this node. This is also used for message prioritization, and can be changed as needed


void setup() {
  
  Serial.begin(115200);     //Set the serial baud rate to 115200
  Wire.begin();             //Begin using I2C

  while (!Serial) { }       // Constantly checks if the Serial is running, basically pausing the program until the connection has been established

  if (!CAN.begin(CanBitRate::BR_500k))            // This initializes CAN and also checks if it fails to initialize and serial prints that, currently set to 500 kbps
  {
    Serial.println("CAN.begin(...) failed.");     // Prints that CAN initialization has failed in Serial (Might want to consider making it an LED somehow)
    for (;;) {}                                   // Pauses moving forward in the code until CAN communication has been initialized 
  }

  sensor.setTimeout(500);                         // Sensor timeout set to 500
  if (!sensor.init())                             // Initializes sensor, and if it fails, does the stuff in if statement
  {
    Serial.println("Failed to detect and initialize sensor!");      // Writes to serial monitor
    while (1) {}                                                    //Basically waits until the sensor is successfully initialized
  }

  sensor.startContinuous(20);                     // Sensor continuously collects information basically every 20 ms, for 50 samples a second

}

static uint32_t reading;                          // define the reading variable, which has ToF stuff

void loop() {

  reading = sensor.readRangeContinuousMillimeters();        // Assigns the sensor reading to the reading variable
  if (sensor.timeoutOccurred()) {Serial.print("TIMEOUT");}    // Checks if the sensor has timed out, and then prints TIMEOUT in the serial monitor

  uint8_t const transmission[] = {0xCA,0xFE,0,0,0,0,0,0};     // Initialize the message that will be sent from CAN, this was taken from the Arduino example program

  memcpy((void*)(transmission + 4), &reading, sizeof(reading)); // Lot happening in this line of code. Memcpy basically is a copy function, which copies data from one place to another
  // the (void*)(transmission + 4) points to the address of transmission after the first 4 bytes. It then takes the address of "reading", the size of it, and copies it in

  CanMsg const msg(CanStandardId(CAN_ID), sizeof(transmission), transmission);  // The line creates an object called msg, which is kept constant so that the contents of the message aren't change midway through transmission
  // CanMsg is a struct that is part of the Arduino CAN library which formulates the message. It takes the CAN_ID, size of transmission, and transmission to formulate the message

  if (int const rc = CAN.write(msg); rc < 0){        // Error handling happens here. The message is sent through CAN.write, and the return value is set to constant rc
   // If rc is less than zero, an error has occured, and the error is printed out in the serial monitor
    Serial.print("CAN.write failed with error code");
    Serial.println(rc);
    for (;;) {}
  }
  else{
    Serial.println("Success");
  }


}
