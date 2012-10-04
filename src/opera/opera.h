#ifndef OPERA
#define OPERA

/** This an object that can be sent messages once per frame 
 *
 * It won't at any point attempt to define the in-game state that should result in those messages.
 * **/


class opera
{
public:
	 opera(); //load all of the operaEvents
	~opera(); 
	void beat(int); /** things to do every frame. accepts an argument intended to come from interface::elapsedTime()**/
	void listen(score, score); //take in a signal and set appropriate things
	void mix(); /**allocate volume to the events based on what they request **/
	int currentVolume;
}

struct playerScoreMask
{
	bool winning:1;
	bool streak:1; //queen guitars
	bool struggling:1; //losing/even ostinato
	bool effect[8]:8; //registers for short effects
}


struct operaScore
{
	bool atMenu:1;  //probably this is all that's enabled at the menu
	playerScoreMask p1score;
	playerScoreMask p2score;
}

typedef union {
	unsigned int i;
	operaScore s;
} score;

#endif 
