/*Header file for "Player" class in project Ground Up Fighting Game
 *
 *Written by Alex Kelly in 2012
 *Under MIT OSI license, see the file "COPYING" for details
 */
#include "../charlist.h"
#ifndef PLAYER
#define PLAYER
class frame;
class instance{
public:
	instance();
	instance(avatar*);
	virtual ~instance();
	virtual avatar * pick() { return v; }

	SDL_Rect spr, *hitbox, *hitreg, collision, *momentum, lock;
	int hitComplexity, regComplexity, momentumComplexity;
	bool secondInstance;
	int posX, posY;
	int facing;
	int deltaX, deltaY; 
	int ID;
	int inputBuffer[30];
	int currentFrame;
	int freeze;
	action * cMove;
	action * bMove;
	action * sMove;
	int connectFlag, hitFlag;
	bool dead:1;
	int throwInvuln;
	virtual bool acceptTarget(instance*);
	virtual bool CHState() { return 0; }
	virtual void init();
	virtual void step();

	virtual void getMove(int*, bool*, SDL_Rect &, bool);
	virtual int takeHit(int, hStat&);
	virtual void enforceGravity(int, int);
	void enforceAttractor(attractor*);
	virtual void invertVectors(int);
	virtual void addVector(SDL_Rect&);
	virtual void removeVector(int);
	virtual void pullVolition();
	virtual void setPosition(int, int);
	virtual void updateRects();
	virtual void draw(int, int, float);
	virtual void drawBoxen(int, int, float);
	virtual void combineDelta();
	virtual bool spriteCheck();
	virtual void connect(int, hStat&);
	virtual void pushInput(bool*);
	virtual int passSignal(int);
	int particleType;
	int blockType;
	int counter;
protected:
	avatar * v;
};

class player : public instance{
public:
	player();
	player(int);
	~player();
	virtual character * pick() { return v; }

	const char * inputName[10];//Input names. This is really just for housekeeping.
	int rounds;		//How many rounds has this player won this match?
	int padding[400];	//More magic. Do not touch
	SDL_Event writeConfig(int);
	virtual bool readConfig();
	virtual void characterSelect(int);
	virtual void drawHitParticle(int, int, float);

	virtual void land();
	virtual void enforceGravity(int, int);
	virtual void drawMeters(int, float);
	virtual void readEvent(SDL_Event &, bool *&, int *&, bool *&);
	virtual void genEvent(bool *&, int *&, bool *&) {}
	virtual void roundInit();
	virtual int takeHit(int, hStat&);
	virtual void connect(int, hStat&);
	virtual bool CHState();
	bool elasticX:1;
	bool elasticY:1;
	bool slide:1;
	bool stick:1;
	int hover;

	bool rCorner, lCorner;

	int particleLife;

	/*Helper functions for "resolve" tick*/
	virtual void checkBlocking();
	virtual void checkFacing(player*);
	virtual int dragBG(int, int);
	virtual void checkCorners(int, int, int);
	virtual void getThrown(action*, int, int);

	virtual void init();
	int wins;
protected:
	character * v;
private:
	SDL_Event input[10];	//Inputs. These are the SDL_Events tied to the 10 buttons in the actual game
};

class demon : public player{
public:
	demon();
	demon(int);
	demon(int, frame*);
	frame * script;
	void roundInit();
	void genEvent(bool *&, int *&, bool *&);
	character * pick() { return v; }
	void characterSelect(int);
protected:
	character * v;
};
#endif
