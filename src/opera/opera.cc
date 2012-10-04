#include "opera.h"
#include "operaEvents.h"
#include <SDL/SDL_mixer.h>


opera::opera()
{ 
	Mix_OpenAudio(44100, AUDIO_S16, 2, 2048);

	//Generate operaEvents from configuration.
}

opera::~opera()
{
	Mix_CloseAudio
}


void opera::beat(elapsedFrames)
{	
	listen(p1score, p2score);
	//for i in events
	//	event.beat();
	mix();
}

void opera::listen(p1score, p2score)
{
	//Take in an operaSignal.
	//Check if even
	//Play the appropriate operaEvent
}

void opera::mix()
{
}

