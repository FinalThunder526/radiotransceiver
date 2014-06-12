/*
BFFRadioReceiver.h
Margaret Robinson, Sarang Joshi
24 April 2014
*/

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
	BFFRadioReceiver(int ce, int csn, char* addr);
	void init(boolean* a, boolean* b, boolean* j, boolean* contact, byte* throttle, int* x, int* y);
	int update();
	String print();

private:
	boolean * _contact;
	boolean * _a, * _b, * _j;
	byte * _throttle;
	int * _x, * _y;
	byte _data[4];
};

#endif