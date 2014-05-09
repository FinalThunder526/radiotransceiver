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

BFFRadioReceiver radio(RadioMISO, RadioMOSI, RadioSCK, RadioCE, RadioCSN);

void setup(){
  Serial.begin(9600);
  radio.init(&ButtonAPressed, &ButtonBPressed, &ButtonJoystickPressed, &RadioInContact,
             &Throttle, &JoystickY, &JoystickX);
  
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
  Serial.print(JoystickX);
  Serial.print(" Y: ");
  Serial.println(JoystickY); */
  
  // R IS REVERSED.
  int valL = 0, valR = 0;
  double k = 2.773;
  valL = (int) ((k / sqrt(2)) * (JoystickX + JoystickY));
  valR = (int) ((k / sqrt(2)) * (JoystickX - JoystickY));
  		
  if(valL > 500) valL = 500;
  if(valR > 500) valR = 500;
		
  servoL.writeMicroseconds(valL + 1500);
  servoR.writeMicroseconds(valR + 1500);
  
  Serial.print("L: ");
  Serial.print(valL);
  Serial.print(", R: ");
  Serial.println(valR);
  
  //delay(200);
 }
