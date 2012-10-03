#ifndef OPERA_EVENTS
#define OPERA_EVENTS
#include "opera.h"

class operaEvent
{
public:
	 operaEvent(char*, char*, uint8, int, int, int, unsigned int);
	~operaEvent();
	void loadOgg();
	void beat(); //things that happen every frame: fire, play, decay
	void activate(); //start, or amplify/sustain
	void play(); //start playing IF the frame is the correct number, AND recently fired
	void decay(); //decay by half or just stop if under a threshold AND last_fired > threshold
private:
	Mix_Chunk eventSample; 
	int frameDuration; //number of frames the sound occupies
	int rateModulus; //can only play on currentFrame % radeModulus
	int lastFired; //checked by play and decay, incremented by decay, zeroed by fire
	int decayFrames; //checked by decay, compared to lastFired. 0 == never, otherwise == halflife
	int thresholdVolume; //minimum to be considered active
}

#endif
