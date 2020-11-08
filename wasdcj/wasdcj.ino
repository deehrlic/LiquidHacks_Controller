#include <Mouse.h>
#include <Keyboard.h>

// 

int w = 4;
int a = 5;
int s = 6;
int d = 7;
int crouch = 8;
int jump = 9;

//

void setup() {
  Keyboard.begin();
  pinMode(w, INPUT);
  pinMode(a, INPUT);
  pinMode(s, INPUT);
  pinMode(d, INPUT);
  pinMode(crouch, INPUT);
  pinMode(jump, INPUT);
}

void loop() {
  int wState = digitalRead(w);
  if(wState == 1){
  Keyboard.press('w');
  }
  else{
    Keyboard.release('w');   
  }
  int aState = digitalRead(a);
  if(aState == 1){
  Keyboard.press('a');
  }
  else{
    Keyboard.release('a');   
  }
  int sState = digitalRead(s);
  if(sState == 1){
  Keyboard.press('s');
  }
  else{
    Keyboard.release('s');   
  }
  int dState = digitalRead(d);
  if(dState == 1){
  Keyboard.press('d');
  }
  else{
    Keyboard.release('d');   
  }
  int cState = digitalRead(crouch);
  if(cState == 1){
  Keyboard.press(KEY_LEFT_CTRL);
  }
  else{
    Keyboard.release(KEY_LEFT_CTRL);   
  }
  int jState = digitalRead(jump);
  if(jState == 1){
  Keyboard.press((char)0x20);
  }
  else{
    Keyboard.release((char)0x20);   
  }

}
