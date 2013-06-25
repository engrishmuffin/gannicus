#include "opera.h"
#include <iostream>
using std::cout;
void soundScape::init()
{
	alutInit(0, nullptr);
	alGetError();
}

sample::sample(string a)
{
	buffer = alutCreateBufferFromFile (a.c_str());
}

ALuint sample::operator()()
{
	return buffer;
}

soundScape::~soundScape()
{
	//alDeleteSources(NUM_SOURCES, source);
	//alDeleteBuffers(NUM_BUFFERS, buffers);
	alutExit();
}
