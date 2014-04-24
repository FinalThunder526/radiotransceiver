#include "BFFRadioReceiver.h"
#include "Arduino.h"
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

RadioReceiver :: RadioReceiver(int miso, int mosi, int sck, int ce, int csn)
{
	Mirf.spi = &MirfHardwareSpi;
  	Mirf.init();
  
  	Mirf.setRADDR((byte *)"clie1");
  
  	Mirf.payload = 4;
  	Mirf.config();
}

void RadioReceiver::init(boolean a, boolean b, boolean j, boolean contact, byte throttle, int fb, int rl)
{
	_a = a;
	_b = b;
	_j = j;
	_contact = contact;
	_throttle = throttle;
	_fb = fb;
	_rl = rl;
}

void RadioReceiver::setup()
{

}

int RadioReceiver::update() //returns the delay I guess? shrug
{
	unsigned long time = millis();
  	boolean timeout = false;

  	byte data[Mirf.payload];
  
  	Mirf.setTADDR((byte *)"serv1");
  
  	while(Mirf.isSending()){
  	}
  	while(!Mirf.dataReady()){
    		if ( ( millis() - time ) > 1000 ) {
      		timeout = true;
    		}
  	}
  	if(!timeout)
  		Mirf.getData(data);

	return millis() - time;

}