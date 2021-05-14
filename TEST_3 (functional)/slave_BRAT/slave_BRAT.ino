// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


String command="";

//The following is a simple stepper motor control procedures:

# define EN 8 // stepper motor enable , active low
# define X_DIR 5 // X -axis stepper motor direction control
# define Y_DIR 6 // y -axis stepper motor direction control
# define Z_DIR 7 // z axis stepper motor direction control
# define X_STP 2 // x -axis stepper control
# define Y_STP 3 // y -axis stepper control
# define Z_STP 4 // z -axis stepper control 



#include <Wire.h>
int AXA_X, AXA_X_MAX;
int AXA_Y;
int AXA_Z;
void setup()
{
  AXA_X = 0;
  AXA_X_MAX=100;
  AXA_Y = 0;
  AXA_Z = 0;
  
  pinMode (X_DIR, OUTPUT); pinMode (X_STP, OUTPUT);
  pinMode (Y_DIR, OUTPUT); pinMode (Y_STP, OUTPUT);
  pinMode (Z_DIR, OUTPUT); pinMode (Z_STP, OUTPUT);
  pinMode (EN, OUTPUT);
  
  
  Wire.begin(5);                // join i2c bus with address #5
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  digitalWrite (EN, LOW);
}

void loop()
{

  if(command.length() > 0)
  {
    Serial.print("Comanda: " + command);

    //comenzi BRAT
    if(command == "bLEFT")
    {
       BratGoLeft_Z(100);
       command="";
       delay(10);
    }
    if(command == "bRIGHT")
    {
       BratGoRight_Z(100);
       command="";
       delay(10);
    }
    if(command == "bFRONT")
    {
       BratGoFront_X(50);
       command="";
       delay(10);
    }
    if(command == "bBACK")
    {
       BratGoBack_X(50);
       command="";
       delay(10);
    }
    if(command == "bUP")
    {
       BratGoUp_Y(50);
       command="";
       delay(10);
    }
    if(command == "bDOWN")
    {
       BratGoDown_Y(50);
       command="";
       delay(10);
    }
    
  }
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while(0 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    command += c;
    Serial.print(c);         // print the character
  }
//  x = Wire.read();    // receive byte as an integer
//  Serial.println(x);         // print the integer
}


// functii comanda BRAT
void BratGoLeft_Z(int n)
{
        Serial.print("\n Sa primit comanda bLEFT \n");
        digitalWrite (Z_DIR, false);
        delay (50);
        for (int i = 0; i < n; i++)
        {
        digitalWrite (Z_STP, HIGH);
        delayMicroseconds (3700);
        digitalWrite (Z_STP, LOW);
        delayMicroseconds (3700);
        }
}
void BratGoRight_Z(int n)
{
        Serial.print("\n Sa primit comanda bLEFT \n");
        digitalWrite (Z_DIR, true);
        delay (50);
        for (int i = 0; i < n; i++)
        {
        digitalWrite (Z_STP, HIGH);
        delayMicroseconds (3700);
        digitalWrite (Z_STP, LOW);
        delayMicroseconds (3700);
        }
}
void BratGoFront_X(int n)
{
        Serial.print("\n Sa primit comanda bLEFT \n");
        digitalWrite (X_DIR, true);
        delay (50);
        for (int i = 0; i < n; i++)
        {
          if(AXA_X < AXA_X_MAX)
          {
              digitalWrite (X_STP, HIGH);
              delayMicroseconds (3700);
              digitalWrite (X_STP, LOW);
              delayMicroseconds (3700);
              AXA_X = AXA_X + 1;
          }
         
        }
}
void BratGoBack_X(int n)
{
  
        Serial.print("\n Sa primit comanda bLEFT \n");
        digitalWrite (X_DIR, false);
        delay (50);
        for (int i = 0; i < n; i++)
        {
          if(AXA_X > 0)
          {
              digitalWrite (X_STP, HIGH);
              delayMicroseconds (3700);
              digitalWrite (X_STP, LOW);
              delayMicroseconds (3700);
              AXA_X = AXA_X - 1;
          }
          

        }
}
void BratGoUp_Y(int n)
{
        Serial.print("\n Sa primit comanda bLEFT \n");
        digitalWrite (Y_DIR, true);
        delay (50);
        for (int i = 0; i < n; i++)
        {
        digitalWrite (Y_STP, HIGH);
        delayMicroseconds (3700);
        digitalWrite (Y_STP, LOW);
        delayMicroseconds (3700);
        }
}
void BratGoDown_Y(int n)
{
        Serial.print("\n Sa primit comanda bLEFT \n");
        
        digitalWrite (Y_DIR, false);
        delay (50);
        for (int i = 0; i < n; i++)
        {
        digitalWrite (Y_STP, HIGH);
        delayMicroseconds (3700);
        digitalWrite (Y_STP, LOW);
        delayMicroseconds (3700);
        }
}
