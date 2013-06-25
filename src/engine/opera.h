#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <string>
using std::string;
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
	ALuint buffer;
	ALuint operator()();
	sample(const sample&);
	sample() {}
	sample(string);
};

class soundScape {
public:
	ALuint source[16];
	virtual void play(int);
	virtual void init();
	virtual ~soundScape();
};
#endif
