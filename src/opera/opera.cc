#include "opera.h"
#include "operaEvent.h"
#include <SDL/SDL_mixer.h>
#include <fstream>
#include <string>




opera::opera()
{ 
	charEvents = operaEvent[16];
	charEvents = operaEventParse("resources/operaChars.yaml");
	stageEvents = parseEvents("resources/operaStage.yaml");
	numEvents = charEvents.number + stageEvents.number;
	Mix_OpenAudio(44100, AUDIO_S16, 2, 2048);
	Mix_AllocateChannels(numEvents);
}

opera::~opera()
{
	Mix_CloseAudio();
}




void opera::beat()
{	
}
