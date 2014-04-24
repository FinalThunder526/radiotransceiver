#include "RadioReceiver.h"
#include "Arduino.h"
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

RadioReceiver :: RadioReceiver(int newChannel)
{
	_channel = newChannel;
}

void RadioReceiver::setup()
{

}
bool RadioReceiver::getA() 
{
	return _a;
}
bool RadioReceiver::getB() {
	return _b;
}
bool RadioReceiver::getJ()
{
	return _j;
}
int RadioReceiver::getUpDown()
{

}
int RadioReceiver::getRightLeft()
{

}
int RadioReceiver::getThrottle()
{

}

bool RadioReceiver::update()
{

}