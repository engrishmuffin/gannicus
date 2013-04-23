
#include <SDL/SDL.h>

#ifndef ___window
#define ___window

class window{
public:
	window();
	virtual bool screenInit();
	virtual void setLighting();
	SDL_Surface * screen;
	int displayMode;
	int h, w;
};
#endif
