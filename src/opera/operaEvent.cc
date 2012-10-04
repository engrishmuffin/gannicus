#include "opera.h"
#include "operaEvent.h"
#include <yaml-cpp/yaml.h>

void operator >> (const YAML::Node& node, operaEventConfig config)
{
	node["name"] >> config.name;
	node["bitAnd"] >> config.bitAnd;
	node["bitNot"] >> config.bitNot;
	node["baseVolume"] >> config.baseVolume;
	node["framesModulus"] >> config.framesModulus;
	node["framesCooldown"] >> config.framesCooldown;
	node["scaleConstant"] >> config.scaleConstant;
}

int operaEventParse(configFile)
{
	std::ifstream in(configFile);
	YAML::Parser parser(in);
	YAML::Node node;
	parser.GetNextDocument(node);
	operaEventConfig events[node.size()];
	for(int i = 0; i < node.size(); i++)
	{
		node[i] >> events[i];
	}
	numberEvents = node.size();
}


operaEvent::operaEvent(oggFolder, channel, operaEventConfig)
{
	
	eventSample = loadOgg();
	Mix_Volume(channel, baseVolume);
	framesAgoPlayed = 0;
	framesAgoActivated = 0;


}

operaEvent::~operaEvent()
{
	Mix_HaltChannel(channel);
}

Mix_Chunk operaEvent::loadOgg()
{
	char resourcePath[200];
	sprintf(resourcePath, "%i/%i.ogg", oggFolder, oggName);
	return Mix_LoadWAV(resourcePath);
}


void operaEvent::activate(condition)
{
	if !condition return;
	else 
	{
		if (framesAgoPlayed >= framesCooldown) && !(elapsedFrames % framesModulus)
		       	play();
		if (framesAgoActivated <= framesCooldown)
			grow();
	}
	decay();
//if lastFired < frames, increase volume
//otherwise set volume to defaultVolume
//zero lastFired
}
void operaEvent::play()
{
	Mix_PlayChannel(channel, eventSample, 0);
}

void operaEvent::grow()
{
//increase volume at a rate proportional to framesCoefficient.
}

void operaEvent::decay()
{
//decrease volume at a rate proportional to framesAgoActivated and framesCoefficient
framesAgoPlayed++;
framesAgoActivated++;
}
