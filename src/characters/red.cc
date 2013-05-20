#include "../engine/interface.h"
red::red()
{
	airHead = new actionTrie;
	head = new actionTrie;
	build("Red", "Red");
	backup = new instance;
}

vector<int> red::generateMeter()
{
	vector<int> meter (7);
	return meter;
}

void red::tick(vector<int>& meter)
{
	character::tick(meter);
	if(meter[5] < 540) meter[5]++;
	if(meter[5] < 0) meter[5] = 0;
}

void red::step(status& current, vector<int>& meter)
{
	if(meter[6] > 0) meter[6]--;
	temporalBuffer.push_back(current);
	if(temporalBuffer.size() > 120) temporalBuffer.erase(temporalBuffer.begin());
	character::step(current, meter);
}

void red::init(status& current)
{
	character::init(current);
	current.meter[5] = 540;
	current.meter[6] = 0;
}

action * red::createMove(string key)
{
	tokenizer t(key, " \t-@?_%$!\n");
        t();
	action * m;
	switch(key[0]){
	case '$':
		if(key[1] == '!') m = new redSuper(name, t.current());
		else m = new redCancel(name, t.current());
		break;
	default:
		m = character::createMove(key);
		break;
	}
	if(m->typeKey == '0') m->typeKey = key[0];
	return m;
}

redCancel::redCancel(string dir, string file) 
{
	build(dir, file); 
}

bool redCancel::check(SDL_Rect& p, vector<int> meter)
{
	if(meter[6] > 0) return 0;
	return action::check(p, meter);
}

void redCancel::execute(action * last, status &current, vector<int>& meter)
{
	meter[2] = 1;
	meter[3] = 1;
	meter[6] = 16;
	action::execute(last, current, meter);
}

int redCancel::arbitraryPoll(int q, int f)
{
	if(q == 33) return 1;
	else return action::arbitraryPoll(q, f);
}
int redSuper::arbitraryPoll(int q, int f)
{
	if(q == 31) return 11;
	else if(q == 32) return 1;
	else return action::arbitraryPoll(q, f);
}

redCancel::~redCancel() {}
redSuper::~redSuper() {}
