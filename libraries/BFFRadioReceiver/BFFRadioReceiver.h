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
	BFFRadioReceiver(int ce, int csn, int payload, char* addr);
	void init(boolean* a, boolean* b, boolean* j, boolean* contact, byte* throttle, int* x, int* y);
	int update();

private:
	boolean * _contact, * _payload;
	boolean * _a, * _b, * _j;
	byte * _throttle;
	int * _x, * _y;
	byte _data[4];
};

#endif