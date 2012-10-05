#include "operaEvent.h"
#include <libconfig.h>

operaEvent::operaEvent(const char* eventPath, int channel)
{
/**
 * eventPath is the relative path to a pair of .ogg and .ocfg files with the same name omitting extension.
 * This constructor will first look for the config before loading any ogg files.
 *
 * channel is an arbitrary channel, which will be assigned by the opera class.
 **/

	growthNum = 2;
	growthDenom = 1;
	if (loadConfig(eventPath))
	{
		loadOgg(eventPath);
		eventChannel = channel;
		tempVolume = baseVolume;
	}
}

operaEvent::~operaEvent()
{
	Mix_HaltChannel(eventChannel);
	Mix_FreeChunk(oggSound);
	oggSound = NULL;
}


bool operaEvent::loadConfig(const char* eventPath)
{
	char configPath[200];
	sprintf(configPath, "%s.ocfg", eventPath);
	config_t event;
	config_init(&event);
	if (config_read_file(&event, configPath))
	{
		int tempScore;
		config_lookup_int(&event, "scoreMask", &tempScore);
		scoreMask.i = tempScore;
		config_lookup_int(&event, "baseVolume", &baseVolume);
		config_lookup_int(&event, "framesModulus", &framesModulus);
		config_lookup_int(&event, "framesCooldown", &framesCooldown);
		config_lookup_int(&event, "framesGrowth", &framesCooldown);
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


void operaEvent::check(scoreField condition, int elapsedFrames)
{
	
	if (condition.i ==  scoreMask.i)
	{
		if (framesAgoPlayed >= framesCooldown)
		{
			if (elapsedFrames % framesModulus)
		       		play();
		}
		if (framesAgoChecked <= framesCooldown)
		{
			if (framesAgoPlayed && !(framesAgoPlayed % framesGrowth))
				grow();
		}
		framesAgoChecked = 0;
	}
	if (framesAgoChecked && !(framesAgoChecked % framesGrowth)) 
		decay();
	age();
}

void operaEvent::play()
{
	framesAgoPlayed = 0;
	if (framesAgoChecked >= framesAgoPlayed)
		tempVolume = baseVolume;
	Mix_Volume(eventChannel, tempVolume);
	Mix_PlayChannel(eventChannel, oggSound, 0);
}


void operaEvent::grow()
{
	tempVolume *= growthNum;
	tempVolume /= growthDenom;
}

void operaEvent::decay()
{
	tempVolume *= growthDenom;
	tempVolume /= growthNum;
}

void operaEvent::age()
{	
	framesAgoPlayed++;
	framesAgoChecked++;
}
