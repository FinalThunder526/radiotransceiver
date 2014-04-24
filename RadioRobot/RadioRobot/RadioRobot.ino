#include <BFFRadioReceiver.h>

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

#define Radio CE 8
#define Radio CSN 7

void setup(){
  Serial.begin(9600);
  BFFRadioReceiver radio(RadioMISO, RadioMOSI, RadioSCK, RadioCE, RadioCSN);
  radio.init(&ButtonAPressed, &ButtonBPressed, &ButtonJoyStickPressed, &RadioInContact,
             &throttle, &JoyStickForwardBack, &JoyStickLeftRight);
  
  Serial.println("Beginning ... "); 
}

void loop(){
  radio.update();
  
  Serial.print("A: ");
  Serial.print(ButtonAPressed);
  Serial.print(" B: ");
  Serial.print(ButtonBPressed);
  Serial.print(" J: ");
  Serial.println(ButtonJoystickPressed);
  
  Serial.print("Throttle: ");
  Serial.print(Throttle);
  Serial.print(" X: ");
  Serial.print(JoystickLeftRight);
  Serial.print(" Y: ");
  Serial.println(JoystickForwardBack);
  Serial.println();
  
  delay(400);
}
