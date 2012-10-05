#include "operaEvent.h"
#ifndef OPERA
#define OPERA

class opera
{
public:
	 opera(char*,char*,char*,char*);
	~opera(); 
	void beat();
	int getCharEvents(char*);
	int getStageEvents(char*);
	int getAnnouncerEvents(char*);
	operaEvent* char1Events;
	operaEvent* char2Events;
	operaEvent* stageEvents;
	operaEvent* announcerEvents;
};

#endif 
