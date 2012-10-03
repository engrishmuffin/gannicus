#include "opera.h"
#include <SDL/SDL_mixer.h>

operaEvent::operaEvent(resourceFolder, resourceName, defaultVolume, frames, rateModulus, decayFrames)
{
	//eventResource == the folder to get ogg from;
}
operaEvent::~operaEvent(){}

void operaEvent::loadOgg(){}

void operaEvent::beat()
{
	
	activate();
	play();
	decay();
}
bool operaEvent::eventConditions()
{
return 0; //the unspecified event never plays
}
void operaEvent::activate()
{
	if !eventConditions() return;
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
