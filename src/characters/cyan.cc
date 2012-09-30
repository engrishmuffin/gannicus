#include "cyan.h"
cyan::cyan(){
	head = new actionTrie;
	airHead = new actionTrie;
	meter = new int[3];
	build("cyan", "cyan");
}
