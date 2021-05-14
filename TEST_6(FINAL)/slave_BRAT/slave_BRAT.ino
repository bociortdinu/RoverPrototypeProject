// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


// Include the Servo library
#include <Servo.h> 

int servoPin = 11;
// Create a servo object
Servo Servo1;
bool clawState;

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
int AXA_X, AXA_X_MIN, AXA_X_MAX;
int AXA_Y, AXA_Y_MIN, AXA_Y_MAX;;
int AXA_Z;
void setup()
{
  AXA_X = 0;
  AXA_X_MAX = 100*37;

  AXA_Y = 0;
  AXA_Y_MAX = 100*20;       // cat are voie sa urce
  AXA_Y_MIN = 0;      // cat are voie sa coboare
  
  AXA_Z = 0;
  
  pinMode (X_DIR, OUTPUT); pinMode (X_STP, OUTPUT);
  pinMode (Y_DIR, OUTPUT); pinMode (Y_STP, OUTPUT);
  pinMode (Z_DIR, OUTPUT); pinMode (Z_STP, OUTPUT);
  pinMode (EN, OUTPUT);
  
  
  Wire.begin(5);                // join i2c bus with address #5
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  //digitalWrite (EN, LOW);
  digitalWrite (EN, HIGH); // il setam pe oprit EN_off

  Servo1.attach(servoPin,600,2300);
  pinMode(servoPin,OUTPUT); 
  clawState = false;
}

void loop()
{

   if(AXA_X == 0)
   {
      AXA_Y_MAX = 100*10;       
      AXA_Y_MIN = 0;      
   }


  if(command.length() > 0)
  {
    Serial.print("Comanda: " + command);

    //comenzi BRAT
    if(command == "bENon")
    {
      digitalWrite (EN, LOW);
      command="";
      delay(10);
    }
    if(command == "bENoff")
    {
      digitalWrite (EN, HIGH);
      command="";
      delay(10);
    }
    
    if(command == "bLEFT32")
    {

        command="";
        digitalWrite (Z_DIR, true);
        delay (50);

        int i=0,N=100*32;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          digitalWrite (Z_STP, HIGH);
          delayMicroseconds (500);
          digitalWrite (Z_STP, LOW);
          delayMicroseconds (500);
          i++;
        }
        
//       BratGoLeft_Z(100*32);
//       command="";
       delay(10);
    }else if(command == "bLEFT16")
    {

        command="";
        digitalWrite (Z_DIR, true);
        delay (50);

        int i=0,N=100*16;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          digitalWrite (Z_STP, HIGH);
          delayMicroseconds (500);
          digitalWrite (Z_STP, LOW);
          delayMicroseconds (500);
          i++;
        }
      
//       BratGoLeft_Z(100*16);
//       command="";
       delay(10);
    }else if(command == "bLEFT1")
    {

        command="";
        digitalWrite (Z_DIR, true);
        delay (50);

        int i=0,N=100*1;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          digitalWrite (Z_STP, HIGH);
          delayMicroseconds (500);
          digitalWrite (Z_STP, LOW);
          delayMicroseconds (500);
          i++;
        }
      
//       BratGoLeft_Z(100*1);
//       command="";
       delay(10);
    }

    if(command == "bRIGHT32")
    {

        command="";
        digitalWrite (Z_DIR, false);
        delay (50);

        int i=0,N=100*32;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          digitalWrite (Z_STP, HIGH);
          delayMicroseconds (500);
          digitalWrite (Z_STP, LOW);
          delayMicroseconds (500);
          i++;
        }
        
//       BratGoRight_Z(100*32);
//       command="";
       delay(10);
    }else if(command == "bRIGHT16")
    {

        command="";
        digitalWrite (Z_DIR, false);
        delay (50);

        int i=0,N=100*16;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          digitalWrite (Z_STP, HIGH);
          delayMicroseconds (500);
          digitalWrite (Z_STP, LOW);
          delayMicroseconds (500);
          i++;
        }
      
//       BratGoRight_Z(100*16);
//       command="";
       delay(10);
    }else if(command == "bRIGHT1")
    {

        command="";
        digitalWrite (Z_DIR, false);
        delay (50);

        int i=0,N=100*1;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          digitalWrite (Z_STP, HIGH);
          delayMicroseconds (500);
          digitalWrite (Z_STP, LOW);
          delayMicroseconds (500);
          i++;
        }
      
