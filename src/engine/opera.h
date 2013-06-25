#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <string>
#include <vector>
#include <array>
using std::array;
using std::string;
using std::vector;
#ifndef OPERA_INCLUDED
#define OPERA_INCLUDED

enum scaleDegree
{
    Tonic, 
    Supertonic, 
    Mediant, 
    Subdominant, 
    Dominant, 
    Submediant, 
    Leading, 
    ScaleDegrees //Count available degrees, == 7
};

enum chromaticScale {Cr0,Cr1,Cr2,Cr3,Cr4,Cr5,Cr6,Cr7,
                     Cr8,Cr9,Cr10,Cr11,ChromaticDegrees};

enum accidental {DoubleFlat=-2, Flat, Neutral, Sharp, DoubleSharp};

typedef array <chromaticScale, ScaleDegrees> scale;

struct note {
	accidental a;
    scaleDegree d;
    size_t octave;
	unsigned int velocity;
	size_t duration;
};

class sample {
public:
	ALuint buffer;
	ALuint operator()();
	sample(const sample&);
	sample() {}
	sample(string);
};

class voice {
    sample attack; //should be 1/60 s
    vector<sample> sustain; //should be n/60 s
    sample decay; //arbitrary length
public: 
    voice(sample, sample, sample); //attack, sustain, decay
    void play(int, int); //Attack, then begin sustain and keep sustaining as long as necessary, then decay.
                         //Arguments are volume and duration
    void stop(); //Stop even if still decaying.
    ~voice();
};

typedef array<voice, ChromaticDegrees> vocalRegister;
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
