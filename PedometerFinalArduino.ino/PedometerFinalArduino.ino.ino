/*
~Pedometer by fitME

Members:
Rakshintha Prasad
Parvathi Krishnan
Sara Hosseini

Description: Uses 3 axes accelerometer (MPU 6050) 
to evaluate motion along axis and detects steps above a certain
threshold

*code based off of Arduino MPU 6050 sample code*

Circuit:
MPU VCC ---> Arduino 5V
MPU GND ---> Arduino GND
MPU SCL ---> Arduino A5
MPU SDA ---> Arduino A4
MPU INT ---> Arduino PIN 2
*/

#include<Wire.h>

const int mpuAddress=0x68; // I2C address of the MPU-6050
int counter = 0;
int16_t AclX = 0;
int16_t AclY = 0;
int16_t AclZ = 0;

int OldAclX = 0;
int OldAclY = 0;
int OldAclZ = 0;
int AcSensitivity = 5000;
boolean moved = false;

void setup(){
  Wire.begin();
  Wire.beginTransmission(mpuAddress);
  Wire.write(0x6B); 
  Wire.write(0); 
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void loop(){
  Wire.beginTransmission(mpuAddress);
  Wire.write(0x3B); 
  Wire.endTransmission(false);
  Wire.requestFrom(mpuAddress,14,true); 
  
  //AclX=Wire.read()<<8|Wire.read(); 
  AclY=Wire.read()<<8|Wire.read();
  AclZ=Wire.read()<<8|Wire.read(); 

//Checking for movement along axes
if(abs(OldAclX - AclX) > AcSensitivity){

moved = true;
counter++;
}

//
if(abs(OldAclY - AclY) > AcSensitivity){
moved = true;
counter++;
}

if(abs(OldAclZ - AclZ) > AcSensitivity){
moved = true;
counter++;
}

if (moved == true) {
  
Serial.println(counter);

}

OldAclX = AclX;
OldAclY = AclY;
OldAclZ = AclZ;
moved = false;

delay(300);
}

