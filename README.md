# Arduino_Vehicular_Security
Creating a unique testbench using Arduino Uno R4's to simulate the CAN Network, and conduct attack testing.

The purpose of this Git repository is to showcase the development of a CAN network testbench.  The system makes use of Arduino R4 Minima's as well as some Arduino R4 Wifi/Bluetooth for wireless capability. The Arduino R4 already features CAN capability, meaning that it has the hardware to format and send CAN messages. However, the Arduino's will still need transceivers such that messages can be sent through the CANBUS. This specific setup is a 6-Node configuration, with 3 time-of-flight sensor nodes, display node for showing real time data, and node with bluetooth access as a possible attack vector (Arduino R4 Wifi/Bluetooth), as well as a free node which the user can use as an attack vector. The following is the wiring diagram that was used for this testbench.

