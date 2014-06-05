/*
RadioPlaneTest.ino
Margaret Robinson, Sarang Joshi
19 May 2014
*/

#include <BFFRadioReceiver.h>
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#include <Servo.h>

boolean ButtonAPressed = false;
boolean ButtonBPressed = false;
boolean ButtonJoystickPressed = false;
boolean RadioInContact = false;
byte Throttle = 127;
int JoystickY = 0;
int JoystickX = 0;

#define RadioMISO 12
#define RadioMOSI 11
#define RadioSCK 13
#define RadioCE 8
#define RadioCSN 7

#define ServoPinL 9
#define ServoPinR 10
Servo servoL, servoR;

#define MotorPin 5
Servo motor;

BFFRadioReceiver radio(RadioMISO, RadioMOSI, RadioSCK, RadioCE, RadioCSN);

void setup(){
  Serial.begin(9600);
  radio.init(&ButtonAPressed, &ButtonBPressed, &ButtonJoystickPressed, &RadioInContact,
             &Throttle, &JoystickY, &JoystickX);
  
  servoL.attach(ServoPinL, 1000, 2000);
  servoR.attach(ServoPinR, 1000, 2000);
  
  motor.attach(MotorPin);
  
  motor.write(0);
  delay(1500);
  
  Serial.println("Beginning ... "); 
}

void loop(){
  int rad = radio.update();
  
  Serial.println(rad);
  //Serial.println();
  
  int valL = 0, valR = 0;
  double k = 2.773;
  
  valL = (int) ((k / sqrt(2)) * (JoystickX + JoystickY));
  valR = (int) ((k / sqrt(2)) * (JoystickX - JoystickY));
  
  servoL.writeMicroseconds(1500 + valL);
  servoR.writeMicroseconds(1500 + valR);
  
  motor.write(map(Throttle, 0, 255, 0, 180));
  
  Serial.print("X: ");
  Serial.print(JoystickX);
  Serial.print(" Y: ");
  Serial.print(JoystickY);
  Serial.print(" Mot: ");
  Serial.println(Throttle);
  
  
  //delay(200);
 }
