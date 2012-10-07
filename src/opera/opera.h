#include "operaEvent.h"
#include <vector>

#ifndef OPERA
#define OPERA

class opera
{
public:
	 opera();
	~opera(); 
	void loadEvents(char*);
	void beat(scoreField, int);
	std::vector<operaEvent*> allEvents;

};

#endif 