//       BratGoRight_Z(100*1);
//       command="";
       delay(10);
    }

    
    if(command == "bFRONT32")
    {
        
        command="";
        digitalWrite (X_DIR, true);
        delay (50);

        int i=0,N=100*32;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          if(AXA_X < AXA_X_MAX)
          {
              digitalWrite (X_STP, HIGH);
              delayMicroseconds (500);
              digitalWrite (X_STP, LOW);
              delayMicroseconds (500);
              AXA_X = AXA_X + 1;
              if( (AXA_X > 100*3 && AXA_X <= 100*16) || (AXA_X > 100*20 && AXA_X <= 100*32) )
              {
                 AXA_Y_MIN = AXA_Y_MIN - 1;
              }
          }
          i++;
        }
        
//       BratGoFront_X(50*32);
//       command="";
       delay(10);
    }else if(command == "bFRONT16")
    {

        command="";
        digitalWrite (X_DIR, true);
        delay (50);

        int i=0,N=100*16;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          if(AXA_X < AXA_X_MAX)
          {
              digitalWrite (X_STP, HIGH);
              delayMicroseconds (500);
              digitalWrite (X_STP, LOW);
              delayMicroseconds (500);
              AXA_X = AXA_X + 1;
              if( (AXA_X > 100*3 && AXA_X <= 100*16) || (AXA_X > 100*20 && AXA_X <= 100*32) )
              {
                 AXA_Y_MIN = AXA_Y_MIN - 1;
              }
          }
          i++;
        }
        
        
//       BratGoFront_X(50*16);
//       command="";
       delay(10);
    }else if(command == "bFRONT1")
    {

        command="";
        digitalWrite (X_DIR, true);
        delay (50);

        int i=0,N=100*1;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          if(AXA_X < AXA_X_MAX)
          {
              digitalWrite (X_STP, HIGH);
              delayMicroseconds (500);
              digitalWrite (X_STP, LOW);
              delayMicroseconds (500);
              AXA_X = AXA_X + 1;
              if( (AXA_X > 100*3 && AXA_X <= 100*16) || (AXA_X > 100*20 && AXA_X <= 100*32) )
              {
                 AXA_Y_MIN = AXA_Y_MIN - 1;
              }
          }
          i++;
        }
        
//       BratGoFront_X(50*1);
//       command="";
       delay(10);
    }

    
    if(command == "bBACK32")
    {
      
        command="";
        digitalWrite (X_DIR, false);
        delay (50);

        int i=0,N=100*32;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          if(AXA_X > 0)
          {
              digitalWrite (X_STP, HIGH);
              delayMicroseconds (500);
              digitalWrite (X_STP, LOW);
              delayMicroseconds (500);
              AXA_X = AXA_X - 1;
              if( (AXA_X > 100*3 && AXA_X <= 100*16) || (AXA_X > 100*20 && AXA_X <= 100*32) )
              {
                 AXA_Y_MIN = AXA_Y_MIN + 1;
              }
              else{
                AXA_Y_MIN = 0;
              }
          }
          i++;
        }
        
//       BratGoBack_X(50*32);
//       command="";
       delay(10);
    }else if(command == "bBACK16")
    {

        command="";
        digitalWrite (X_DIR, false);
        delay (50);

        int i=0,N=100*16;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          if(AXA_X > 0)
          {
              digitalWrite (X_STP, HIGH);
              delayMicroseconds (500);
              digitalWrite (X_STP, LOW);
              delayMicroseconds (500);
              AXA_X = AXA_X - 1;
              if( (AXA_X > 100*3 && AXA_X <= 100*16) || (AXA_X > 100*20 && AXA_X <= 100*32) )
              {
                 AXA_Y_MIN = AXA_Y_MIN + 1;
              }
              else{
                AXA_Y_MIN = 0;
              }
          }
          i++;
        }
        
