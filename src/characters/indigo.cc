#include "indigo.h"
indigo::indigo(){
	head = new actionTrie;
	airHead = new actionTrie;
	meter = new int[3];
	build("indigo", "indigo");
}
