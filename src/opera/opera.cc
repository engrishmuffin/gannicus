#include "opera.h"
#include "operaEvent.h"
#include <SDL/SDL_mixer.h>
#include <fstream>

opera::opera()
{
	/**The constructor just opens up the mixer. 
	 * This way, we can potentially load a menu event list during the menu, and others during the game. **/
	Mix_OpenAudio(44100, AUDIO_S16, 2, 2048);
}

opera::~opera()
{
	Mix_CloseAudio();
	//unload all events	
	for(int n = 0; n < allEvents.size(); n++)
	{
		delete allEvents.at(n);
		allEvents.erase(allEvents.begin() + n);
	}

}

void opera::loadEvents(char* folder)
{
	/**loadEvents looks for events.ocfg in folder**/
	char listPath[200];
        sprintf(listPath, "%s/events.ocfg", folder);	
	std::string name;
	std::ifstream list(listPath);
	std::vector<std::string> eventNames;

	while (list >> name) 
	{
		eventNames.push_back(name);
	}
	
	int numEvents = eventNames.size();
	Mix_AllocateChannels(numEvents);
	
	for (int n = 0; n < numEvents; n++)
	{
		char eventPath[200];
		const char* eventName = eventNames.at(n).c_str();
		sprintf(eventPath, "%s/%s.ocfg", folder, eventName);
		operaEvent* eventPtr;
		eventPtr = new operaEvent(eventPath,  n);

	}
}

void opera::beat(scoreField condition, int elapsedFrames)
{	
	for(int n = 0; n < allEvents.size(); n++)
	{
		allEvents.at(n)->check(condition, elapsedFrames);
	}
}

