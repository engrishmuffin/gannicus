#ifndef OPERA
#define OPERA
class opera
{
public:
	 opera();
	~opera(); 
	void beat();
	int parseCharacterEvents();
	int parseStageEvents();
	int currentVolume;
}

struct playerScoreMask
{
	bool winning:1; 
	bool streak:1; //queen guitars
	bool losing:1; //losing/even ostinato
	bool effect[5]:5; //registers for short effects
}


struct operaScore
{
	playerScoreMask p1score;
	playerScoreMask p2score;
}

typedef union {
	unsigned int i;
	operaScore s;
} score;

#endif 
