#ifndef GENERIC_INCLUDED
#define GENERIC_INCLUDED
#include "../engine/character.h"
class cyan : public character {
public:
	cyan();
};

class blink : public action {
public:
//	virtual bool cancel(action*, int&, int&); //Cancel allowed activate. Essentially: is action Lvalue allowed given the current state of action Rvalue?

};
#endif
