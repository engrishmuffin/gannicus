#include "cyan.h"
cyan::cyan(){
	head = new actionTrie;
	airHead = new actionTrie;
	meter = new int[4];
	build("cyan", "cyan");
}

bool blink::check(SDL_Rect& p, int resource[])
{
	if(resource[3] < 5 * 60) return 0;
	else return action::check(p, resource);
}

void blink::execute(action * last, int *& resource, int &f, int &c, int &h)
{
	resource[3] -= 5 * 60;
	action::execute(last, resource, f, c, h);
}
