#include <SDL/SDL_mixer.h>

#ifndef OPERA_EVENT
#define OPERA_EVENT

struct eventConfig
{
	int bitAnd;
	int bitNot;
	int baseVolume;
        int framesModulus;
	int framesCooldown;
	int scaleConstant;
};

class operaEvent
{
public:
	 operaEvent(const char*); //takes a path to a config as an argument
	~operaEvent();
	eventConfig parseConfig(const char*); //from config named
//	Mix_Chunk loadOgg(); 
//	void check(int); //send it the signal bitmask, maybe activate
//	void play();
//      void grow();	
//	void decay();
private:
	int framesAgoPlayed;
	int framesAgoActivated;
	eventConfig config;

};

#endif
