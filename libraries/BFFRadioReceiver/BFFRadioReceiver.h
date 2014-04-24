#ifndef RadioReceiver_h
#define RadioReceiver_h

#include "Arduino.h"

class RadioReceiver
{
public:
	RadioReceiver(int newChannel);
	void setup();
	bool getA();
	bool getB();
	bool getJ();
	int getUpDown();
	int getRightLeft();
	int getThrottle();
	bool update();

private:
	int _channel;
	bool _a, _b, _j;
	bool _ud, _rl;
	byte _data[4];
};

#endif