#include "opera.h"
#include <SDL/SDL_mixer.h>


opera::opera()
{	
	//tare the current frame so that "number of frames elapsed" can be tracked
	//load each event
	currentVolume = defaultVolume;
}

opera::~opera()
{
}


void opera::beat()
{	
	listen(p1Score, p2Score);
	//for i in events
	//	event.beat();
}

void opera::listen(operaScore, operaScore)
{
	//Take in an operaSignal.
	//Check if even
	//Play the appropriate operaEvent
}

float opera::volume(){return currentVolume;}
//float->currentVolume with bounds
float opera::volume(newVolume){
	if newVolume < maxVolume {
		if newVolume > minVolume {
			currentVolume = newVolume;
		} else currentVolume = minVolume;
	} else newVolume = maxVolume;