//       BratGoBack_X(50*16);
//       command="";
       delay(10);
    }else if(command == "bBACK1")
    {
      
        command="";
        digitalWrite (X_DIR, false);
        delay (50);

        int i=0,N=100*1;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          if(AXA_X > 0)
          {
              digitalWrite (X_STP, HIGH);
              delayMicroseconds (500);
              digitalWrite (X_STP, LOW);
              delayMicroseconds (500);
              AXA_X = AXA_X - 1;
              if( (AXA_X > 100*3 && AXA_X <= 100*16) || (AXA_X > 100*20 && AXA_X <= 100*32) )
              {
                 AXA_Y_MIN = AXA_Y_MIN + 1;
              }
              else{
                AXA_Y_MIN = 0;
              }
          }
          i++;
        }
        
//       BratGoBack_X(50*1);
//       command="";
       delay(10);
    }

    
    if(command == "bUP32")
    {

        command="";
        digitalWrite (Y_DIR, true);
        delay (50);

        int i=0,N=100*32;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          if(AXA_Y < AXA_Y_MAX)
          {
              digitalWrite (Y_STP, HIGH);
              delayMicroseconds (500);
              digitalWrite (Y_STP, LOW);
              delayMicroseconds (500);
              AXA_Y = AXA_Y + 1;
          }
          i++;
        }
        
//       BratGoUp_Y(50*32);
//       command="";
       delay(10);
    }else if(command == "bUP16")
    {

        command="";
        digitalWrite (Y_DIR, true);
        delay (50);

        int i=0,N=100*16;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          if(AXA_Y < AXA_Y_MAX)
          {
              digitalWrite (Y_STP, HIGH);
              delayMicroseconds (500);
              digitalWrite (Y_STP, LOW);
              delayMicroseconds (500);
              AXA_Y = AXA_Y + 1;
          }

          i++;
        }
        
//       BratGoUp_Y(50*16);
//       command="";
       delay(10);
    }else if(command == "bUP1")
    {

        command="";
        digitalWrite (Y_DIR, true);
        delay (50);

        int i=0,N=100*1;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          if(AXA_Y < AXA_Y_MAX)
          {
              digitalWrite (Y_STP, HIGH);
              delayMicroseconds (500);
              digitalWrite (Y_STP, LOW);
              delayMicroseconds (500);
              AXA_Y = AXA_Y + 1;
          }

          i++;
        }
        
//       BratGoUp_Y(50*1);
//       command="";
       delay(10);
    }

    
    if(command == "bDOWN32")
    {

        command="";
        digitalWrite (Y_DIR, false);
        delay (50);

        int i=0,N=100*32;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          if(AXA_Y > AXA_Y_MIN)
          {
              digitalWrite (Y_STP, HIGH);
              delayMicroseconds (500);
              digitalWrite (Y_STP, LOW);
              delayMicroseconds (500);
              AXA_Y = AXA_Y - 1;
          }
          i++;
        }
        
//       BratGoDown_Y(50*32);
//       command="";
       delay(10);
    }else if(command == "bDOWN16")
    {

        command="";
        digitalWrite (Y_DIR, false);
        delay (50);

        int i=0,N=100*16;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          if(AXA_Y > AXA_Y_MIN)
          {
              digitalWrite (Y_STP, HIGH);
              delayMicroseconds (500);
              digitalWrite (Y_STP, LOW);
              delayMicroseconds (500);
              AXA_Y = AXA_Y - 1;
          }
          i++;
        }
        
//       BratGoDown_Y(50*16);
//       command="";
       delay(10);
    }else if(command == "bDOWN1")
    {

        command="";
        digitalWrite (Y_DIR, false);
        delay (50);

        int i=0,N=100*1;
        while(i<N) 
        {
          if(command!="")
          {
            break;
          }
          if(AXA_Y > AXA_Y_MIN)
          {
              digitalWrite (Y_STP, HIGH);
              delayMicroseconds (500);
              digitalWrite (Y_STP, LOW);
              delayMicroseconds (500);
              AXA_Y = AXA_Y - 1;
          }

          i++;
        }
        
//       BratGoDown_Y(50*1);
//       command="";
       delay(10);
    }

    
    if(command == "bCLAW")
    {
       BratOpenOrCloseClaw();
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
void BratOpenOrCloseClaw()
{
  if(clawState==false)
  {
    Servo1.write(180);           // DESCHIDE
    delay(100);
    clawState = true;
  }
  else if(clawState==true)
  {
    Servo1.write(90);            //   INCHIDE
    delay(100);
    clawState = false;
  }

}
