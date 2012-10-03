#include "opera.h"
#include <SDL/SDL_mixer.h>

operaEvent::operaEvent()
{
	currentVolume = 0.0;
}
operaEvent::~operaEvent(){}

void operaEvent::beat()
{
	
	activate();
	play();
	decay();
}
bool operaEvent::eventTrigger()
{
return 0; //the unspecified event never plays
}
void operaEvent::activate()
{
	if !eventTrigger() return;
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
