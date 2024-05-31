#include "Agent.h"

Agent::Agent()
{

}


Agent::~Agent()
{
}

void Agent::placePlayer(mcpp::Coordinate mazeStartPos) {
    mcpp::MinecraftConnection mc;
    
    mc.setPlayerPosition(mazeStartPos);

}

void Agent::solveMaze() {
    mcpp::MinecraftConnection mc;

    mcpp::Coordinate startSolvePoint = mc.getPlayerPosition();

    

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