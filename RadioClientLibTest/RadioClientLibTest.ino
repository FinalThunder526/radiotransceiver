#include <RadioReceiver.h>

RadioReceiver receiver(10);

void setup() {
  
}

void loop() {
  int x;
  receiver.getA();
  Serial.println(x);
}
