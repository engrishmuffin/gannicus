#include <SDL/SDL.h>
#include "controller.h"
#ifndef HARNESS_INCLUDED
#define HARNESS_INCLUDED
class harness{
public:
	harness();
	void init();
	virtual void readInput();
	virtual void processInput(SDL_Event&);
	bool gameover;
	std::vector<controller*> p;
};
#endif