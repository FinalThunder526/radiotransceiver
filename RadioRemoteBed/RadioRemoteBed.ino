#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

int a, b, j;
int yVal, xVal;
int isUp, isRight;
int throttle;

char * taddr = "switches";

#define throttlePot A4
#define xAnalog A6
#define yAnalog A7

// Equivalent to Analog pins
#define jButton 15
#define aButton 16
#define bButton 17

// On custom PCB's, CE is 7, CSN is 8
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
  pinMode(jButton, INPUT);
  
  Serial.println("Listening..."); 
}

void loop(){
  byte data[Mirf.payload];
  
  data[0] = byte0();
  data[1] = byte1();
  data[2] = byte2();
  data[3] = byte3();
  
  Serial.print("j");
  Serial.print(j);
  Serial.print(" a");
  Serial.print(a);
  Serial.print(" b");
  Serial.print(b);
  Serial.print(". ");
  
  setJoystickVal();
  setButtons();
  setThrottleVal();
  
  if(!Mirf.isSending()){
    Mirf.setTADDR((byte *)taddr);
    
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
  yVal = analogRead(yAnalog);
  xVal = analogRead(xAnalog);
}

void setThrottleVal() {
  throttle = analogRead(throttlePot);
}

void setButtons() {
  a = !digitalRead(aButton);
  b = !digitalRead(bButton);
  j = !digitalRead(jButton);
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
  byte n = 0;
  int y512 = map(yVal, 0, 1024, -255, 256);
  isUp = getSign(y512);
  n = abs(y512);
  return n;
}

// Right left
byte byte2() { 
  byte n = 0;
  int x512 = map(xVal, 0, 1024, -255, 256);
  isRight = getSign(x512);
  n = abs(x512);
  return n;
}

// Throttle
byte byte3() {
  byte x = map(throttle, 0, 1024, 0, 256);
  return x;
}
