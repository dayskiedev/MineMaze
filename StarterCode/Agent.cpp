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

    mcpp::Coordinate pointLoc = mc.getPlayerPosition();

    int stepCounter = 1;

    mc.setBlock(pointLoc, mcpp::Blocks::LIME_CARPET);

    while (!(mc.getBlock(pointLoc) == mcpp::Blocks::BLUE_CARPET)) {
        if (mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::AIR) {
            pointLoc = pointLoc + MOVE_ZPLUS;
            mc.setBlock(pointLoc, mcpp::Blocks::LIME_CARPET);
        }
        else if (!(mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::AIR) && mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::AIR) {
            pointLoc = pointLoc + MOVE_XPLUS;
            mc.setBlock(pointLoc, mcpp::Blocks::LIME_CARPET);
        } 
        else if (!(mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::AIR) && mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::AIR) {
            pointLoc = pointLoc + MOVE_ZMINUS;
            mc.setBlock(pointLoc, mcpp::Blocks::LIME_CARPET);
        }
        else if (!(mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::AIR)) {
            pointLoc = pointLoc + MOVE_XMINUS;
            mc.setBlock(pointLoc, mcpp::Blocks::LIME_CARPET);
        }
        
        std::cout << "Step[" << stepCounter << "]: (" << pointLoc.x << ", " << pointLoc.y << ", " << pointLoc.z << ")"  << std::endl;

        stepCounter++;

        // mc.setBlock(pointLoc, mcpp::Blocks::AIR);
        // Need to figure how to do the second delay 
    
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