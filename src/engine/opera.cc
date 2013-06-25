#include "opera.h"
void soundScape::init()
{
	alutInit(0, nullptr);
	alGetError();
}

soundScape::~soundScape()
{
	//alDeleteSources(NUM_SOURCES, source);
	//alDeleteBuffers(NUM_BUFFERS, buffers);
	alutExit();
}
