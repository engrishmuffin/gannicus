#include <SDL/SDL_mixer.h>

#ifndef OPERA_EVENT
#define OPERA_EVENT

class operaEvent
{
public:
	operaEvent(const char*, int); //takes a path to a config and a channel
       ~operaEvent();
	void loadConfig(const char*); 
//	Mix_Chunk loadOgg(); 
//	void check(int);
//	void play();
//      void grow();	
//	void decay();
	int bitAnd;
private:
	int bitNot;
	int eventChannel;
	int baseVolume;
	int framesModulus; //period of potential recurrence
	int framesCooldown; //period before the sound can play again
	int framesHalflife; //period for growth or decay to happen
	int framesAgoPlayed; 
	int framesAgoChecked;

};

#endif
