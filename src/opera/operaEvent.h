#include <SDL/SDL_mixer.h>
#include "../engine/masks.h"
#ifndef OPERA_EVENT
#define OPERA_EVENT



class operaEvent
{
public:
	operaEvent(const char*, int); //takes a path to a config and a channel
       ~operaEvent();
	bool loadConfig(const char*); 
	void loadOgg(const char*); 
	void check(scoreField, int);
	void play();
        void grow();	
	void decay();
	void age();
private:
	scoreField scoreMask;
	int eventChannel;
	int baseVolume;
	int tempVolume;
	int framesModulus; //period of potential recurrence
	int framesCooldown; //period before the sound can play again
	int framesGrowth; //period for growth or decay to happen
	int framesAgoPlayed; 
	int framesAgoChecked;
	int framesAgoGrew;
	int growthNum;
	int growthDenom;
	Mix_Chunk* oggSound;
};

#endif
