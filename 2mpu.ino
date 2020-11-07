//Boilerplate code to enable MPU 6050: https://www.youtube.com/watch?v=fvWNnUdWwrA
//Modified by Drew Ehrlich for LiquidHacks2020!

#include <Wire.h>
#include <Mouse.h>
const int MPU2 = 0x69, MPU1=0x68;

long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ, gyroX, gyroY, gyroZ,rotX, rotY, rotZ;
long accelX2, accelY2, accelZ2;
float gForceX2, gForceY2, gForceZ2, elapsedTime, previousTime, currentTime, yaw, yawPrev, yawDiff;

int pushButton = 9;

int prev0 = 0;
int prev1 = 0;

void setup(){
  Wire.begin();
  Mouse.begin();
  Wire.beginTransmission(MPU1);
  Wire.write(0x6B);
  Wire.write(0b00000000);
  Wire.endTransmission();  
  Wire.beginTransmission(MPU1);
  Wire.write(0x1B);
  Wire.write(0x00000000);
  Wire.endTransmission(); 
  Wire.beginTransmission(MPU1);
  Wire.write(0x1C);
  Wire.write(0b00000000);
  Wire.endTransmission(); 
  
  Wire.begin();
  Wire.beginTransmission(MPU2);
  Wire.write(0x6B);
  Wire.write(0b00000000); 
  Wire.endTransmission();  
  Wire.beginTransmission(MPU2); 
  Wire.write(0x1B);
  Wire.write(0x00000000);
  Wire.endTransmission(); 
  Wire.beginTransmission(MPU2);
  Wire.write(0x1C);
  Wire.write(0b00000000);
  Wire.endTransmission(); 
  Serial.begin(38400);

  pinMode(pushButton, INPUT);
  
}

void loop(){
  GetMpuValue(MPU1);
  Serial.print("\t ||| \t");

  GetMpuValue(MPU2);
  //Serial.println("");

  int buttonState = digitalRead(pushButton);
  if(buttonState == 1){
    Serial.print("fire!");
    Mouse.click();
  }

}

void GetMpuValue(const int MPU){

  previousTime = currentTime;        
  currentTime = millis();            
  elapsedTime = (currentTime - previousTime) / 1000;
  
  Wire.beginTransmission(MPU); 
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(MPU,6);
  while(Wire.available() < 6);
  accelX = Wire.read()<<8|Wire.read(); 
  accelY = Wire.read()<<8|Wire.read(); 
  accelZ = Wire.read()<<8|Wire.read();
  
  Wire.beginTransmission(MPU);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(MPU,6);
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read();
  gyroY = Wire.read()<<8|Wire.read();
  gyroZ = (Wire.read()<<8|Wire.read())/131.0; 
  
  gForceY = accelY / 16384.0; 
  gForceX = accelX / 16384.0; 

  
  yaw = yaw + gyroZ * elapsedTime;
  yawDiff = yaw-yawPrev;
  //Serial.print(yawDiff);
  

  //Serial.print(yaw);
  
  if(MPU == 105 && abs(gForceY)>.08){
    if(prev0>gForceY){
      Mouse.move(0, 5);
    }
    else if(prev0<gForceY){
      Mouse.move(0, -5);
    }
    prev0 = gForceY;
  }
  else if(MPU == 104 && (yawDiff)<-.01){
     Mouse.move(5, 0);
  }
  else if(MPU == 104 && (yawDiff)>0.1){
     Mouse.move(-10, 0);
  }
    prev1 = gForceY;
    yawPrev = yaw;
  
  
}
