#include "blue.h"
blue::blue(){
	head = new actionTrie;
	airHead = new actionTrie;
	meter = new int[3];
	build("Blue", "Blue");
}
