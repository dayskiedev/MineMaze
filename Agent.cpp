#include "Agent.h"

Agent::Agent()
{   
}


Agent::~Agent()
{
}

mcpp::Coordinate Agent::randStartCord(mcpp::Coordinate basePoint, int length, int width) { //Teleport player anywhere within the maze
    mcpp::MinecraftConnection mc;

    mcpp::Coordinate randomPoint;
    mcpp::Coordinate tempPoint;

    tempPoint = basePoint;

    int randomLen = rand() % (length - 1) + 1; //Random any number between 1 to the length - 1 because length will be the boundary, hence -1 will place player inside the maze
    int randomWid = rand() % (width - 1) + 1;

    tempPoint.x = tempPoint.x + randomLen; //The basepoint + the random number generated
    tempPoint.z = tempPoint.z + randomWid;
    
    while (!(mc.getBlock(tempPoint) == mcpp::Blocks::AIR)) { //If the randomPoint generated has a block, then while loop is entered
        tempPoint.x = tempPoint.x - randomLen; //The randomNum is subtracted from tempPoint
        tempPoint.z = tempPoint.z - randomWid;

        randomLen = rand() % (length - 1) + 1; //Reroll of the random
        randomWid = rand() % (width - 1) + 1;

        tempPoint.x = tempPoint.x + randomLen; //New tempPoints are generated
        tempPoint.z = tempPoint.z + randomWid;
    }

    randomPoint = tempPoint; //While loop is exited means tempValue is an empty space within the loop

    return randomPoint;
}

mcpp::Coordinate Agent::furtherstFromEntrance(mcpp::Coordinate basePoint, int length, int width) { //Furthest point from the entrance - Test mode
    mcpp::MinecraftConnection mc;

    mcpp::Coordinate farFromEntrance;
    mcpp::Coordinate tempValue;
    mc.postToChat("test mode tp");

    int l = 1;
    int w = 0;

    farFromEntrance = basePoint;

    tempValue = farFromEntrance;

    tempValue.x++; 
    tempValue.z++; //X and Z values are incremented meaning now the coordinates are the corner of the maze


    while (!(mc.getBlock(tempValue) == mcpp::Blocks::AIR)) { //To find the entrance of the maze, so while the block read is not air, loop continue 
        if (w == 0) { //Read through the first side of the maze, along the x+
            tempValue.x++;
            l++;
            if (l == length) {
                w++;
            }
        }
        else if (l == length) { //Read through the second side, along the z+
            tempValue.z++;
            w++;
            if (w == width) {
                l--;
            }
        }
        else if (w == width) { //Read through the third side, along x-
            tempValue.x--;;
            l--;
            if (l == 0) {
                w--;
            }
        }
        else if (l == 0) { //Read through fourth side, along z-
            tempValue.z--; 
        }
    }

    int identifier = 0;

    if (tempValue.x == (basePoint.x + 1)) { //If entrance is at the right hand wall
        identifier = tempValue.z - basePoint.z;
        if (identifier <= width / 2) { /*Split the wall into 2 parts, and assigns tempValue to the opposite corner, where player is teleported to*/
            tempValue.x = basePoint.x + (length - 1);
            tempValue.z = basePoint.z + (width - 1);
        }
        else if (identifier > width / 2) {
            tempValue.x = basePoint.x + (length - 1);
            tempValue.z = basePoint.z + 2;

        }
    }
    else if (tempValue.z == (basePoint.z + 1)) { //If entrance is at the bottom side wall
        identifier = tempValue.x - basePoint.x;
        if (identifier <= length / 2) {
            tempValue.x = basePoint.x + (length - 1);
            tempValue.z = basePoint.z + (width - 1);
        }
        else if (identifier > length / 2) {
            tempValue.x = basePoint.x + 2;
            tempValue.z = basePoint.z + (width - 1); 
        }
    }
    else if (tempValue.x == (basePoint.x + 9)) { //If entrance is at the left hand wall
        identifier = tempValue.z - basePoint.z;
        if (identifier <= width / 2) {
            tempValue.x = basePoint.x + 2;
            tempValue.z = basePoint.z + (width - 1); 
        }
        else if (identifier > width / 2) {
            tempValue.x = basePoint.x + 2;
            tempValue.z = basePoint.z + 2;
        }
    }
    else if (tempValue.z == (basePoint.z + 9)) { //If entrance is at the top side wall
        identifier = tempValue.x - basePoint.x;
        if (identifier <= length / 2) {
            tempValue.x = basePoint.x + (length - 1);
            tempValue.z = basePoint.z + 2;      
        }
        else if (identifier > length / 2) {
            tempValue.x = basePoint.x + 2;
            tempValue.z = basePoint.z + 2;
        }
    }

    farFromEntrance = tempValue;

    return farFromEntrance;
}


void Agent::placePlayer(mcpp::Coordinate placePoint) {
    mcpp::MinecraftConnection mc;

    mc.setPlayerPosition(placePoint);
}

void Agent::solveMaze(mcpp::Coordinate basePoint, int length, int width) {
    mcpp::MinecraftConnection mc;

    mcpp::Coordinate pointLoc = mc.getPlayerPosition();
    mcpp::Coordinate boundary;

    bCarpetFound = false; //Carpet not found

    boundary.x = basePoint.x + length;
    boundary.y = basePoint.y;
    boundary.z = basePoint.z + width;

    int boundaryX = boundary.x - pointLoc.x;
    int boundaryY = boundary.y - pointLoc.y;
    int boundaryZ = boundary.z - pointLoc.z;

    if ((boundaryX > 0 && boundaryX < (length - 1)) && (boundaryZ > 0 && boundaryZ < (width - 1)) && (boundaryY >= 0 && boundaryY < 2)) { //Check if player is within the maze
        while (!bCarpetFound) { // While blue carpet is not found, the below 'if' statements determine the direction to start
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
        solveCord.clear(); //Clear the vector
    }
    else { //If player is outside of the maze, the following will be called
        std::cout << std::endl << "Please be wintin a Maze for escape route to be shown." << std::endl;
    }
}

void Agent::printAndGuideSolve (std::vector<mcpp::Coordinate> completeVec) { // Print all coordinate in the vector which leads to the blue carpet
    mcpp::MinecraftConnection mc;

    for (unsigned long int i = 0; i < completeVec.size(); i++) {
        int j = i + 1;
        std::cout << "Step[" << j << "]: (" << completeVec[i].x << ", " << completeVec[i].y << ", " << completeVec[i].z << ")"  << std::endl; 
        mc.setBlock(completeVec[i], mcpp::Blocks::LIME_CARPET);
        sleep(2); //Time Delay
        mc.setBlock(completeVec[i], mcpp::Blocks::AIR);

        if (i == completeVec.size() - 1) {
            sleep(2);
            mc.setBlock(completeVec[i], mcpp::Blocks::BLUE_CARPET);
        }
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