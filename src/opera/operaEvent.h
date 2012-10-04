#ifndef OPERA_EVENTS
#define OPERA_EVENTS
#include "opera.h"
#include <SDL/SDL_mixer.h>

class operaEvent
{
public:
	 operaEvent(char*, char*, int, int, int, int);
	~operaEvent();
	Mix_Chunk loadOgg(); 
	void activate(bool);
	void play();
        void grow();	
	void decay();
private:
	int framesAgoPlayed;
	int framesAgoActivated
	int thresholdVolume; //minimum to be considered active

}

#endif
