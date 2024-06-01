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

    int stepCounter = 1;

    while () {
        if (mc.getBlock() == mcpp::Blocks::AIR) {
            mc.setPlayerPosition();
        }
        else if (mc.getBlock() != mcpp::Blocks::AIR && mc.getBlock() == mcpp::Blocks::AIR) {
            mc.setPlayerPosition();
        } 
        else if (mc.getBlock() != mcpp::Blocks::AIR && mc.getBlock() != mcpp::Blocks::AIR && mc.getBlock() == mcpp::Blocks::AIR) {
            mc.setPlayerPosition();
        }
        else if (mc.getBlock() != mcpp::Blocks::AIR && mc.getBlock() != mcpp::Blocks::AIR && mc.getBlock() != mcpp::Blocks::AIR) {
            mc.setPlayerPosition();
        }
        
        std::cout << "Step[" + stepCounter + "]: " + /*(x, y, z)*/ << std::endl;

        stepCounter++;
    }

}
   
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