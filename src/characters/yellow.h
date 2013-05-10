#ifndef YELLOW_INCLUDED
#define YELLOW_INCLUDED
#include "../engine/character.h"
class yellow : public character {
public:
	yellow();
	void resetAirOptions(vector<int>&);
	action * createMove(string);
	int takeHit(status&, hStat&, int, int&, vector<int>&);
	void drawMeters(int, int, vector<int>);
	void tick(vector<int>&);
	void init(vector<int>&);
	vector<int> generateMeter();
	void step(status&, vector<int>&);
};

class flashStep : public airMove {
public:
	flashStep();
	flashStep(string, string);
	bool check(SDL_Rect&, vector<int>);
	void execute(action *, status&, vector<int>&);
private:
	int flashMeterCost;
};

class flashSummon : public special {
public:
	flashSummon();
	flashSummon(string, string);
	int arbitraryPoll(int, int);
	bool check(SDL_Rect&, vector<int>);
	void execute(action *, status&, vector<int>&);
	bool setParameter(string);
	virtual void zero();
	void step(vector<int>&, status&);
private:
	bool uFlag;
	int flashMeterGain;
};
#endif
