// Agent.cc

#include "Agent.h"

using namespace std;

Agent::Agent ()
{

}

Agent::~Agent ()
{
    // Print wumpus location
    cout << "Wumpus is at " << wumpusLocation.X << ", " << wumpusLocation.Y << endl;
    // Print pit locations
    for (vector<Location>::iterator it = pitLocations.begin(); it != pitLocations.end(); it++)
        cout << "Pit is at " << it->X << ", " << it->Y << endl;
}

void Agent::Initialize ()
{
    oldBuf = cout.rdbuf(ss.rdbuf());
    agentLocation.X = agentLocation.Y = 1;
    agentOrientation = RIGHT;
}

void Agent::Map ()
{
    // finite automata states
    enum {
        START, COUNT, ROW, COLUMN, FAKE_ROW1, FAKE_ROW2,
    } state = START;

    int c, row = 1, column = 1; // to fit EOF
    while ((c = ss.get()) != EOF) {
        switch (state) { 
            case START:
                if (c == '+')
                    state = COUNT;
                break;
            case COUNT:
                if (c == '+')
                    worldSize++;
                else if (c == '\n')
                    state = ROW;
                break;
            case ROW:
                if (c == '|')
                    state = COLUMN;
                break;
            case COLUMN:
                if (c == '|')
                    column++;
                else if (c == 'W') {
                    wumpusLocation.X = worldSize - row + 1;
                    wumpusLocation.Y = column;
                }
                else if (c == 'P') {
                    Location pitLocation;
                    pitLocation.X = worldSize - row + 1;
                    pitLocation.Y = column;
                    pitLocations.push_back(pitLocation);
                }
                else if (c == 'G') {
                    goldLocation.X = row;
                    goldLocation.Y = column;
                }
                else if (c == '\n') {
                    row++;
                    column = 1;
                    state = FAKE_ROW1;
                }
                break;
            case FAKE_ROW1:
                if (c == '\n')
                    state = FAKE_ROW2;
                break;
            case FAKE_ROW2:
                if (c == '\n')
                    state = ROW;
                break;
            default:
                assert(0);
                break;
        }
    }

    cout.rdbuf(oldBuf); // restore cout
    cout << ss.str(); // output the text we hijacked from cout
}

Action Agent::Process (Percept& percept)
{
	Action action;

    Map();

	return CLIMB;
}

void Agent::GameOver (int score)
{

}

