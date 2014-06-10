#ifndef BFFRadioReceiver_h
#define BFFRadioReceiver_h

#include "Arduino.h"
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

class BFFRadioReceiver
{
public:
	BFFRadioReceiver(int miso, int mosi, int sck, int ce, int csn, char* addr);
	void init(boolean* a, boolean* b, boolean* j, boolean* contact, byte* throttle, int* fb, int* rl);
	int update();

private:
	boolean * _contact;
	boolean * _a, * _b, * _j;
	byte * _throttle;
	int * _fb, * _rl;
	byte _data[4];
};

#endif