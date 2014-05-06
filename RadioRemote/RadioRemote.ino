#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

int a, b, j;
int ud, rl;
int isUp, isRight;
int throttle;

#define throttlePot A4

#define xAnalog A6
#define yAnalog A7

#define aButton 16
#define bButton 17

#define radioCEpin 8
#define radioCSNpin 7

void setup(){
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"serv1");
  // N.B.: Same as Receiver
  Mirf.payload = 4;
  Mirf.config();
  
  // Sets the CSN and CE pins
  Mirf.cePin = radioCEpin;
  Mirf.csnPin = radioCSNpin;
  
  pinMode(aButton, INPUT);
  pinMode(bButton, INPUT);
  
  isRight = 1;
  isUp = 1;
  j = 1;
  b = 1;
  a = 0;
  
  ud = 344;
  rl = 800;
  
  Serial.println("Listening..."); 
}

void loop(){
  byte data[Mirf.payload];
  
  data[0] = byte0();
  data[1] = byte1();
  data[2] = byte2();
  data[3] = byte3();
  
  setJoystickVal();
  setButtons();
  setThrottleVal();
  
  if(!Mirf.isSending()){
    Mirf.setTADDR((byte *)"clie1");
    
    Mirf.send(data);
    
    Serial.print("Message sent.");
    
    for(int i = 0; i < Mirf.payload; i++) {
      Serial.print(" ");
      Serial.print(data[i]);
    }
  }
  Serial.println();    
}

void setJoystickVal() {
  ud = analogRead(yAnalog);
  rl = analogRead(xAnalog);
}

void setThrottleVal() {
  throttle = analogRead(throttlePot);
}

void setButtons() {
  a = !digitalRead(aButton);
  b = !digitalRead(bButton);
}

/////////////////
// PACKET DATA //
/////////////////
// BITS:
// 128
// 64
// 32
// 16     R or L
// 8      U or D
// 4      J
// 2      B
// 1      A

byte byte0() {
  byte x = 0;
  
  x += a*1 + b*2 + j*4;
  x += isUp * 8;
  x += isRight * 16;
  
  return x;
}

int getSign(int x) {
  int y;
  if(x < 0)
    y = 0;
  else
    y = 1;
  return y;
}

// Up down
byte byte1() {
  byte x = 0;
  int ud512 = map(ud, 0, 1024, -255, 256);
  isUp = getSign(ud512);
  x = abs(ud512);
  return x;
}

// Right left
byte byte2() { 
  byte x = 0;
  int rl512 = map(rl, 0, 1024, -255, 256);
  isRight = getSign(rl512);
  x = abs(rl512);
  return x;
}

// Throttle
byte byte3() {
  byte x = map(throttle, 0, 1024, 0, 256);
  return x;
}
