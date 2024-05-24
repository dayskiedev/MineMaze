#include "Agent.h"

Agent::Agent(mcpp::Coordinate startLoc)
{
}

Agent::~Agent()
{
}

Left-Hand follow algorithm

player coordinates = (x, y, z)
// Considering player is facing forward in these coordinates

if (x + 1 == Air)

// if (left is empty)
//  go left
// else if (left is not empty, but straight is)
//  go straight
// else if (left and straight is not empty)
//  go right 
// else if (left, right and straight is not empty)
// turn 180* 