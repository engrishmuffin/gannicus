#include "opera.h"
#include <SDL/SDL_mixer.h>
#include <string>

#ifndef OPERA_EVENTS
#define OPERA_EVENTS


struct operaEventConfig
{
	std::string name;
	int bitAnd;
	int bitNot;
	int baseVolume;
        int framesModulus;
	int framesCooldown;
	int scaleConstant;	
}

class operaEvent
{
public:
	 operaEvent(char*, operaEventConfig);
	~operaEvent();
	Mix_Chunk loadOgg(); 
	void activate(bool);
	void play();
        void grow();	
	void decay();
	std::string name;
	int bitAnd;
	int bitNot;
private:
	int framesAgoPlayed;
	int framesAgoActivated


}

#endif
