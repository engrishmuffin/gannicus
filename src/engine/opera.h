#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#ifndef OPERA_INCLUDED
#define OPERA_INCLUDED
struct note {
	int octave;
	int accidental;
	int degree;
	int velocity;
	int duration;
//	int modulation;
};

class sample {
public:
	ALenum format;
	ALsizei size;
	ALsizei freq;
	ALboolean loop;
	ALvoid* data;
	sample(string);
};

class soundScape {
public:
	virtual void init();
	virtual ~soundScape();
};
#endif
