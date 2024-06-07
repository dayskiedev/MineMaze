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
    unsigned int nexMove = 1;
    bool bCarpetFound = false;

        if (!(mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::AIR)) {   //xMinus becomes left hand needs revision
            while (!bCarpetFound) {
                if (nexMove == 1) {
                    while (nexMove == 1) {
                        if (mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::AIR && !(mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::AIR)) {
                            pointLoc = pointLoc + MOVE_ZPLUS;
                            mc.setBlock(pointLoc, mcpp::Blocks::LIME_CARPET);
                            std::cout << nexMove << "Step[" << stepCounter << "]: (" << pointLoc.x << ", " << pointLoc.y << ", " << pointLoc.z << ")"  << std::endl;
                            stepCounter++;
                            sleep(2);
                            mc.setBlock(pointLoc, mcpp::Blocks::AIR); 
                        }
                        else if (mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::BLUE_CARPET) {
                            bCarpetFound = true;
                            pointLoc = pointLoc + MOVE_ZPLUS;
                        }
                        else {
                            nexMove = 2;
                        }
                    }
                }
                else if (nexMove == 2) {
                    while (nexMove == 2) {
                        if (!(mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::AIR) && mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::AIR) {
                            pointLoc = pointLoc + MOVE_XPLUS;
                            mc.setBlock(pointLoc, mcpp::Blocks::LIME_CARPET);
                            std::cout << nexMove << "Step[" << stepCounter << "]: (" << pointLoc.x << ", " << pointLoc.y << ", " << pointLoc.z << ")"  << std::endl;
                            stepCounter++;
                            sleep(2);
                            mc.setBlock(pointLoc, mcpp::Blocks::AIR); 
                        }
                        else if (mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::BLUE_CARPET) {
                            bCarpetFound = true;
                            pointLoc = pointLoc + MOVE_XPLUS;
                        }
                        else {
                            nexMove = 3;
                        }
                    }
                }
                else if (nexMove == 3) {
                    while (nexMove == 3) {
                        if (!(mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::AIR) && mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::AIR){
                            pointLoc = pointLoc + MOVE_ZMINUS;
                            mc.setBlock(pointLoc, mcpp::Blocks::LIME_CARPET);
                            std::cout << nexMove << "Step[" << stepCounter << "]: (" << pointLoc.x << ", " << pointLoc.y << ", " << pointLoc.z << ")"  << std::endl;
                            stepCounter++;
                            sleep(2);
                            mc.setBlock(pointLoc, mcpp::Blocks::AIR); 
                        }
                        else if (mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::BLUE_CARPET) {
                            bCarpetFound = true;
                            pointLoc = pointLoc + MOVE_ZMINUS;
                        }
                        else {
                            nexMove = 4;
                        }
                    }

                }
                else if (nexMove == 4) {
                    while (nexMove == 4) {
                        if (!(mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::AIR) && (mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::AIR)){
                            pointLoc = pointLoc + MOVE_XMINUS;
                            mc.setBlock(pointLoc, mcpp::Blocks::LIME_CARPET);
                            std::cout << nexMove << "Step[" << stepCounter << "]: (" << pointLoc.x << ", " << pointLoc.y << ", " << pointLoc.z << ")"  << std::endl;
                            stepCounter++;
                            sleep(2);
                            mc.setBlock(pointLoc, mcpp::Blocks::AIR);    
                        }
                        else if (mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::BLUE_CARPET) {
                            bCarpetFound = true;
                            pointLoc = pointLoc + MOVE_ZMINUS;
                        }
                        else {
                            nexMove = 1;
                        }
                    }
                } 
            }           
        }
        else { // zMinus becomes left hand
            while (!bCarpetFound) {
                if (nexMove == 1) {
                    while (nexMove == 1) {
                        if (mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::AIR && !(mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::AIR)) {
                            pointLoc = pointLoc + MOVE_XPLUS;
                            mc.setBlock(pointLoc, mcpp::Blocks::LIME_CARPET);
                            std::cout << nexMove << "Step[" << stepCounter << "]: (" << pointLoc.x << ", " << pointLoc.y << ", " << pointLoc.z << ")"  << std::endl;
                            stepCounter++;
                            sleep(2);
                            mc.setBlock(pointLoc, mcpp::Blocks::AIR); 
                        }
                        else if (mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::BLUE_CARPET) {
                            bCarpetFound = true;
                            pointLoc = pointLoc + MOVE_XPLUS;
                        }
                        else {
                            nexMove = 2;
                        }
                    }
                }
                else if (nexMove == 2) {
                    while (nexMove == 2) {
                        if (!(mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::AIR) && mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::AIR) {
                            pointLoc = pointLoc + MOVE_ZPLUS;
                            mc.setBlock(pointLoc, mcpp::Blocks::LIME_CARPET);
                            std::cout << nexMove << "Step[" << stepCounter << "]: (" << pointLoc.x << ", " << pointLoc.y << ", " << pointLoc.z << ")"  << std::endl;
                            stepCounter++;
                            sleep(2);
                            mc.setBlock(pointLoc, mcpp::Blocks::AIR); 
                        }
                        else if (mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::BLUE_CARPET) {
                            bCarpetFound = true;
                            pointLoc = pointLoc + MOVE_ZPLUS;
                        }
                        else {
                            nexMove = 3;
                        }
                    }
                }
                else if (nexMove == 3) {
                    while (nexMove == 3) {
                        if (!(mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::AIR) && mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::AIR){
                            pointLoc = pointLoc + MOVE_XMINUS;
                            mc.setBlock(pointLoc, mcpp::Blocks::LIME_CARPET);
                            std::cout << nexMove << "Step[" << stepCounter << "]: (" << pointLoc.x << ", " << pointLoc.y << ", " << pointLoc.z << ")"  << std::endl;
                            stepCounter++;
                            sleep(2);
                            mc.setBlock(pointLoc, mcpp::Blocks::AIR); 
                        }
                        else if (mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::BLUE_CARPET) {
                            bCarpetFound = true;
                            pointLoc = pointLoc + MOVE_XMINUS;
                        }
                        else {
                            nexMove = 4;
                        }
                    }

                }
                else if (nexMove == 4) {
                    while (nexMove == 4) {
                        if (!(mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::AIR) && (mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::AIR)){
                            pointLoc = pointLoc + MOVE_ZMINUS;
                            mc.setBlock(pointLoc, mcpp::Blocks::LIME_CARPET);
                            std::cout << nexMove << "Step[" << stepCounter << "]: (" << pointLoc.x << ", " << pointLoc.y << ", " << pointLoc.z << ")"  << std::endl;
                            stepCounter++;
                            sleep(2);
                            mc.setBlock(pointLoc, mcpp::Blocks::AIR);    
                        }
                        else if (mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::BLUE_CARPET) {
                            bCarpetFound = true;
                            pointLoc = pointLoc + MOVE_ZMINUS;
                        }
                        else {
                            nexMove = 1;
                        }
                    }
                } 
            } 
        }
        
        mc.setBlock(pointLoc, mcpp::Blocks::LIME_CARPET);
        std::cout << "Step[" << stepCounter << "]: (" << pointLoc.x << ", " << pointLoc.y << ", " << pointLoc.z << ")"  << std::endl;
        sleep(2);
        mc.setBlock(pointLoc, mcpp::Blocks::AIR);

        
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