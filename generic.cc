#include "generic.h"
generic::generic(){
	head = new actionTrie;
	airHead = new actionTrie;
	meter = new int[3];
	build("generic", "generic");
}
