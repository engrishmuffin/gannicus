#include "gl-compat.h"
#include "harness.h"
#include "window.h"
#include <iostream>
using std::cout;

harness::harness()
{
	gameover = false;
}

void harness::init()
{
	/*Set up input buffers and joysticks*/
	macro = false;
	command.clear();
	for(int i = 0; i < SDL_NumJoysticks(); i++)
		SDL_JoystickOpen(i);
}

void harness::processInput(SDL_Event &event)
{
	/*Do stuff with event*/
	switch (event.type){
	/*Kill handler*/
	case SDL_QUIT:
		printf("Sigterm received!\n");
		gameover = 1;
		break;
	/*Keyboard handler. Maybe I'll optimize such that the knows if it even needs to check this (EG if sticks are used)*/
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_ESCAPE:
			gameover = 1;
			break;
		case SDLK_SEMICOLON:
			if(SDL_GetModState() & KMOD_SHIFT && !macro){
				macro = true;
				command = "";
			}
			break;
		case SDLK_RETURN:
			if(macro){ 
				runMacro();
				macro = false;
				command.clear();
			}
			break;
		default:
			if(macro) command += SDL_GetKeyName(event.key.keysym.sym);
			break;
		}
		break;
	}
}

void harness::runMacro()
{
	cout << command + '\n';
}

void harness::readInput()
{
	/*Make our dummy event for polls*/
	SDL_Event event;
	for(int i = 0; i < 20; i++){
		if (SDL_PollEvent(&event)){
			processInput(event);
		}
	}
}

void arcadeHarness::initContainers()
{
	for(frame i:currentFrame){
		for(bool j:i.axis) j = false;
		for(int j:i.buttons) j = 0;
		i.n.i = 0;
	}
	for(int& i:counter) i = 0;
}

void arcadeHarness::initContainers(int players, int buttons)
{
	for(int i = 0; i < players; i++){
		frame temp;
		for(int j = 0; j < buttons; j++){
			temp.buttons.push_back(0);
		}
		for(int j = 0; j < 4; j++)
			temp.axis.push_back(0);
		counter.push_back(0);
		currentFrame.push_back(temp);
	}
}

