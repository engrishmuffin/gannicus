#include "opera.h"
#include <SDL/SDL_mixer.h>

operaEvent::operaEvent(resourceFolder, resourceName, baseVolume, framesModulus, framesCooldown, framesCoefficient)
{
	
	eventSample = loadOgg();
	eventSample.volume = baseVolume;
	framesAgoPlayed = 0;
	framesAgoActivated = 0;


}
operaEvent::~operaEvent(){}

Mix_Chunk operaEvent::loadOgg()
{
	char resourcePath[200];
	sprintf(resourcePath, "%i/%i.ogg", oggFolder, oggName);
	return Mix_LoadWAV(resourcePath);
}


void operaEvent::activate(condition)
{
	if !condition return;
	else 
	{
		if (framesAgoPlayed >= framesCooldown) && !(elapsedFrames % framesModulus)
		       	play();
		if (framesAgoActivated <= framesCooldown)
			grow();
	}
	decay();
//if lastFired < frames, increase volume
//otherwise set volume to defaultVolume
//zero lastFired
}
void operaEvent::play()
{
	
}

void operaEvent::grow()
{
//increase volume at a rate proportional to framesCoefficient.
}

void operaEvent::decay()
{
//decrease volume at a rate proportional to framesAgoActivated and framesCoefficient
framesAgoPlayed++;
framesAgoActivated++;
}
