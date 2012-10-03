/** Everything is currently a stub!! 
 *
 * This is an object that can be sent messages once per frame 
 *
 * It won't at any point attempt to define the in-game state that should result in those messages.
 * **/

#include<SDL/SDL_mixer.h> //until we find something better. really could be anything

class opera
{
public:
	 opera(); 
	~opera();
	void loadOgg(); 
	void tick(); /** things to do every frame **/
	void listen(operaScore, operaScore); //take in a signal and set appropriate things
}

class operaEvent
{
public:
	 operaEvent(); //get the correct .ogg file
	~operaEvent(); //make sure silent
	fire(); //start, or amplify/sustain
	play(); //start playing IF the frame is the correct number, AND recently fired
	decay(); //decay by half or just stop if under a threshold AND last_fired > threshold
	tick(); //things that happen every frame: fire
private:
	float volume; //as a portion of the total
	int frames; //number of frames the sound occupies and how often it can fire 
	int lastFired; //checked by play and decay, incremented by decay, zeroed by fire
	const int decayThreshold;
}

//Make descendent classes of operaEvent for the event types, since they have default volume/frames values, different conditions in fire() before zeroing, etc. 
//for each player: streak, winning, even, losing, exists.
//for stage: ambience, interlude
struct scoreMask
{
	/*Obviously, more information is good, but  */
	bool winning:1;
	bool streak:1; //queen guitars
	bool struggling:1; //e.g. if both have this, they're even
}

typedef union {
	unsigned int i;
	scoreMask s;
} operaScore;


