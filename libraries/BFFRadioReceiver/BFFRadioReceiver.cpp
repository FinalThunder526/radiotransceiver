#include "BFFRadioReceiver.h"
#include "Arduino.h"
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

BFFRadioReceiver :: BFFRadioReceiver(int miso, int mosi, int sck, int ce, int csn)
{
	Mirf.spi = &MirfHardwareSpi;
  	Mirf.init();
  
  	Mirf.setRADDR((byte *)"clie1");
  
  	Mirf.payload = 4;
  	Mirf.config();
}

void BFFRadioReceiver::init(boolean* a, boolean* b, boolean* j, boolean* contact, byte* throttle, int* fb, int* rl)
{
	_a = a;
	_b = b;
	_j = j;
	_contact = contact;
	_throttle = throttle;
	_fb = fb;
	_rl = rl;
}

int BFFRadioReceiver::update() //returns the delay I guess? shrug
{
	unsigned long time = millis();
  	boolean timeout = false;
  
  	Mirf.setTADDR((byte *)"serv1");
  
  	while(Mirf.isSending()){
  	}
  	while(!Mirf.dataReady()){
    		if ( ( millis() - time ) > 1000 ) {
      		timeout = true;
		_contact = false;
    		}
  	}
  	if(!timeout) {
  		Mirf.getData(_data);
		boolean rlsign, udsign;

		rlsign = _data[0] / 16;
  		udsign = (_data[0] % 16) / 8;
  		*_j = (_data[0] % 8) / 4;
  		*_b = (_data[0] % 4) / 2;
  		*_a = (_data[0] % 2);

		*_fb = udsign * _data[1];
		*_rl = rlsign * _data[2];
		*_throttle = _data[3];
		*_contact = true;
	}

	return millis() - time;

}