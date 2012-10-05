#include "operaEvent.h"
#include <fstream>
#include <libconfig.h>

operaEvent::operaEvent(const char* eventPath, int channel)
{
/**
 * eventPath is the relative path to a pair of .ogg and .config files with the same name omitting extension.
 * This constructor will first look for the config before loading any ogg files.
 *
 * channel is an arbitrary channel, which will be assigned by the opera class.
 **/


	if (loadConfig(eventPath))
	{
		loadOgg(eventPath);
		eventChannel = channel;
		framesAgoPlayed = 0;
		framesAgoChecked = 0;
		Mix_Volume(eventChannel, baseVolume);
	}
}

operaEvent::~operaEvent()
{
//	Mix_HaltChannel(channel);
}

bool operaEvent::loadConfig(const char* eventPath)
{
	char configPath[200];
	sprintf(configPath, "%s.ocfg", eventPath);
	config_t event;
	config_init(&event);
	if (config_read_file(&event, configPath))
	{
		config_lookup_int(&event, "bitAnd", &bitAnd);
		config_lookup_int(&event, "bitNot", &bitNot);
		config_lookup_int(&event, "baseVolume", &baseVolume);
		config_lookup_int(&event, "framesModulus", &framesModulus);
		config_lookup_int(&event, "framesCooldown", &framesCooldown);
		config_lookup_int(&event, "framesHalflife", &framesCooldown);
		config_destroy(&event);
		return 1;
	}
	else
	{
		//could output error with config_error_{file,line,text}
		return 0;
	}
}



void operaEvent::loadOgg(const char* eventPath)
{
	char oggPath[200];
	sprintf(oggPath, "%s.ogg", eventPath);
	oggSound = Mix_LoadWAV(oggPath);
}

/*
void operaEvent::check(int condition)
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
*/
void operaEvent::play()
{
	Mix_PlayChannel(eventChannel, oggSound, 0);
}

/*
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

