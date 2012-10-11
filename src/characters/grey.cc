#include "grey.h"
grey::grey(){
	head = new actionTrie;
	airHead = new actionTrie;
	build("Grey", "Grey");
	noirActivate = neutral;
}

int * grey::generateMeter()
{
	int * meter;
	meter = new int[5];
	return meter;
}

int grey::takeHit(action *& cMove, hStat & s, int blockType, int &frame, int &connectFlag, int &hitFlag, int &hitType, bool &aerial, int *& meter)
{
	int freeze = character::takeHit(cMove, s, blockType, frame, connectFlag, hitFlag, hitType, aerial, meter);
	if(hitType == -1) meter[4] += 205;
	if(meter[4] >= 1020){
		meter[4] = 1023;
		freeze = 0;
		cMove = noirActivate;
	}
	return freeze;
}

void grey::tick(int *& meter)
{
	if(meter[4] > 0) meter[4]--;
}

void grey::init(int *& meter)
{
	meter[4] = 0;
	character::init(meter);
}
