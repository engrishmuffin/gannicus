#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <string>
#include <vector>
#include <array>
#include "notation.h"

using std::array;
using std::string;
using std::vector;
#ifndef OPERA_INCLUDED
#define OPERA_INCLUDED

class sample {
public:
	ALuint buffer;
	ALuint operator()();
	sample(const sample&);
	sample() {}
	sample(string);
};

class voice {
    sample attack, sustain, decay; //Attack == 1*f, Sustain = n*f length
public: 
    voice(sample, sample, sample); //attack, sustain, decay
    void play(int, int); //Attack, then begin sustain and keep sustaining as long as necessary, then decay.
                         //Arguments are volume and sustain duration
    void stop(); //Stop even if still decaying.
    ~voice();
};

typedef array<voice, ChromaticOctave> vocalRegister;
//A vocal register is all of the samples for chroma within an octave

class vocalFont : vector<vocalRegister>
//A vocalFont is all of the samples for an instrument for various octaves. 
{};
  
class soundScape {
public:
	ALuint source[16];
	virtual void play(int);
	virtual void init();
	virtual ~soundScape();
};
  
#endif
