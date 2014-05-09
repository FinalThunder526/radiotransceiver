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

#define ServoPinA 4
#define ServoPinB 5
#define ServoPinC 3
Servo ServoA, ServoB, ServoC; //throttle, joyX, joyY

BFFRadioReceiver radio(RadioMISO, RadioMOSI, RadioSCK, RadioCE, RadioCSN);

void setup(){
  Serial.begin(9600);
  radio.init(&ButtonAPressed, &ButtonBPressed, &ButtonJoystickPressed, &RadioInContact,
             &Throttle, &JoystickY, &JoystickX);
  
  ServoA.attach(ServoPinA, 1000, 2000);
  ServoB.attach(ServoPinB, 1000, 2000);
  ServoC.attach(ServoPinC, 1000, 2000);
  
  pinMode(2, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(A5, OUTPUT);
  
  Serial.println("Beginning ... "); 
}

void loop(){
  int rad = radio.update();
  Serial.println(rad);
  
  Serial.print("A: ");
  Serial.print(ButtonAPressed);
  Serial.print(" B: ");
  Serial.print(ButtonBPressed);
  Serial.print(" J: ");
  Serial.println(ButtonJoystickPressed);
  
  Serial.print("Throttle: ");
  Serial.print(Throttle);
  Serial.print(" X: ");
  Serial.print(JoystickX);
  Serial.print(" Y: ");
  Serial.println(JoystickY);
  
  ServoA.writeMicroseconds(map(Throttle, 0, 255, 1000, 2000));
  ServoB.writeMicroseconds(map(JoystickX, -255, 255, 1000, 2000));
  ServoC.writeMicroseconds(map(JoystickY, -255, 255, 1000, 2000));
  
  digitalWrite(2, RadioInContact); //red
  digitalWrite(9, ButtonAPressed); //blue
  digitalWrite(10, ButtonJoystickPressed); //green
  digitalWrite(A5, ButtonBPressed); //yellow
  
  //delay(200);
 }
