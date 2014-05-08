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
int JoystickForwardBack = 0;
int JoystickLeftRight = 0;

#define RadioMISO 12
#define RadioMOSI 11
#define RadioSCK 13
#define RadioCE 8
#define RadioCSN 7

#define ServoPinL 9
#define ServoPinR 10
Servo servoL, servoR;

BFFRadioReceiver radio(RadioMISO, RadioMOSI, RadioSCK, RadioCE, RadioCSN);

void setup(){
  Serial.begin(9600);
  radio.init(&ButtonAPressed, &ButtonBPressed, &ButtonJoystickPressed, &RadioInContact,
             &Throttle, &JoystickForwardBack, &JoystickLeftRight);
  
  servoL.attach(ServoPinL, 1000, 2000);
  servoR.attach(ServoPinR, 1000, 2000);
  
  Serial.println("Beginning ... "); 
}

void loop(){
  int rad = radio.update();
  /*Serial.print(rad);
  
  Serial.print(" || Throttle: ");
  Serial.print(Throttle);
  Serial.print(" X: ");
  Serial.print(JoystickLeftRight);
  Serial.print(" Y: ");
  Serial.println(JoystickForwardBack); */
  
  int modL = 1;
  int modR = 1;
  if(JoystickLeftRight > 50)
    modR = -1;
  if(JoystickLeftRight < -50)
    modL = -1;
  
  int valL = map(JoystickForwardBack, -255, 255, 1000, 2000) * modL;
  int valR = map(JoystickForwardBack, -255, 255, 1000, 2000) * modR;
  
  servoL.writeMicroseconds(valL);
  servoR.writeMicroseconds(valR);
  
  Serial.print("L: ");
  Serial.print(valL);
  Serial.print(" | R: ");
  Serial.println(valR);
  
  //delay(200);
 }
