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
int x = 1;

volatile bool STOP;
void setup()
{
  STOP = true;
  
  pinMode (X_DIR, OUTPUT); pinMode (X_STP, OUTPUT);
  pinMode (Y_DIR, OUTPUT); pinMode (Y_STP, OUTPUT);
  pinMode (Z_DIR, OUTPUT); pinMode (Z_STP, OUTPUT);
  pinMode (EN, OUTPUT);
  
  
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  //digitalWrite (EN, LOW);
  digitalWrite (EN, HIGH); // il setam pe oprit EN_off
}

void loop()
{

  if(command.length() > 0)
  {
    Serial.print("Comanda: " + command);

    
    if(command == "rENon")
    {
      STOP = false;
      digitalWrite (EN, LOW);
      command="";
      delay(10);
    }
    if(command == "rENoff")
    {     
      STOP = true;
      digitalWrite (EN, HIGH);
      command="";
      delay(10);
    }
    
    if (command == "rFRONT32")
    {
        command="";
        digitalWrite (X_DIR, false);
        digitalWrite (Y_DIR, true);
        digitalWrite (Z_DIR, false);
        delay (50);
        
        int i=0,N=200*32;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          digitalWrite (X_STP, HIGH);
          digitalWrite (Y_STP, HIGH);
          digitalWrite (Z_STP, HIGH);
          delayMicroseconds (300); 
          digitalWrite (X_STP, LOW);
          digitalWrite (Y_STP, LOW);
          digitalWrite (Z_STP, LOW);
          delayMicroseconds (300);
          i++;
        }
        
    }else if(command == "rFRONT16")
    {
        command="";
        digitalWrite (X_DIR, false);
        digitalWrite (Y_DIR, true);
        digitalWrite (Z_DIR, false);
        delay (50);
        
        int i=0,N=200*16;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          digitalWrite (X_STP, HIGH);
          digitalWrite (Y_STP, HIGH);
          digitalWrite (Z_STP, HIGH);
          delayMicroseconds (300);
          digitalWrite (X_STP, LOW);
          digitalWrite (Y_STP, LOW);
          digitalWrite (Z_STP, LOW);
          delayMicroseconds (300);
          i++;
        }
        
    }else if(command == "rFRONT1")
    {
        command="";
        digitalWrite (X_DIR, false);
        digitalWrite (Y_DIR, true);
        digitalWrite (Z_DIR, false);
        delay (50);
        
        int i=0,N=200*1;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          digitalWrite (X_STP, HIGH);
          digitalWrite (Y_STP, HIGH);
          digitalWrite (Z_STP, HIGH);
          delayMicroseconds (300);
          digitalWrite (X_STP, LOW);
          digitalWrite (Y_STP, LOW);
          digitalWrite (Z_STP, LOW);
          delayMicroseconds (300);
          i++;
        }
        
    }
    
    if(command == "rBACK32")
    {  
        command="";
        digitalWrite (X_DIR, true);
        digitalWrite (Y_DIR, false);
        digitalWrite (Z_DIR, true);
        delay (50);
        
        int i=0,N=200*32;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          digitalWrite (X_STP, HIGH);
          digitalWrite (Y_STP, HIGH);
          digitalWrite (Z_STP, HIGH);
          delayMicroseconds (300);
          digitalWrite (X_STP, LOW);
          digitalWrite (Y_STP, LOW);
          digitalWrite (Z_STP, LOW);
          delayMicroseconds (300);
          i++;
        }
        
    }else if(command == "rBACK16")
    {
        command="";
        digitalWrite (X_DIR, true);
        digitalWrite (Y_DIR, false);
        digitalWrite (Z_DIR, true);
        delay (50);
        
        int i=0,N=200*16;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          digitalWrite (X_STP, HIGH);
          digitalWrite (Y_STP, HIGH);
          digitalWrite (Z_STP, HIGH);
          delayMicroseconds (300);
          digitalWrite (X_STP, LOW);
          digitalWrite (Y_STP, LOW);
          digitalWrite (Z_STP, LOW);
          delayMicroseconds (300);
          i++;
        }
        
    }else if(command == "rBACK1")
    {
        command="";
        digitalWrite (X_DIR, true);
        digitalWrite (Y_DIR, false);
        digitalWrite (Z_DIR, true);
        delay (50);
        
        int i=0,N=200*1;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          digitalWrite (X_STP, HIGH);
          digitalWrite (Y_STP, HIGH);
          digitalWrite (Z_STP, HIGH);
          delayMicroseconds (300);
          digitalWrite (X_STP, LOW);
          digitalWrite (Y_STP, LOW);
          digitalWrite (Z_STP, LOW);
          delayMicroseconds (300);
          i++;
        }
        
    }
    
    if(command == "rLEFT32")
    {

        command="";
        digitalWrite (X_DIR, true);
        digitalWrite (Y_DIR, true);
        digitalWrite (Z_DIR, true);
        delay (50);
        
        int i=0,N=200*32;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          digitalWrite (X_STP, HIGH);
          digitalWrite (Y_STP, HIGH);
          digitalWrite (Z_STP, HIGH);
          delayMicroseconds (500);
          digitalWrite (X_STP, LOW);
          digitalWrite (Y_STP, LOW);
          digitalWrite (Z_STP, LOW);
          delayMicroseconds (500);
          i++;
        }

    }else if(command == "rLEFT16")
    {
        command="";
        digitalWrite (X_DIR, true);
        digitalWrite (Y_DIR, true);
        digitalWrite (Z_DIR, true);
        delay (50);
        
        int i=0,N=200*16;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          digitalWrite (X_STP, HIGH);
          digitalWrite (Y_STP, HIGH);
          digitalWrite (Z_STP, HIGH);
          delayMicroseconds (500);
          digitalWrite (X_STP, LOW);
          digitalWrite (Y_STP, LOW);
          digitalWrite (Z_STP, LOW);
          delayMicroseconds (500);
          i++;
        }
        
    }else if(command == "rLEFT1")
    {
        command="";
        digitalWrite (X_DIR, true);
        digitalWrite (Y_DIR, true);
        digitalWrite (Z_DIR, true);
        delay (50);
        
        int i=0,N=200*1;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          digitalWrite (X_STP, HIGH);
          digitalWrite (Y_STP, HIGH);
          digitalWrite (Z_STP, HIGH);
          delayMicroseconds (500);
          digitalWrite (X_STP, LOW);
          digitalWrite (Y_STP, LOW);
          digitalWrite (Z_STP, LOW);
          delayMicroseconds (500);
          i++;
        }
    }

    
    if(command == "rRIGHT32")
    {

        command="";
        digitalWrite (X_DIR, false);
        digitalWrite (Y_DIR, false);
        digitalWrite (Z_DIR, false);
        delay (50);
        
        int i=0,N=200*32;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          digitalWrite (X_STP, HIGH);
          digitalWrite (Y_STP, HIGH);
          digitalWrite (Z_STP, HIGH);
          delayMicroseconds (500);
          digitalWrite (X_STP, LOW);
          digitalWrite (Y_STP, LOW);
          digitalWrite (Z_STP, LOW);
          delayMicroseconds (500);
          i++;
        }
        
    }else if(command == "rRIGHT16")
    {
        command="";
        digitalWrite (X_DIR, false);
        digitalWrite (Y_DIR, false);
        digitalWrite (Z_DIR, false);
        delay (50);
        
        int i=0,N=200*16;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          digitalWrite (X_STP, HIGH);
          digitalWrite (Y_STP, HIGH);
          digitalWrite (Z_STP, HIGH);
          delayMicroseconds (500);
          digitalWrite (X_STP, LOW);
          digitalWrite (Y_STP, LOW);
          digitalWrite (Z_STP, LOW);
          delayMicroseconds (500);
          i++;
        }
        
    }else if(command == "rRIGHT1")
    {
        command="";
        digitalWrite (X_DIR, false);
        digitalWrite (Y_DIR, false);
        digitalWrite (Z_DIR, false);
        delay (50);
        
        int i=0,N=200*1;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          digitalWrite (X_STP, HIGH);
          digitalWrite (Y_STP, HIGH);
          digitalWrite (Z_STP, HIGH);
          delayMicroseconds (500);
          digitalWrite (X_STP, LOW);
          digitalWrite (Y_STP, LOW);
          digitalWrite (Z_STP, LOW);
          delayMicroseconds (500);
          i++;
        }
        
    }

    
    delay(100);
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
