//build with g++ operaEvent.cc test.cc -lconfig -lSDL -lSDL_mixer


#include "operaEvent.h"
#include <iostream>
#include <SDL/SDL_mixer.h>

int main(int argc, char* argv[])
{
	Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);
	operaEvent event(argv[1], 1);
	event.play();
	std::cin.get();
}
