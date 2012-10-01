#include "cyan.h"
cyan::cyan(){
	head = new actionTrie;
	airHead = new actionTrie;
	meter = new int[4];
	build("cyan", "cyan");
}

void blink::execute(action * last, int *& resource, int &f, int &c, int &h)
{
	armorCounter = 0;
	resource[3] -= 5 * 60;
	resource[0] -= cost;
	cover = last;
	currentFrame = f;
	connectFlag = c;
	hitFlag = h;
	f = 0;
	c = 0;
	h = 0;
}
