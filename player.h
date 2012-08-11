/*Header file for "Player" class in project Ground Up Fighting Game
 *
 *Written by Alex Kelly in 2012
 *Under MIT OSI license, see the file "COPYING" for details
 */
#include "charlist.h"
#ifndef PLAYER
#define PLAYER
class instance{
public:
	instance();
	instance(avatar * f);
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
	int cFlag;
	bool dead:1;
	virtual void init();
	virtual void step();

	virtual void getMove(bool*, bool*, SDL_Rect &, bool);
	virtual void invertVectors(int);
	virtual void addVector(SDL_Rect&);
	virtual void removeVector(int);
	virtual void pullVolition();
	virtual void setPosition(int, int);
	virtual void updateRects();
	virtual void draw(int, int);
	virtual void drawBoxen(int, int);
	virtual void combineDelta();
	virtual bool spriteCheck();
	virtual void connect(int, hStat&);
	virtual void pushInput(bool*);
protected:
	avatar * v;
};

class player : public instance{
public:
	player();
	player(int);
	~player();
	character * pick() { return v; }

	bool aerial();
	void getMove(bool*, bool*, SDL_Rect &, bool);
	const char * inputName[10];   //Input names. This is really just for housekeeping.
	SDL_Event input[10];    //Inputs. These are the SDL_Events tied to the 10 buttons in the actual game
	int rounds;		//How many rounds has this player won this match?
	int padding[400];   //More magic. Do not touch
	void writeConfig();
	bool readConfig();
	void characterSelect(int);
	void drawHitParticle(int, int);

	void land();
	void drawMeters(int);
	void readEvent(SDL_Event &, bool *&, bool *&, bool *&);
	void roundInit();
	int takeHit(int, hStat&);
	void connect(int, hStat&);
	bool CHState();
	bool elasticX:1;
	bool elasticY:1;
	bool slide:1;
	bool stick:1;
	int blockType;
	int hover;
	int throwInvuln;

	bool rCorner, lCorner;

	int particleLife;
	int particleType;

	/*Helper functions for "resolve" tick*/
	void enforceGravity(int, int);
	void checkBlocking();
	void checkFacing(player*);
	int dragBG(int, int);
	void checkCorners(int, int, int);
	void getThrown(action*, int, int);

	void init();
protected:
	character * v;
};
#endif
