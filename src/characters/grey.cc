#include "grey.h"
grey::grey(){
	head = new actionTrie;
	airHead = new actionTrie;
	meter = new int[5];
	build("Grey", "Grey");
	noirActivate = neutral;
}

int grey::takeHit(action *& cMove, hStat & s, int blockType, int &frame, int &connectFlag, int &hitFlag, int &hitType, bool &aerial)
{
	int freeze = character::takeHit(cMove, s, blockType, frame, connectFlag, hitFlag, blockType, aerial);
	if(hitType == -1) meter[4] += 205;
	if(meter[4] >= 1020){
		meter[4] = 1023;
		freeze = 0;
		cMove = noirActivate;
	}
	return freeze;
}

void grey::tick()
{
	if(meter[4] > 0) meter[4]--;
}

void grey::init(action *& cMove)
{
	meter[4] = 0;
	character::init(cMove);
}
