#ifndef RadioReceiver_h
#define RadioReceiver_h

#include "Arduino.h"

class RadioReceiver
{
public:
	RadioReceiver(int miso, int mosi, int sck, int ce, int csn);
	void init(boolean a, boolean b, boolean j, boolean contact, byte throttle, int fb, int rl);
	int update();

private:
	bool _contact;
	bool _a, _b, _j;
	byte _throttle;
	int _fb, _rl;
	byte _data[Mirf.payload];
};

#endif