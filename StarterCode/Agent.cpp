#include "Agent.h"

Agent::Agent()
{   
}


Agent::~Agent()
{
}

void Agent::placePlayer(mcpp::Coordinate basePoint, bool mode) {
    mcpp::MinecraftConnection mc;
    
    // if (!mode) {
    //     = normal
    // }
    // else if (mode) {
    //     = test
    // }

    mc.setPlayerPosition(basePoint);
}

void Agent::solveMaze() {
    mcpp::MinecraftConnection mc;

    mcpp::Coordinate pointLoc = mc.getPlayerPosition();

    bCarpetFound = false; //Carpet not found

    while (!bCarpetFound) {
        int vectorCounter = 0; 
        if (mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::AIR) {// Move to zPlus if it is empty 
            zPlus(pointLoc, vectorCounter); 
        }
        else if (mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::AIR) {// Move to xPlus if it is empty 
            xPlus(pointLoc, vectorCounter);
        }
        else if (mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::AIR) {// Move to zMinus if it is empty 
            zMinus(pointLoc, vectorCounter);
        }
        else if (mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::AIR) {// Move to xMinus if it is empty 
            xMinus(pointLoc, vectorCounter);
        }
        bCarpetFound = true;
    }
    printAndGuideSolve(solveCord); //Print solveCord vector - the solution to the maze
    solveCord.clear();
}

void Agent::printAndGuideSolve (std::vector<mcpp::Coordinate> completeVec) { 
    mcpp::MinecraftConnection mc;

    for (unsigned long int i = 0; i < completeVec.size(); i++) {
        int j = i + 1;
        std::cout << "Step[" << j << "]: (" << completeVec[i].x << ", " << completeVec[i].y << ", " << completeVec[i].z << ")"  << std::endl; 
        mc.setBlock(completeVec[i], mcpp::Blocks::LIME_CARPET);
        sleep(2); //Time Delay
        mc.setBlock(completeVec[i], mcpp::Blocks::AIR);
    }
}

void Agent::zPlus(mcpp::Coordinate currentCor, int vecCounter) {
    mcpp::MinecraftConnection mc;

    currentCor = currentCor + MOVE_ZPLUS;
    solveCord.push_back(currentCor);
    vecCounter++;
    
    if (mc.getBlock(currentCor + MOVE_ZPLUS) == mcpp::Blocks::BLUE_CARPET) {
        currentCor = currentCor + MOVE_ZPLUS;
        solveCord.push_back(currentCor); 
    }
    else if (mc.getBlock(currentCor + MOVE_XMINUS) == mcpp::Blocks::AIR) {
        xMinus(currentCor, vecCounter);
    }
    else if (mc.getBlock(currentCor + MOVE_ZPLUS) == mcpp::Blocks::AIR) {
        zPlus(currentCor, vecCounter);
    }
    else if (mc.getBlock(currentCor + MOVE_XPLUS) == mcpp::Blocks::AIR) {
        xPlus(currentCor, vecCounter);
    }
    else if (mc.getBlock(currentCor + MOVE_ZMINUS) == mcpp::Blocks::AIR) {
        zMinus(currentCor, vecCounter);
    }
}

void Agent::zMinus(mcpp::Coordinate currentCor, int vecCounter) {
    mcpp::MinecraftConnection mc;

    currentCor = currentCor + MOVE_ZMINUS;
    solveCord.push_back(currentCor);
    vecCounter++;

    if (mc.getBlock(currentCor + MOVE_ZMINUS) == mcpp::Blocks::BLUE_CARPET) {
        currentCor = currentCor + MOVE_ZMINUS;
        solveCord.push_back(currentCor);
    }
    else if (mc.getBlock(currentCor + MOVE_XPLUS) == mcpp::Blocks::AIR) {
        xPlus(currentCor, vecCounter);
    }
    else if (mc.getBlock(currentCor + MOVE_ZMINUS) == mcpp::Blocks::AIR) {
        zMinus(currentCor, vecCounter);
    }
    else if (mc.getBlock(currentCor + MOVE_XMINUS) == mcpp::Blocks::AIR) {
        xMinus(currentCor, vecCounter);
    }
    else if (mc.getBlock(currentCor + MOVE_ZPLUS) == mcpp::Blocks::AIR) {
        zPlus(currentCor, vecCounter);
    }
}

void Agent::xMinus(mcpp::Coordinate currentCor, int vecCounter) {
    mcpp::MinecraftConnection mc;

    currentCor = currentCor + MOVE_XMINUS;
    solveCord.push_back(currentCor);
    vecCounter++;

    if (mc.getBlock(currentCor + MOVE_XMINUS) == mcpp::Blocks::BLUE_CARPET) {
        currentCor = currentCor + MOVE_XMINUS;
        solveCord.push_back(currentCor);
    }
    else if (mc.getBlock(currentCor + MOVE_ZMINUS) == mcpp::Blocks::AIR) {
        zMinus(currentCor, vecCounter);
    }
    else if (mc.getBlock(currentCor + MOVE_XMINUS) == mcpp::Blocks::AIR) {
        xMinus(currentCor, vecCounter);
    }
    else if (mc.getBlock(currentCor + MOVE_ZPLUS) == mcpp::Blocks::AIR) {
        zPlus(currentCor, vecCounter);
    }
    else if (mc.getBlock(currentCor + MOVE_XPLUS) == mcpp::Blocks::AIR) {
        xPlus(currentCor, vecCounter);
    }
}

void Agent::xPlus(mcpp::Coordinate currentCor, int vecCounter) {
    mcpp::MinecraftConnection mc;

    currentCor = currentCor + MOVE_XPLUS;
    solveCord.push_back(currentCor);
    vecCounter++;

    if (mc.getBlock(currentCor + MOVE_ZPLUS) == mcpp::Blocks::BLUE_CARPET) {
        currentCor = currentCor + MOVE_ZPLUS;
        solveCord.push_back(currentCor);
    }
    else if (mc.getBlock(currentCor + MOVE_ZPLUS) == mcpp::Blocks::AIR) {
        zPlus(currentCor, vecCounter);
    }
    else if (mc.getBlock(currentCor + MOVE_XPLUS) == mcpp::Blocks::AIR) {
        xPlus(currentCor, vecCounter);
    }
    else if (mc.getBlock(currentCor + MOVE_ZMINUS) == mcpp::Blocks::AIR) {
        zMinus(currentCor, vecCounter);
    }
    else if (mc.getBlock(currentCor + MOVE_XMINUS) == mcpp::Blocks::AIR) {
        xMinus(currentCor, vecCounter);
    }
}