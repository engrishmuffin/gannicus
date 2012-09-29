#include "genericCharacter.h"
genericCharacter::genericCharacter(){
	head = new actionTrie;
	airHead = new actionTrie;
	meter = new int[3];
	build("genericCharacter", "genericCharacter");
}
