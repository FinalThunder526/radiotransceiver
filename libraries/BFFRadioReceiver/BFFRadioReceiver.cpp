/*
BFFRadioReceiver.cpp
Margaret Robinson, Sarang Joshi
24 April 2014
*/

#include "BFFRadioReceiver.h"
#include "Arduino.h"
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

/*
Hard-coded pins:
MOSI 11
MISO 12
SCK 13
*/

// Constructs the BFFRadioReceiver object given the CE and CSN pins, and the receiving address.
BFFRadioReceiver :: BFFRadioReceiver(int ce, int csn, char * raddr)
{
	// Standard Mirf setup
	Mirf.spi = &MirfHardwareSpi;
  	Mirf.init();
  
	Mirf.payload = 4;
	
	// User-set values
	Mirf.cePin = ce;
	Mirf.csnPin = csn;
	Mirf.setRADDR((byte *)raddr);
	
	// Finishing up
	Mirf.config();
}

// Initializes pointer variables for all the receivable values.
void BFFRadioReceiver::init(boolean* a, boolean* b, boolean* j, boolean* contact, byte* throttle, int* x, int* y)
{
	_a = a;
	_b = b;
	_j = j;
	_contact = contact;
	_throttle = throttle;
	_y = y;
	_x = x;
}

// Returns the delay and receives data.
int BFFRadioReceiver::update()
{
	unsigned long time = millis();
  	boolean timeout = false;
  
  	Mirf.setTADDR((byte *)"serv1");
  
  	while(Mirf.isSending()){
  	}
  	while(!Mirf.dataReady()){
    		if ( ( millis() - time ) > 1000 ) {
      		timeout = true;
			*_contact = false;
			break;
    		}
  	}
  	if(!timeout) {
  		Mirf.getData(_data);

		//// PARSING ALGORITHM ////
		boolean xsign, ysign;

		// The 0th byte contains:
		// The sign of the x and y values for the joystick (positive/negative)
		xsign = (_data[0] % 32) / 16;
  		ysign = (_data[0] % 16) / 8;
		// The values of the buttons
		// j,
  		*_j = (_data[0] % 8) / 4;
		// b, and
  		*_b = (_data[0] % 4) / 2;
		// a.
  		*_a = (_data[0] % 2);
		
		// The 1st byte contains y value information.
		if(ysign)
			*_y = _data[1];
		else
			*_y = -1 * _data[1];
		
		// The 2nd byte contains x value information.
		if(xsign)
			*_x = _data[2];
		else
			*_x = -1 * _data[2];

		// The 3rd byte contains throttle value information.
		*_throttle = _data[3];

		// Since data has been received, we are still in contact.
		*_contact = true;
	}

	// This represents the time delay between time received and time calculated.
	return millis() - time;

}

String BFFRadioReceiver::print()
{
	String str = "Not connected.";
	
	if (*_contact)
	{
		str = "| A: ";
		str.concat(*_a);
		str.concat(" B: ");
		str.concat(*_b);
		str.concat(" J: ");
		str.concat(*_j);
		str.concat(" | Throttle: ");
		str.concat(*_throttle);
		str.concat(" X: ");
		str.concat(*_x);
		str.concat(" Y: ");
		str.concat(*_y);
		str.concat(" |\n");
	}
	return str;
}