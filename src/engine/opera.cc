#include "opera.h"
using std::string;
void soundScape::init()
{
	alutInit(0, nullptr);
	alGetError();
}

sample::sample(string a)
{
	alutLoadWAVFile(a.c_str(), &format, &data, &size, &freq, &loop);
	if ((error = alGetError()) != AL_NO_ERROR) cout << "Eu dunne fukt up\n";
}

soundScape::~soundScape()
{
	//alDeleteSources(NUM_SOURCES, source);
	//alDeleteBuffers(NUM_BUFFERS, buffers);
	alutExit();
}
