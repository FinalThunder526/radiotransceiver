/*
RadioClientLib.ino
Margaret Robinson, Sarang Joshi
9 May 2014
*/

#include <BFFRadioReceiver.h>
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

boolean ButtonAPressed = false;
boolean ButtonBPressed = false;
boolean ButtonJoystickPressed = false;
boolean RadioInContact = false;
byte Throttle = 127;
int JoystickForwardBack = 0;
int JoystickLeftRight = 0;

#define RadioMISO 12
#define RadioMOSI 11
#define RadioSCK 13

//CE is 8 normally but it's 7 on the receiver board for whatever reason
#define RadioCE 7
#define RadioCSN 8

BFFRadioReceiver radio(RadioMISO, RadioMOSI, RadioSCK, RadioCE, RadioCSN);

void setup(){
  Serial.begin(9600);
  radio.init(&ButtonAPressed, &ButtonBPressed, &ButtonJoystickPressed, &RadioInContact,
             &Throttle, &JoystickForwardBack, &JoystickLeftRight);
  
  Serial.println("Beginning ... "); 
}

void loop(){
  int rad = radio.update();
  
  //Serial.println(rad);
  Serial.print(RadioInContact);
  
  Serial.print(" | A: ");
  Serial.print(ButtonAPressed);
  Serial.print(" B: ");
  Serial.print(ButtonBPressed);
  Serial.print(" J: ");
  Serial.print(ButtonJoystickPressed);
  
  Serial.print(" | Throttle: ");
  Serial.print(Throttle);
  Serial.print(" X: ");
  Serial.print(JoystickLeftRight);
  Serial.print(" Y: ");
  Serial.println(JoystickForwardBack);
  
  delay(400);
 }
