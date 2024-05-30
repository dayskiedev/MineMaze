#ifndef ASSIGN3_AGENT_H
#define ASSIGN3_AGENT_H

#include <iostream>
#include <cstdlib> //Is this permitted?
#include <mcpp/mcpp.h>

#define MOVE_XPLUS mcpp::Coordinate(1,0,0)
#define MOVE_XMINUS mcpp::Coordinate(-1,0,0)
#define MOVE_ZPLUS mcpp::Coordinate(0,0,1)
#define MOVE_ZMINUS mcpp::Coordinate(0,0,-1)

enum solveAlgorithm{
        LEFT_HAND_FOLLOW,
        BREATH_FIRST_SEARCH,
};

enum AgentOrientation{
    X_PLUS,
    Z_PLUS,
    X_MINUS,
    Z_MINUS
};

class Agent
{

public:
    Agent(mcpp::Coordinate startLoc);
    ~Agent();
    mcpp::Coordinate getPlayerLocation(void) const;
    mcpp::Coordinate Agent::randLocation(void);


private:
    /* data */
    mcpp::MinecraftConnection mc;
    mcpp::Coordinate startLoc;

};



#endif //ASSIGN3_AGENT_H