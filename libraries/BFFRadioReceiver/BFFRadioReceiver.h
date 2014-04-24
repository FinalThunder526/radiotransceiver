#ifndef RadioReceiver_h
#define RadioReceiver_h

#include "Arduino.h"

class RadioReceiver
{
public:
	RadioReceiver(int newChannel);
	void setup();
	void init(boolean a, boolean b, boolean j, boolean contact, byte throttle, int fb, int rl);
	bool update();

private:
	int _channel;
	bool _a, _b, _j;
	byte _throttle;
	bool _fb, _rl;
	byte _data[4];
};

#endif