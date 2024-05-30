#include "Agent.h"

Agent::Agent(mcpp::Coordinate startLoc)
{
    mcpp::MinecraftConnection mc;

    this->startLoc.x = startLoc.x;
    this->startLoc.y = startLoc.y;
    this->startLoc.z = startLoc.z;
    mc.setPlayerPosition(this->startLoc);

}

Agent::~Agent()
{
}

mcpp::Coordinate Agent::getStartLocation(void) const {
    mcpp::MinecraftConnection mc;

    return strCord;
}

mcpp::Coordinate Agent::randLocation(void) {

    int emptCord[NUM_RAND_CORD][2] = //... All empty location

    int emptCordIndices []



    return randCord
}




        // Normal Mode
    // if(state num = solveMaze manually) {

    // Place player randomly inside the maze
    //}


        // Test Mode
    // if(state num = solveMaze manually) {

    // Place player at the furthest point from the exit
    //}




    // if(state num = solveSolution) {

    // Left-Hand follow algorithm

    //}

    //Left-Hand follow algorithm

//player coordinates = (x, y, z)
// Considering player is facing forward in the x direction
//if (z + 1 == Air)
// go z + 1
//else if (z + 1 != Air && x + 1 == Air)
// go x + 1
//else if (z + 1 != Air && x + 1 != Air && z - 1 == Air)
// go z - 1
//else if (z + 1 != Air && x + 1 != Air && z - 1 != Air)
// go x -1