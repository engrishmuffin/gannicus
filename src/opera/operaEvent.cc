#include "operaEvent.h"
#include <fstream>
#include <libconfig.h>

operaEvent::operaEvent(const char* eventPath, int channel)
{
	
	loadConfig(eventPath);
//	eventSample = loadOgg();
//	Mix_Volume(channel, baseVolume);
	eventChannel = channel;
	framesAgoPlayed = 0;
	framesAgoChecked = 0;

}

operaEvent::~operaEvent()
{
//	Mix_HaltChannel(channel);
}

void operaEvent::loadConfig(const char* eventPath)
{
	std::ifstream in(eventPath);
	config_t event;
	config_init(&event);
	config_read_file(&event, eventPath);
	config_lookup_int(&event, "bitAnd", &bitAnd);
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
//if framesAgoPlayed >= framesHalflife, grow.
}

void operaEvent::decay()
{
//if framesAgoActivated >= framesHalflife, shrink.
framesAgoPlayed++;
framesAgoActivated++;
}
*/

