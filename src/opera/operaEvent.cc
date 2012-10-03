#include "opera.h"
#include <SDL/SDL_mixer.h>

operaEvent::operaEvent(resourceFolder, resourceName, defaultVolume, frames, rateModulus, decayFrames, conditionBitmask)
{
	
	loadOgg();
	eventSample.volume = defaultVolume;

}
operaEvent::~operaEvent(){}

void operaEvent::loadOgg()
{
	char resourcePath[200];
	sprintf(resourcePath, "%i/%i", resourceFolder, resourceName);
	eventSample = Mix_LoadWAV(resourcePath);
}

void operaEvent::beat()
{
	
	activate();
	play();
	decay();
}



void operaEvent::activate()
{
	if !(SOMETHING) return;
	else
//if lastFired < frames, increase volume
//otherwise set volume to defaultVolume
//zero lastFired
}
void operaEvent::play()
{
//play IF timer % rateModulus AND currentVolume > volumeThreshold AND lastFired > frames
}
void operaEvent::decay()
{
//decrease volume 
//increment lastFired
}
