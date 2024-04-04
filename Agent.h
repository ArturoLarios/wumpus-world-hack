// Agent.h

#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>

#include "Action.h"
#include "Percept.h"
#include "Location.h"
#include "Orientation.h"

class Agent
{
private:
	stringstream ss;
	string output;
	streambuf* oldBuf;
	int worldSize;
	Location goldLocation;
	Location wumpusLocation;
	vector<Location> pitLocations;
	Location agentLocation;
	Orientation agentOrientation;
	void Map ();
public:
	Agent ();
	~Agent ();
	void Initialize ();
	Action Process (Percept& percept);
	void GameOver (int score);
};

#endif // AGENT_H
