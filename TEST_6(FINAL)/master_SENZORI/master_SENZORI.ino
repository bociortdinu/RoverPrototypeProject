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

//SENSORS
#define FRONT_trigPin_US 4
#define FRONT_echoPin_US 5

#define BACK_trigPin_US 6
#define BACK_echoPin_US 7

#define LEFT_trigPin_US 8
#define LEFT_echoPin_US 9

#define RIGHT_trigPin_US 10 
#define RIGHT_echoPin_US 11

boolean sendData = false;

unsigned long previousTime = 0;
byte seconds ;
bool readSensors;

void setup()
{
  Wire.begin(2); // join i2c bus (address optional for master)
  Serial.begin(9600);
  BTserial.begin(9600);

  pinMode(FRONT_trigPin_US, OUTPUT);
  pinMode(FRONT_echoPin_US, INPUT);

  pinMode(BACK_trigPin_US, OUTPUT);
  pinMode(BACK_echoPin_US, INPUT);

  pinMode(LEFT_trigPin_US, OUTPUT);
  pinMode(LEFT_echoPin_US, INPUT);

  pinMode(RIGHT_trigPin_US, OUTPUT);
  pinMode(RIGHT_echoPin_US, INPUT);

  readSensors = false;
}

byte x = 0;

void loop()
{
  if (millis() >= (previousTime))
  {
     previousTime = previousTime + 1000;  // use 100000 for uS
     seconds = seconds +1;
     Serial.println("Au trecut " + String(seconds) + " secunde");
     Serial.println(millis());
     readSensors = true;
  }


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

      // comanda care trimite datele senzorilr catre aplicatie
      if (command == "readON")
      {
        sendData = true;
      }
      //comanda care opreste trimiterea datelor catre aplicatie
      if (command == "readOFF")
      {
        sendData = false;
      }

      
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
      if (command == "bLEFT16")       
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


//      // comanda oprire ROTI venita de la senzori
//      if (command == "stopFRONT")
//      {
//        Wire.beginTransmission(4); // transmit to device #4
//        Wire.write("stopFRONT");        // sends five bytes
//        Wire.endTransmission();    // stop transmitting
//        command = "";
//      }

      
    command = "";
    
  }



  if(readSensors == true)
  {

    Serial.println("Am citit senzorii");

    //Ultrasonic Sensors
    // FRONT
    long FRONT_duration, FRONT_distance;
    digitalWrite(FRONT_trigPin_US, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(FRONT_trigPin_US, HIGH);
  //  delayMicroseconds(1000); - Removed this line
    delayMicroseconds(10); // Added this line
    digitalWrite(FRONT_trigPin_US, LOW);
    FRONT_duration = pulseIn(FRONT_echoPin_US, HIGH);
    FRONT_distance = (FRONT_duration/2) / 29.1;

    if(sendData)
    {
        if (FRONT_distance >= 200 || FRONT_distance <= 0){
        BTserial.print("FRONT : ");
        BTserial.print("Out of range\n");
        
        }
        else {
          BTserial.print("FRONT : ");
          BTserial.print(FRONT_distance);
          BTserial.print(" cm\n");
          
        }
    }
    
    delay(10);


    // BACK
    long BACK_duration, BACK_distance;
    digitalWrite(BACK_trigPin_US, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(BACK_trigPin_US, HIGH);
  //  delayMicroseconds(1000); - Removed this line
    delayMicroseconds(10); // Added this line
    digitalWrite(BACK_trigPin_US, LOW);
    BACK_duration = pulseIn(BACK_echoPin_US, HIGH);
    BACK_distance = (BACK_duration/2) / 29.1;

    if(sendData)
    {
        if (BACK_distance >= 200 || BACK_distance <= 0){
        BTserial.print("BACK : ");
        BTserial.print("Out of range\n");
        }
        else {
          BTserial.print("BACK : ");
          BTserial.print(BACK_distance);
          BTserial.print(" cm\n");
          
        }
    }
    
    delay(10);


    // LEFT
    long LEFT_duration, LEFT_distance;
    digitalWrite(LEFT_trigPin_US, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(LEFT_trigPin_US, HIGH);
  //  delayMicroseconds(1000); - Removed this line
    delayMicroseconds(10); // Added this line
    digitalWrite(LEFT_trigPin_US, LOW);
    LEFT_duration = pulseIn(LEFT_echoPin_US, HIGH);
    LEFT_distance = (LEFT_duration/2) / 29.1;

    if(sendData)
    {
        if (LEFT_distance >= 200 || LEFT_distance <= 0){
        BTserial.print("LEFT : ");
        BTserial.print("Out of range\n");
        }
        else {
          BTserial.print("LEFT : ");
          BTserial.print(LEFT_distance);
          BTserial.print(" cm\n");
        }
    }
    
    delay(10);



    // RIGHT
    long RIGHT_duration, RIGHT_distance;
    digitalWrite(RIGHT_trigPin_US, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(RIGHT_trigPin_US, HIGH);
  //  delayMicroseconds(1000); - Removed this line
    delayMicroseconds(10); // Added this line
    digitalWrite(RIGHT_trigPin_US, LOW);
    RIGHT_duration = pulseIn(RIGHT_echoPin_US, HIGH);
    RIGHT_distance = (RIGHT_duration/2) / 29.1;

    if(sendData)
    {
        if (RIGHT_distance >= 200 || RIGHT_distance <= 0){
        BTserial.print("RIGHT : ");
        BTserial.print("Out of range\n");
        }
        else { 
          BTserial.print("RIGHT : ");
          BTserial.print(RIGHT_distance);
          BTserial.print(" cm\n");
        }
    }
    

    delay(10);


    if(FRONT_distance <= 10)
      {
        
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write("stopFRONTgo");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
        delay(2000);
        
      }else if(FRONT_distance <= 20){
        
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write("stopFRONT");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
        delay(500);
        
      }else if(BACK_distance <= 10)
      {
        
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write("stopBACKgo");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
        delay(2000);
        
      }else if(BACK_distance <= 20){
        
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write("stopBACK");        // sends five bytes
        Wire.endTransmission();    // stop transmitting
        delay(500);
        
      }
    
    readSensors = false;
  }





  
  
//  Wire.beginTransmission(4); // transmit to device #4
//  Wire.write("x is ");        // sends five bytes
//  Wire.write(x);              // sends one byte  
//  Wire.endTransmission();    // stop transmitting

//  x++;
  delay(100);
}
