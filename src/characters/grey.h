#ifndef GREY_INCLUDED
#define GREY_INCLUDED
#include "yellow.h"
class grey : public character {
public:
	grey();
	int * generateMeter();
	int takeHit(action *&, hStat&, int, int&, int&, int&, int&, bool&, int*&);
	void tick(int*&);
	void init(int*&);
	action * noirActivate;
};
#endif
