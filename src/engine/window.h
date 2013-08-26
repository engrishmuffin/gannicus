#include "shader.h"
#include <SDL/SDL.h>
#ifndef ___window
#define ___window

class window{
public:
	window();
	virtual bool initShaders();
	virtual bool screenInit();
	virtual void setLighting();
	GLuint prog;
	SDL_Surface * screen;
	vector <shader> currentShaders;
	int displayMode;
	int h, w;
};
#endif
