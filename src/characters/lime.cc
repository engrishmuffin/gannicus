#include "lime.h"
lime::lime(){
	head = new actionTrie;
	airHead = new actionTrie;
	meter = new int[3];
	build("lime", "lime");
}
