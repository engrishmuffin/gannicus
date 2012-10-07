//build with g++ operaEvent.cc test.cc -lconfig -lSDL -lSDL_mixer


#include "operaEvent.h"
#include "opera.h"
#include <iostream>

int main(int argc, char* argv[])
{
	scoreField score;
	score.i = 13;
	opera test;	
	test.loadEvents(argv[1]);
	test.beat(score, 1);	
	std::cin.get();
	test.beat(score, 4);
	std::cin.get();
	test.allEvents.at(1)->play();
	std::cin.get();
}
