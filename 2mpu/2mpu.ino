//Boilerplate code to enable MPU 6050: https://www.youtube.com/watch?v=fvWNnUdWwrA
//Modified by Drew Ehrlich for LiquidHacks2020!

#include <Wire.h>
#include <Mouse.h>
#include <Keyboard.h>

const int MPU2 = 0x69, MPU1=0x68;

long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ, gyroX, gyroY, gyroZ,rotX, rotY, rotZ;
long accelX2, accelY2, accelZ2;
float gForceX2, gForceY2, gForceZ2, elapsedTime, previousTime, currentTime, yaw, yawPrev, yawDiff, yaw2prev;

int lClick = 9;
int rClick = 8;
int shift = 7;
int q = 6;
int e = 10;
int x = 15;
int c = 14;
int scroll = 5;
int r = 16;
int scrollStatus=1;

char keys[] = {'1','2','3','4'};

int prev0 = 0;
int prev1 = 0;

void setup(){
  Wire.begin();
  Keyboard.begin();
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

  pinMode(lClick, INPUT);
  pinMode(rClick, INPUT);
  pinMode(shift, INPUT);
  pinMode(q, INPUT);
  pinMode(e, INPUT);
  pinMode(x, INPUT);
  pinMode(c, INPUT);
  pinMode(scroll, INPUT);
  pinMode(r, INPUT);
}

void loop(){
  GetMpuValue(MPU1);

  GetMpuValue(MPU2);
 

  int lClickState = digitalRead(lClick);
  if(lClickState == 1){
    Mouse.press();
  }
  else{
    Mouse.release();
  }
  int rClickState = digitalRead(rClick);
  if(rClickState == 1){
    Mouse.press(MOUSE_RIGHT);
  }
  else{
    Mouse.release(MOUSE_RIGHT);
  }
  int shiftState = digitalRead(shift);
  if(shiftState == 1){
    Keyboard.press(KEY_LEFT_SHIFT);
  }
  else{
    Keyboard.release(KEY_LEFT_SHIFT);
  }
  int qState = digitalRead(q);
  if(qState == 1){
    Keyboard.press('q');
  }
  else{
    Keyboard.release('q');
  }
  int eState = digitalRead(e);
  if(eState == 1){
    Keyboard.press('e');
  }
  else{
    Keyboard.release('e');
  }
  int xState = digitalRead(x);
  if(xState == 1){
    Keyboard.press('x');
  }
  else{
    Keyboard.release('x');
  }
  int cState = digitalRead(c);
  if(cState == 1){
    Keyboard.press('c');
  }
  else{
    Keyboard.release('c');
  }
  int scrollState = digitalRead(scroll);
  if(scrollState == 1){
     Keyboard.press(keys[scrollStatus-1]);
     if(scrollStatus==4){
      scrollStatus=1;
    }
    else{
      scrollStatus++;
    }
  }
  else{
    Keyboard.release('4');
    Keyboard.release('3');
    Keyboard.release('1');
    Keyboard.release('2');
  }
  int rState = digitalRead(r);
  if(rState == 1){
    Keyboard.press('r');
  }
  else{
    Keyboard.release('r');
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
  yawDiff = (yaw2prev+yawPrev+yaw)/3-yaw;
  
  
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
     Mouse.move(-10, 0);
  }
  else if(MPU == 104 && (yawDiff)>0.01){
     Mouse.move(5, 0);
  }
    prev1 = gForceY;
    yaw2prev = yawPrev;
    yawPrev = yaw;
  
  
}
