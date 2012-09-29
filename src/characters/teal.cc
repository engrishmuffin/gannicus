#include "teal.h"
teal::teal(){
	for(int i = 0; i < 4; i++){
		head[i] = new actionTrie;
		airHead[i] = new actionTrie;
	}
	meter = new int[4];
	build("Teal", "Teal");
	dFlag = 1;
}

int teal::comboState(action * c)
{
	for(int i = 0; i < 4; i++){
		if(c == reel[i]) return 1;
		if(c == crouchReel[i]) return 1;
		if(c == untech[i]) return 1;
		if(c == fall[i]) return -2;
		if(i < 3){
			if(c == standBlock[i]) return -1;
			if(c == crouchBlock[i]) return -1;
			if(c == airBlock[i]) return -1;
		}
	}
	return 0;
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

void teal::build(const char *directory, const char *file)
{
	getName(directory, file);

	char buffer[101];

	char array[5] = "NRSP";

	for(int i = 0; i < 4; i++){
		sprintf(buffer, "%s/NS%c", name, array[i]);
		neutral[i] = new looping(buffer);
	}

	avatar::build(directory, file);

	for(int i = 0; i < 4; i++){
		sprintf(buffer, "%s/NL%c", name, array[i]);
		crouch[i] = new looping(buffer);

		sprintf(buffer, "%s/NJ%c", name, array[i]);
		airNeutral[i] = new airLooping(buffer);
		airNeutral[i]->feed(neutral[i], 1, 0);

		sprintf(buffer, "%s/HS%c", name, array[i]);
		reel[i] = new hitstun(buffer);

		sprintf(buffer, "%s/Fall%c", name, array[i]);
		fall[i] = new airLooping(buffer);

		sprintf(buffer, "%s/UT%c", name, array[i]);
		untech[i] = new untechState(buffer);
		untech[i]->feed(fall[i], 0, 0);

		sprintf(buffer, "%s/down%c", name, array[i]);
		down[i] = new utility(buffer);
		untech[i]->feed(down[i], 1, 0);
		fall[i]->feed(down[i], 1, 0);

		sprintf(buffer, "%s/HL%c", name, array[i]);
		crouchReel[i] = new hitstun(buffer);

		if(i < 3){
			sprintf(buffer, "%s/BH%c", name, array[i]);
			standBlock[i] = new hitstun(buffer);

			sprintf(buffer, "%s/BL%c", name, array[i]);
			crouchBlock[i] = new hitstun(buffer);

			sprintf(buffer, "%s/BA%c", name, array[i]);
			airBlock[i] = new hitstun(buffer);
		}
		head[i]->insert(5, neutral[i]);

		head[i]->insert(2, crouch[i]);
		head[i]->insert(3, crouch[i]);
		head[i]->insert(1, crouch[i]);

		airHead[i]->insert(5, airNeutral[i]);
	}
	throwBreak = new shift(buffer);
	sprintf(buffer, "%s/break", name);
}

void teal::init(action *& cMove)
{
	meter[3] = 0;
	character::init(cMove);
}

void teal::neutralize(action *& cMove)
{
	if(aerial) cMove = airNeutral[meter[3]];
	else cMove = neutral[meter[3]];
}

void teal::resetAirOptions()
{
	character::resetAirOptions();
	if(meter[3] == 3) meter[2] = 2;
}

int teal::checkBlocking(action *& cMove, int input[], int &connectFlag, int &hitFlag)
{
	if(meter[3] == 3) return -1;
	int st;
	bool success = false;
	int ret = -1;
	st = cMove->arbitraryPoll(1, 0);
	switch(input[0]){
	case 3:
	case 6:
	case 9:
		for(int i = 1; i < 7; i++){
			if(input[i] % 3 == 1){
				for(int j = i+1; j < 8; j++){
					if(input[j] % 3 == 2){
						if(aerial){
							if(airBlock[meter[3]]->cancel(cMove, connectFlag, hitFlag)) {
								airBlock[meter[3]]->init(st);
								cMove = airBlock[meter[3]];
							}
						} else {
							if(input[0] > 3){ 
								if(standBlock[meter[3]]->cancel(cMove, connectFlag, hitFlag)) {
									standBlock[meter[3]]->init(st);
									cMove = standBlock[meter[3]];
								}
							} else {
								if(crouchBlock[meter[3]]->cancel(cMove, connectFlag, hitFlag)) {
									crouchBlock[meter[3]]->init(st);
									cMove = crouchBlock[meter[3]];
								}
							}
							ret = 2;
							j = 10;
						}
					}
				}
				i = 9;
			}
		}
		break;
	case 7:
	case 4:
	case 1:
		if(aerial){
			if(airBlock[meter[3]]->cancel(cMove, connectFlag, hitFlag)) {
				airBlock[meter[3]]->init(st);
				cMove = airBlock[meter[3]];
			}
		} else { 
			if(input[0] > 3){ 
				if(standBlock[meter[3]]->cancel(cMove, connectFlag, hitFlag)) {
					standBlock[meter[3]]->init(st);
					cMove = standBlock[meter[3]];
				}
			} else {
				if(crouchBlock[meter[3]]->cancel(cMove, connectFlag, hitFlag)) {
					crouchBlock[meter[3]]->init(st);
					cMove = crouchBlock[meter[3]];
				}
			}
		}
		success = true;
		break;
	}
	if(success){
		ret = 0;
		for(int i = 1; i < 7; i++){
			if(input[i] % 3 != 1)
			ret = 1;
		}
	}
	return ret;
}

int teal::takeHit(action *& cMove, hStat & s, int b, int &f, int &c, int &h, int &p)
{
	int freeze = s.stun/4 + 10;
	p = cMove->takeHit(s, b, f, c, h);
	if (p == 1){
		if(s.launch) aerial = 1;
		health -= s.damage;
		if(health < 0) health = 0;
		if(s.stun > 0){
			f = 0;
			if(aerial){
				untech[meter[3]]->init(s.stun+s.untech);
				cMove = untech[meter[3]];
				resetAirOptions();
			} else if(cMove->crouch){
				crouchReel[meter[3]]->init(s.stun + s.stun/5);
				cMove = crouchReel[meter[3]];
			} else {
				reel[meter[3]]->init(s.stun);
				cMove = reel[meter[3]];
			}
		}
	} else if (p == -1) {
		if(meter[0] + 6 < 300) meter[0] += 6;
		else meter[0] = 300;
	}
	if(meter[0] + 1 < 300) meter[0] += 1;
	else meter[0] = 300;
	return freeze;
}

action * teal::hook(int inputBuffer[30], int i, int f, int * r, int down[5], bool up[5], action * c, SDL_Rect &p, int &cFlag, int &hFlag)
{
	if(aerial) return airHead[meter[3]]->actionHook(inputBuffer, 0, -1, meter, down, up, c, p, cFlag, hFlag);
	else return head[meter[3]]->actionHook(inputBuffer, 0, -1, meter, down, up, c, p, cFlag, hFlag);
}

void teal::sortMove(action * m, char* buffer)
{
	char component[2];
	char * token;
	int q;
	int pattern;
	actionTrie * t = NULL;
	token = strtok(buffer, " \t=>-&?@%$_!\n");
	while (token){
		token = NULL;
		token = strtok(NULL, " \t=>-&?@%$_!\n");
		if(token) {
			switch (token[0]){
			case 'n':
				if(token[1] == 'a') t = airHead[0];
				else if(token[1] == 'h') t = head[0];
				break;
			case 'r':
				if(token[1] == 'a') t = airHead[1];
				else if(token[1] == 'h') t = head[1];
				break;
			case 's':
				if(token[1] == 'a') t = airHead[2];
				else if(token[1] == 'h') t = head[2];
				break;
			case 'p':
				if(token[1] == 'a') t = airHead[3];
				else if(token[1] == 'h') t = head[3];
				break;
			default:
				break;
			}
			pattern = 0;
			for(int i = strlen(token)-1; i > 0; i--){
				switch(token[i]){
				case 'A':
				case 'B':
				case 'C':
				case 'D':
				case 'E':
					pattern += 1 << (token[i] - 'A');
					break;
				default:
					sprintf(component, "%c\0", token[i]);
					q = atoi(component);
					if(q > 10) q = q % 10;
					t = t->insert(q);
					break;
				}
			}
			t->insert(m, pattern);
		}
	}
}

action * teal::createMove(char * fullName)
{
	char * token;
	char type[2] = {fullName[0], fullName[1]};
	char actionName[151];
	char buffer[101];
	strcpy (buffer, fullName);

	token = strtok(fullName, " \t-@?_%$!\n");
	sprintf(actionName, "%s/%s", name, token);

	action * m;
	switch(type[0]){
	case '$':
		m = new shift(actionName);
		break;
	default:
		m = character::createMove(buffer);
		break;
	}
	return m;
}

bool shift::setParameter(char * buffer)
{
	char savedBuffer[100];
	strcpy(savedBuffer, buffer);

	char * token = strtok(buffer, "\t: \n-");

	if(!strcmp("Stance", token)){
		token = strtok(NULL, "\t: \n-");
		stance = atoi(token); 
		return 1;
	} else return action::setParameter(savedBuffer);
}

void shift::execute(action * last, int *& resource)
{
	resource[0] -= cost;
	resource[3] = stance;
}

shift::shift(const char *n)
{
	build(n);
}

void shift::zero()
{
	action::zero();
	stance = 0;
}

shift::~shift() {}
