#ifndef OPERA_EVENTS
#define OPERA_EVENTS
#include "opera.h"

class operaEvent
{
public:
	 operaEvent();
	~operaEvent(); //make sure silent
	void loadOgg(); //load the file
	void beat(); //things that happen every frame: fire, play, decay
	bool eventTrigger(); //function that varies among events, and checks _something_ to determine whether the event activates
	void activate(); //start, or amplify/sustain
	void play(); //start playing IF the frame is the correct number, AND recently fired
	void decay(); //decay by half or just stop if under a threshold AND last_fired > threshold
private:
	float currentVolume; //as a portion of the total
	float thresholdVolume; //to be considered active
	float defaultVolume; //when a fresh instance of the sound starts
	int frameDuration; //number of frames the sound occupies
	int rateModulus; //can only play on currentFrame % radeModulus
	int lastFired; //checked by play and decay, incremented by decay, zeroed by fire
	int decayFrames; //checked by decay, compared to lastFired. 0 == never, otherwise == halflife
	char* resourceFolder; //folder to look for e.g. character sounds, etc
	char* eventName; //filename of .ogg file associated with the event
}

#endif