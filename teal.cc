#include "teal.h"
teal::teal(){
	for(int i = 0; i < 4; i++){
		head[i] = new actionTrie;
		airHead[i] = new actionTrie;
	}
	meter = new int[4];
	build("Name", "Name");
	dFlag = 1;
}

teal::~teal()
	//Character destructor. Might not need this if we aren't working with any dynamic memory, but it might be worthwhile to have.
{
	for(int i = 0; i < 4; i++){
		delete head[i];
		delete airHead[i];
		delete neutral[i];
		delete crouch[i];
		delete reel[i];
		delete untech[i];
		delete crouchReel[i];
		delete down[i];
		if(i < 3){
			delete crouchBlock[i];
			delete standBlock[i];
			delete airBlock[i];
		}
	}
	delete [] meter;
	if(name) delete [] name;
}

/*Here begin action functions. Actually contemplating making this a class instead, but this might be simpler for now*/
