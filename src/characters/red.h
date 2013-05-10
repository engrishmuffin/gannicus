#ifndef RED_INCLUDED
#define RED_INCLUDED
#include "../engine/character.h"
class red : public character{
public:
	red();
	action * createMove(string);
	void tick(vector<int>&);
	vector<int> generateMeter();
	void step(status&, vector<int>&);
	void init(vector<int>&);
	vector<status> temporalBuffer;
	instance * backup;
};

class redCancel : virtual public special{
public:
	redCancel() {}
	~redCancel();
	redCancel(string, string);
	bool check(SDL_Rect&, vector<int>);
	int arbitraryPoll(int, int);
	void execute(action *, status&, vector<int>&);
};

class redSuper : virtual public special{
public:
	redSuper();
	~redSuper();
	redSuper(string d, string f) { build(d,f); }
	int arbitraryPoll(int, int);
};
#endif
