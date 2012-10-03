#ifndef OPERA
#define OPERA

/** Everything is currently a stub!! 
 *
 * This is an object that can be sent messages once per frame 
 *
 * It won't at any point attempt to define the in-game state that should result in those messages.
 * **/


class opera
{
public:
	 opera(); //load all of the operaEvents
	~opera(); //unload everything
	void beat(int); /** things to do every frame. accepts an argument as to what frame it is **/
	void listen(operaScore, operaScore); //take in a signal and set appropriate things
	void mix(); /**allocate volume to the events based on what they request **/
	float volume(); //get current master volume
	float volume(int) //set current master volume
private:
	float currentVolume;
	const float maxVolume = 100.0;
	const float minVolume = 0.0;
	const float defaultVolume = 50.0;
}

class operaEvent
{
public:
	 operaEvent(); //get the correct .ogg file
	~operaEvent(); //make sure silent
	void beat(); //things that happen every frame: fire, play, decay
	void activate(); //start, or amplify/sustain
	void play(); //start playing IF the frame is the correct number, AND recently fired
	void decay(); //decay by half or just stop if under a threshold AND last_fired > threshold
private:
	float currentVolume; //as a portion of the total
	float thresholdVolume; //to be considered active
	int frames; //number of frames the sound occupies
	int rateModulus; //can only play on currentFrame
	int lastFired; //checked by play and decay, incremented by decay, zeroed by fire
	const int decayThreshold;
}

//Make descendent classes of operaEvent for the event types, since they have default volume/frames values, different conditions in fire() before zeroing, etc. 
//for each player: streak, winning, even, losing, move player
//for stage: ambience, interlude

//for NOW:
//ambience
//exists
//winning

struct scoreMask
{
	/*Obviously, more information is good, but for now... */
	bool winning:1;
	bool streak:1; //queen guitars
	bool struggling:1; //e.g. if both have this, they're even
}

typedef union {
	unsigned int i;
	scoreMask s;
} operaScore;

#endif 
