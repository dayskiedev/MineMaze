#ifndef ASSIGN3_AGENT_H
#define ASSIGN3_AGENT_H

#include <iostream>
#include <mcpp/mcpp.h>
#include <unistd.h>   
#include <vector>

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
    Agent();
    ~Agent();
    void placePlayer(mcpp::Coordinate placePoint);
    void solveMaze();

private:
    /* data */ 
    void printAndGuideSolve (std::vector<mcpp::Coordinate> completeVec);
    void zMinus (mcpp::Coordinate currentCor, int vecCounter);
    void zPlus (mcpp::Coordinate currentCor, int vecCounter);
    void xMinus (mcpp::Coordinate currentCor, int vecCounter);
    void xPlus (mcpp::Coordinate currentCor, int vecCounter);
    
    mcpp::MinecraftConnection mc;
    mcpp::Coordinate pointLoc;
    bool bCarpetFound;
    std::vector<mcpp::Coordinate> solveCord;

};

#endif //ASSIGN3_AGENT_H