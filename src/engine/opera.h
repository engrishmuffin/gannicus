#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <string>
using std::string;
#ifndef OPERA_INCLUDED
#define OPERA_INCLUDED

enum Degree {Tonic, Supertonic, Mediant, Subdominant, Dominant, Submediant, LeadingTone};


struct note {
	int octave;
	int accidental;
    Degree degree;
	unsigned int velocity;
	size_t duration;
//	int modulation;
};

class sample {
public:
	ALuint buffer;
	ALuint operator()();
	sample(string);
};

class soundScape {
public:
	virtual void init();
	virtual ~soundScape();
};

class voice {
    sample attack, sustain, decay; //I'll try to make attack n / 60 seconds, sustain 1/60 second, and decay arbitrary length in general, so they map nicely to frames.
public: 
    voice(sample, sample, sample); //attack, sustain, decay
    void play(int, int); //Attack, then begin sustain and keep sustaining.
                         //Arguments are volume and duration

    void stop(); //Stop even if still decaying.
    ~voice();
    
#endif
