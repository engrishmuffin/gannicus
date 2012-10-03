#include "opera.h"
#include <SDL/SDL_mixer.h>


opera::opera()
{ 
	p1ambience = new operaEvent();
}

opera::~opera()
{
}


void opera::beat()
{	
	listen(p1Score, p2Score);
	//for i in events
	//	event.beat();
	mix();
}

void opera::listen(operaScore, operaScore)
{
	//Take in an operaSignal.
	//Check if even
	//Play the appropriate operaEvent
}

void opera::mix()
{
}

float opera::volume(){return currentVolume;}
//float->currentVolume with bounds
float opera::volume(newVolume){
	if newVolume < maxVolume {
		if newVolume > minVolume {
			currentVolume = newVolume;
		} else currentVolume = minVolume;
	} else newVolume = maxVolume;

