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
	void beat(int); /** things to do every frame. accepts an argument intended to come from interface::elapsedTime()**/
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