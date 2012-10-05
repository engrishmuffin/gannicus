#include "opera.h"
#include "operaEvent.h"
#include <SDL/SDL_mixer.h>
#include <libconfig.h>


opera::opera(char* character1, char* character2, char* stage, char* narrator)
{ 
	Mix_OpenAudio(44100, AUDIO_S16, 2, 2048);
	int numEvents = getCharEvents(character1) + getCharEvents(character2) + getStageEvents(stage) + getAnnouncerEvents(narrator);
	Mix_AllocateChannels(numEvents);
}

opera::~opera()
{
	Mix_CloseAudio();
}

int opera::getCharEvents(char* characterName)
{
	//do the same thing as getStageEvents, but for characters
}

int opera::getStageEvents(char* stageName)
{
	char masterConfigPath[200];
       	sprintf (masterConfigPath, "resources/stages/%s/events.ocfg", stageName);
	config_t stageEvents;
	config_init(&stageEvents);
	if (config_read_file(&stageEvents, masterConfigPath))
	{
		//look for the configs named in events.ocfg
		//generate stage events
		//return them or assign variables to them or something!?
	}
}

int opera::getAnnouncerEvents(char* announcerName)
{
}

void opera::beat()
{	
}

