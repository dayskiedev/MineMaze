#include "Agent.h"

Agent()
{   
}


Agent::~Agent()
{
}

mcpp::Coordinate Agent::randStartCord(mcpp::Coordinate basePoint, int length, int width) {
    mcpp::MinecraftConnection mc;

    mcpp::Coordinate randomPoint;
    mcpp::Coordinate tempPoint;

    tempPoint = basePoint;

    int randomLen = rand() % (length - 1) + 1;
    int randomWid = rand() % (width - 1) + 1;

    tempPoint.x = tempPoint.x + randomLen; 
    tempPoint.z = tempPoint.z + randomWid;
    
    while (!(mc.getBlock(tempPoint) == mcpp::Blocks::AIR)) { //Still Teleporting inside of block
        tempPoint.x = tempPoint.x - randomLen; 
        tempPoint.z = tempPoint.z - randomWid;

        randomLen = rand() % (length - 1) + 1;
        randomWid = rand() % (width - 1) + 1;

        tempPoint.x = tempPoint.x + randomLen; 
        tempPoint.z = tempPoint.z + randomWid;
    }

    randomPoint = tempPoint;

    return randomPoint;
}

mcpp::Coordinate Agent::furtherstFromEntrance(mcpp::Coordinate basePoint, int length, int width) {
    mcpp::MinecraftConnection mc;


    mcpp::Coordinate farFromEntrance;
    mcpp::Coordinate tempValue;
    mc.postToChat("test mode tp");

    int l = 1;
    int w = 1;

    farFromEntrance = basePoint;

    farFromEntrance.x = basePoint.x + length;
    farFromEntrance.z = basePoint.z + width;

    tempValue = farFromEntrance;

    while (!(mc.getBlock(tempValue) == mcpp::Blocks::AIR)) {
        if (w > 1) {
            tempValue.z = farFromEntrance.z + w;
            w++;
        }
        
        tempValue.x = farFromEntrance.x - l;

        if (!(mc.getBlock(tempValue) == mcpp::Blocks::AIR)) {
            tempValue.x = farFromEntrance.x + l;
            l++;

            tempValue.z = farFromEntrance.z - w;
        }
    }

    farFromEntrance = tempValue;

    return farFromEntrance;
}


void Agent::placePlayer(mcpp::Coordinate placePoint) {
    mcpp::MinecraftConnection mc;

    mc.setPlayerPosition(placePoint);
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
    mc.setBlock(solveCord[solveCord.size() - 1], mcpp::Blocks::BLUE_CARPET);
    solveCord.clear(); //Clear the vector
}

void Agent::printAndGuideSolve (std::vector<mcpp::Coordinate> completeVec) { // Print all coordinate in the vector which leads to the blue carpet
    mcpp::MinecraftConnection mc;

    for (unsigned long int i = 0; i < completeVec.size(); i++) {
        int j = i + 1;
        std::cout << "Step[" << j << "]: (" << completeVec[i].x << ", " << completeVec[i].y << ", " << completeVec[i].z << ")"  << std::endl; 
        mc.setBlock(completeVec[i], mcpp::Blocks::LIME_CARPET);
        sleep(2); //Time Delay
        mc.setBlock(completeVec[i], mcpp::Blocks::AIR);
    }
}

    /*
    The 4 functions zPlus, zMinus, xPlus and xMinus are done so to mimic a first-person pov right hand solve rule
    this is achieved by having each direction zPlus, zMinus ... have thier own seperate and different direction of thre "right"
    the functions keep calling each other until the blue carpet is stubled upon, only then will the function calling stop
    and be directed back to the while loop for an exit. 
    */
void Agent::zPlus(mcpp::Coordinate currentCor, int vecCounter) { 
    mcpp::MinecraftConnection mc;

    currentCor = currentCor + MOVE_ZPLUS; //After zPlus function is called, the currentCoordinates are incremented by moveZplus
    solveCord.push_back(currentCor); //Current Coord is placed at the end of the vector.
    vecCounter++; //The counter for vec is incremented by one, this is to keep track of the "steps" in the solve
    
    if (mc.getBlock(currentCor + MOVE_ZPLUS) == mcpp::Blocks::BLUE_CARPET) { //If it is a blueCarpet, function will return to the main
        currentCor = currentCor + MOVE_ZPLUS; //Current Coord in now Current Coord + Direction
        solveCord.push_back(currentCor);  //Coord is stored in vector
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