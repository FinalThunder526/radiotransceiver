#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

boolean a, b, j;
boolean ud, rl;

void setup(){
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  
  Mirf.setRADDR((byte *)"clie1");
  
  Mirf.payload = 4;
  Mirf.config();
  
  Serial.println("Beginning ... "); 
}

void loop(){
  unsigned long time = millis();
  
  byte data[Mirf.payload];
  
  Mirf.setTADDR((byte *)"serv1");
  
  while(Mirf.isSending()){
  }
  Serial.println("Finished sending");
  Serial.println();
  delay(10);
  while(!Mirf.dataReady()){
    //Serial.println("Waiting");
    if ( ( millis() - time ) > 1000 ) {
      Serial.println("Timeout on response from server!");
      return;
    }
  }
  
  Mirf.getData(data);
  
  Serial.print("Ping: ");
  Serial.println((millis() - time));
  
  for(int i = 0; i < Mirf.payload; i++) {
    Serial.print(data[i]);
    Serial.print(" ");
  }
  Serial.println();
  
  decodeByte0(data[0]);
  Serial.print("RL: ");
  Serial.print(rl);
  Serial.print("   UD: ");
  Serial.print(ud);
  Serial.print("   Joybtn: ");
  Serial.print(j);
  Serial.print("   B: ");
  Serial.print(b);
  Serial.print("   A: ");
  Serial.print(a);
  Serial.println();
  
  Serial.print("U/D: ");
  Serial.print(getJoystickValue(data[1], ud));
  Serial.print("   R/L: ");
  Serial.print(getJoystickValue(data[2], rl));
  Serial.print("   Pot: ");
  Serial.print(data[3]);
  Serial.println();
  
  delay(400);
} 

void decodeByte0(byte raw) {
  rl = raw / 16;
  ud = (raw % 16) / 8;
  j = (raw % 8) / 4;
  b = (raw % 4) / 2;
  a = (raw % 2);
}

int getJoystickValue(byte mag, boolean sign) {
  if(sign)
    return mag;
  else
    return mag * -1;
}
