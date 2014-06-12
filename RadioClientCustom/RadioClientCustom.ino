/*
RadioClientCustom.ino
Margaret Robinson, Sarang Joshi
10 June 2014
*/

#include <BFFRadioReceiver.h>
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

boolean a = false;
boolean b = false;
boolean j = false;
boolean inContact = false;
byte throttle = 127;
int joystickY = 0;
int joystickX = 0;

//CE is 8 normally but it's 7 on the receiver board for whatever reason
#define RadioCE 7
#define RadioCSN 8

BFFRadioReceiver radio(RadioCE, RadioCSN, "switches");

void setup(){
  Serial.begin(9600);
  radio.init(&a, &b, &j, &inContact,
             &throttle, &joystickX, &joystickY);
  
  Serial.println("Beginning ... "); 
}

void loop(){
  int rad = radio.update();
  
  String printed = radio.print();
  Serial.print(printed);
  
  delay(400);
 }
