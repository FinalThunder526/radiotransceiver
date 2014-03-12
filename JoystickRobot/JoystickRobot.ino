#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

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
  
  delay(1000);
} 
  
  
  
