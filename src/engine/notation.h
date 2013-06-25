#include<array>
#include<bitset>

#ifndef ___notation
#define ___notation

using std::array;
using std::bitset;

enum diatonic {Tonic, Supertonic, Mediant, Subdominant, 
               Dominant, Submediant, Leading, DiatonicDegrees};

enum chromatic {Cr0,Cr1,Cr2,Cr3,Cr4,Cr5,Cr6,Cr7,
                     Cr8,Cr9,Cr10,Cr11,ChromaticOctave};

enum accidental {DoubleFlat=-2, Flat, Neutral, Sharp, DoubleSharp};

typedef array <chromatic, DiatonicDegrees> scale;

struct note
{
	accidental a;
    diatonic d;
    size_t octave; //Octave is between like, 0 and 5
	size_t dynamic; //I think we should use a narrow range of "dynamics" that get applied to overall volume at a different step, e.g. dynamic is probably between like, 0 and 5
	size_t duration; //In frames
};

template <size_t L> class phrase : array<note, L> {};

template <size_t S, size_t L> class rhythm : array<bitset<S>, L> {};

#endif
