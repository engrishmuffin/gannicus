#include "opera.h"
#include "operaEvent.h"
#include <SDL/SDL_mixer.h>
#include <libconfig.h>


opera::opera(char* character1, char* character2, char* stage, char* narrator)
{ 
	baseVolume = 32;
	Mix_OpenAudio(44100, AUDIO_S16, 2, 2048);

	

	Mix_AllocateChannels(numEvents);
}

opera::~opera()
{
	Mix_CloseAudio();
}

void opera::getCharEvents()
{
}

void opera::getStageEvents()
{
	char* masterConfigPath[200];
       	sprintf (masterConfigPath, "resources/stages/%i/events.ocfg");
	config_t stageEvents;
	config_init(&stageEvents);
	if (config_read_file())
}

void opera::getAnnouncerEvents()
{
}

void opera::beat()
{	
}

