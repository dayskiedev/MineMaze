#include "Agent.h"

Agent::Agent()
{
}


Agent::~Agent()
{
}

void placePlayer(mcpp::Coordinate mazeStartPos) {
    mcpp::MinecraftConnection mc;
    
    mc.setPlayerPosition(mazeStartPos);

}

/*
// Generate a random (x, y, z) and will teleport player to it
mcpp::Coordinate Agent::randLocation(void) {
    mcpp::MinecraftConnection mc;
    mcpp::Coordinate randCord; 

    int emptCord[NUM_RAND_CORD][2] = {{x,z},{x,z}}; //... All possible empty location

    int emptCordIndices[NUM_RAND_CORD] = {0,1}; //Amount of empty sets of coordinates

    srand(time(0));
    int randomNumber = rand() % 2; // random gen 0 - 1

    randCord = getPlayerLocation();

    randCord.x = emptCord[randomNumber][0];
    randCord.z = emptCord[randomNumber][1];

    mc.setPlayerPosition(randCord);

    return randCord;
}

*/ 
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