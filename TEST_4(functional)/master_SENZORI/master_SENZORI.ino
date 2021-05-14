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
  Wire.begin(2); // join i2c bus (address optional for master)
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
    //comanda EN ROTI
    if(command == "rENon")
    {
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write("rENon");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
    }
    if(command == "rENoff")
    {
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write("rENoff");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
    }
    
    // comenzi ROTI
      // S*32
    if (command == "rFRONT32")       
      {
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write("rFRONT32");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "rBACK32")       
      {
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write("rBACK32");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "rLEFT32")       
      {
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write("rLEFT32");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "rRIGHT32")       
      {
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write("rRIGHT32");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
            // S*16
    if (command == "rFRONT16")       
      {
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write("rFRONT16");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "rBACK16")       
      {
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write("rBACK16");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "rLEFT16")       
      {
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write("rLEFT16");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "rRIGHT16")       
      {
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write("rRIGHT16");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
            // S*1
    if (command == "rFRONT1")       
      {
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write("rFRONT1");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "rBACK1")       
      {
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write("rBACK1");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "rLEFT1")       
      {
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write("rLEFT1");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "rRIGHT1")       
      {
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write("rRIGHT1");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }


      //comanda EN BRAT
      if(command == "bENon")
      {
          Wire.beginTransmission(5); // transmit to device #4
          Wire.write("bENon");        // sends five bytes
          Wire.endTransmission();    // stop transmitting
      }
      if(command == "bENoff")
      {
          Wire.beginTransmission(5); // transmit to device #4
          Wire.write("bENoff");        // sends five bytes
          Wire.endTransmission();    // stop transmitting
      }
      
      // comenzi BRAT
            // S*32
      if (command == "bLEFT32")       
      {
        Wire.beginTransmission(5); // transmit to device #5
        Wire.write("bLEFT32");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "bRIGHT32")       
      {
        Wire.beginTransmission(5); // transmit to device #5
        Wire.write("bRIGHT32");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "bFRONT32")       
      {
        Wire.beginTransmission(5); // transmit to device #5
        Wire.write("bFRONT32");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "bBACK32")       
      {
        Wire.beginTransmission(5); // transmit to device #5
        Wire.write("bBACK32");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "bUP32")       
      {
        Wire.beginTransmission(5); // transmit to device #5
        Wire.write("bUP32");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "bDOWN32")       
      {
        Wire.beginTransmission(5); // transmit to device #5
        Wire.write("bDOWN32");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
                  // S*16
      if (command == "bLEFT")       
      {
        Wire.beginTransmission(5); // transmit to device #5
        Wire.write("bLEFT16");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "bRIGHT16")       
      {
        Wire.beginTransmission(5); // transmit to device #5
        Wire.write("bRIGHT16");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "bFRONT16")       
      {
        Wire.beginTransmission(5); // transmit to device #5
        Wire.write("bFRONT16");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "bBACK16")       
      {
        Wire.beginTransmission(5); // transmit to device #5
        Wire.write("bBACK16");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "bUP16")       
      {
        Wire.beginTransmission(5); // transmit to device #5
        Wire.write("bUP16");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "bDOWN16")       
      {
        Wire.beginTransmission(5); // transmit to device #5
        Wire.write("bDOWN16");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
                  // S*1
      if (command == "bLEFT1")       
      {
        Wire.beginTransmission(5); // transmit to device #5
        Wire.write("bLEFT1");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "bRIGHT1")       
      {
        Wire.beginTransmission(5); // transmit to device #5
        Wire.write("bRIGHT1");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "bFRONT1")       
      {
        Wire.beginTransmission(5); // transmit to device #5
        Wire.write("bFRONT1");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "bBACK1")       
      {
        Wire.beginTransmission(5); // transmit to device #5
        Wire.write("bBACK1");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "bUP1")       
      {
        Wire.beginTransmission(5); // transmit to device #5
        Wire.write("bUP1");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }
      if (command == "bDOWN1")       
      {
        Wire.beginTransmission(5); // transmit to device #5
        Wire.write("bDOWN1");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }

      //comeanda CLESTE
      if (command == "bCLAW")       
      {
        Wire.beginTransmission(5); // transmit to device #5
        Wire.write("bCLAW");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      }

      
    command = "";
    
  }
  
//  Wire.beginTransmission(4); // transmit to device #4
//  Wire.write("x is ");        // sends five bytes
//  Wire.write(x);              // sends one byte  
//  Wire.endTransmission();    // stop transmitting

//  x++;
  delay(100);
}
