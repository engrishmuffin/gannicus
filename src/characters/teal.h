#ifndef TEAL_INCLUDED
#define TEAL_INCLUDED
#include "yellow.h"
class shift : virtual public special {
public:
	shift() {}
	~shift();
	shift(const char *);
	virtual void zero();
	virtual bool setParameter(char*);
	virtual void execute(action *, int *&);
	int stance;
};

class teal : public character {
public:
	teal();
	~teal();
	int * generateMeter();
	void build(const char*, const char*);
	void sortMove(action*, char*);
	void neutralize(action *&, bool, int *&);
	int checkBlocking(action *&, int[], int&, int&, bool, int*);
	virtual action * createMove(char*);
	void resetAirOptions(int *&);
	int comboState(action *);
	void init(int *&);
	int takeHit(action *&, hStat&, int, int&, int&, int&, int&, bool&, int *&);
	action * hook(int[40], int, int, int*, int[5], bool[5], action *, SDL_Rect&, int&, int&, bool);

	actionTrie * head[4];
	actionTrie * airHead[4];
	action * neutral[4];
	action * airNeutral[4];
	action * crouch[4];
	hitstun * reel[4];
	untechState * untech[4];
	airLooping * fall[4];
	utility * down[4];
	hitstun * crouchReel[4];
	hitstun * crouchBlock[3];
	hitstun * standBlock[3];
	hitstun * airBlock[3];
	shift * throwBreak;
};
#endif
