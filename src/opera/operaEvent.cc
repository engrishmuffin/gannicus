#include "operaEvent.h"
#include <fstream>


operaEvent::operaEvent(const char* eventPath)
{
	
	config = parseConfig(eventPath);
//	eventSample = loadOgg();
//	Mix_Volume(channel, baseVolume);
	framesAgoPlayed = 0;
	framesAgoActivated = 0;

}

operaEvent::~operaEvent()
{
//	Mix_HaltChannel(channel);
}


eventConfig operaEvent::parseConfig(const char* eventPath)
{
//	std::ifstream in(eventPath);
	eventConfig event;
	return event;
}

/*
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
	Mix_PlayChannel(channel, eventSample, 0);
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
*/

