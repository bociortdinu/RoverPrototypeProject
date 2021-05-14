// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006
boolean is_written = false;
// This example code is in the public domain.
#include <SoftwareSerial.h>   //import Software Serial library
SoftwareSerial BTserial(2,3); // Pini modul bluetooth for Rx and Tx respectively
String command = "";
String string;

#include <Wire.h>

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  BTserial.begin(9600);
}

byte x = 0;

void loop()
{

  while (BTserial.available())    //if the Bluetooth client is available
  {
    char ch = BTserial.read();    //read data from stream
    command = command + ch;       //create string command
    delay(3);
  }
  
   if (!(BTserial.available()))    //controlling 'is_written' to make sure printing is done only once per choice
  {
    is_written = false;
  }
  
  if (command.length() > 0 && is_written == false )
  {
    if (command == "Roata")       //matching case for IR sensor
      {
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write("Roata");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
    command = "";
    
  }
  
//  Wire.beginTransmission(4); // transmit to device #4
//  Wire.write("x is ");        // sends five bytes
//  Wire.write(x);              // sends one byte  
//  Wire.endTransmission();    // stop transmitting

//  x++;
  delay(500);
}
