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

    bool bCarpetFound = false;
    std::vector<mcpp::Coordinate> solveCord;

    while (!bCarpetFound) { // ADD branch for if no block behind
        unsigned int quit = 0;
        if (!(mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::AIR)) { //wall either side on Zplus and Zminus
            if (!(mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::AIR)) { //If xMinus is blocked
                while (quit == 0) {
                    if (solveCord.size() == 0) { //Straight line down xPlus
                        while (mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::AIR) {
                            pointLoc = pointLoc + MOVE_XPLUS;
                            solveCord.push_back(pointLoc);
std::cout << "MoveXP.1.1.1" << std::endl;
                        }
                        if (!(mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::AIR)) { //Meets a corner
                            pointLoc = pointLoc + MOVE_ZPLUS;
                            solveCord.push_back(pointLoc);
std::cout << "MoveZP.1.1.1.1" << std::endl;
                        }
                        else if (!(mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::AIR)) { //Meets other corner
                            pointLoc = pointLoc + MOVE_ZMINUS;
                            solveCord.push_back(pointLoc); 
std::cout << "MoveZM.1.1.1.2" << std::endl;
                        }  
                        quit++;
                    }
                    else if ((mc.getBlock(solveCord[(solveCord.size() - 1)] + MOVE_ZMINUS) == mcpp::Blocks::AIR) && solveCord.size() > 0) { //Retrace back - There's an alternate path
                        pointLoc = solveCord[(solveCord.size() - 1)] + MOVE_ZMINUS;
                        solveCord.push_back(pointLoc);
                        quit++;
std::cout << "MoveZM.1.1.2" << std::endl;
                    }
                    else if ((mc.getBlock(solveCord[(solveCord.size() - 1)] + MOVE_ZPLUS) == mcpp::Blocks::AIR) && solveCord.size() > 0) { // ^
                        pointLoc = solveCord[(solveCord.size() - 1)] + MOVE_ZPLUS;
                        solveCord.push_back(pointLoc);
                        quit++;
std::cout << "MoveZP.1.1.3" << std::endl;
                    }
                    else { //Remove wrong path from vector
                        solveCord.pop_back();
                        pointLoc = solveCord[(solveCord.size() - 1)];
std::cout << "Retrace 1.1.4" << std::endl;
                    }
                }
                quit = 0;
            }
            else if (!(mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::AIR)) { //If xPlus is blocked
                while (quit == 0) {
                    if (solveCord.size() == 0) {
                        while (mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::AIR) { //Straight line down xMinus
                            pointLoc = pointLoc + MOVE_XMINUS;
                            solveCord.push_back(pointLoc);
std::cout << "MoveXM.1.2.1" << std::endl;
                        }
                        if (!(mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::AIR)) { //Meets a corner
                            pointLoc = pointLoc + MOVE_ZMINUS;
                            solveCord.push_back(pointLoc);
std::cout << "MoveZM.1.2.1.1" << std::endl;
                        }
                        else if (!(mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::AIR)) { //Meets other corner
                            pointLoc = pointLoc + MOVE_ZPLUS;
                            solveCord.push_back(pointLoc);   
std::cout << "MoveZP.1.2.1.2" << std::endl;
                        }  
                        quit++; 
                    } 
                    else if ((mc.getBlock(solveCord[(solveCord.size() - 1)] + MOVE_ZMINUS) == mcpp::Blocks::AIR) && solveCord.size() > 0) { //Retrace back - There's an alternate path
                        pointLoc = solveCord[(solveCord.size() - 1)] + MOVE_ZMINUS;
                        solveCord.push_back(pointLoc);
                        quit++;
std::cout << "MoveZM.1.2.2" << std::endl;
                    }
                    else if ((mc.getBlock(solveCord[solveCord.size() - 1] + MOVE_ZPLUS) == mcpp::Blocks::AIR) && solveCord.size() > 0) { // ^
                        pointLoc = solveCord[(solveCord.size() - 1)] + MOVE_ZPLUS;
                        solveCord.push_back(pointLoc);
                        quit++;
std::cout << "MoveZP.1.2.3" << std::endl;
                    }    
                    else { //Remove wrong path from vector
                        solveCord.pop_back();
                        pointLoc = solveCord[(solveCord.size() - 1)];
std::cout << "Retrace.1.2.4" << std::endl;
                    }
                }
                quit = 0;
            }     
            else if ((mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::AIR && solveCord[(solveCord.size() - 2)] == pointLoc + MOVE_XMINUS) || (mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::AIR && solveCord.size() == 0)) {
                while (mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::AIR) {
                    pointLoc = pointLoc + MOVE_XPLUS;
                    solveCord.push_back(pointLoc);
                    if (!(mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::AIR)) { //Meets a corner
                            pointLoc = pointLoc + MOVE_ZPLUS;
                            solveCord.push_back(pointLoc);
std::cout << "MoveZP.1.3.1" << std::endl;
                        }
                        else if (!(mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::AIR)) { //Meets other corner
                            pointLoc = pointLoc + MOVE_ZMINUS;
                            solveCord.push_back(pointLoc);   
std::cout << "MoveZM.1.3.2" << std::endl;
                        }  
                }
            }
            else if ((mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::AIR && solveCord[(solveCord.size() - 2)] == pointLoc + MOVE_XPLUS ) || (mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::AIR && solveCord.size() == 0)) {
                while (mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::AIR) {
                    pointLoc = pointLoc + MOVE_XMINUS;
                    solveCord.push_back(pointLoc);
                    if (!(mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::AIR)) { //Meets a corner
                        pointLoc = pointLoc + MOVE_ZMINUS;
                        solveCord.push_back(pointLoc);
std::cout << "MoveZM.1.4.1" << std::endl;
                        }
                    else if (!(mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::AIR)) { //Meets other corner
                        pointLoc = pointLoc + MOVE_ZPLUS;
                        solveCord.push_back(pointLoc);   
std::cout << "Move.ZP.1.4.2" << std::endl;
                        }  
                }
                
std::cout << "1.4" << std::endl;
            }
        }
        
        
        else if (!(mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::AIR)) { //wall either side on Xplus and Xminus
std::cout << "2" << std::endl;
            
            if (!(mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::AIR)) { //If zminus is blocked
std::cout << "2.1" << std::endl;
                while (quit == 0) {
                    if (solveCord.size() == 0) { //Straight line down zPlus
std::cout << "2.1.1" << std::endl;
                        while (mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::AIR) {
                            pointLoc = pointLoc + MOVE_ZPLUS;
                            solveCord.push_back(pointLoc);
                        }
                        if (!(mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::AIR)) { //Meets a corner
                            pointLoc = pointLoc + MOVE_XPLUS;
                            solveCord.push_back(pointLoc);
std::cout << "2.1.1.1" << std::endl;
                        }
                        else if (!(mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::AIR)) { //Meets other corner
                            pointLoc = pointLoc + MOVE_XMINUS;
                            solveCord.push_back(pointLoc); 
std::cout << "2.1.1.2" << std::endl;
                        } 
                        quit++;
                    }
                    else if ((mc.getBlock(solveCord[(solveCord.size() - 1)] + MOVE_XMINUS) == mcpp::Blocks::AIR) && solveCord.size() > 0) { //Retrace back - There's an alternate path
                        pointLoc = solveCord[(solveCord.size() - 1)] + MOVE_XMINUS;
                        solveCord.push_back(pointLoc);
                        quit++;
std::cout << "2.1.2" << std::endl;
                    }
                    else if ((mc.getBlock(solveCord[(solveCord.size() - 1)] + MOVE_XPLUS) == mcpp::Blocks::AIR) && solveCord.size() > 0) { // ^
                        pointLoc = solveCord[(solveCord.size() - 1)] + MOVE_XPLUS;
                        solveCord.push_back(pointLoc);
                        quit++;
std::cout << "2.1.3" << std::endl;
                    }
                    else { //Remove wrong path from vector
                        solveCord.pop_back();
                        pointLoc = solveCord[(solveCord.size() - 1)];
std::cout << "2.1.4" << std::endl;
                    }
                }
                quit = 0;

            }
            
            else if (!(mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::AIR)) {
std::cout << "2.2" << std::endl;
                while (quit == 0) {
                    if (solveCord.size() == 0) { //Straight line down zPlus
std::cout << "2.2.1" << std::endl;
                        while (mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::AIR) {
                            pointLoc = pointLoc + MOVE_ZMINUS;
                            solveCord.push_back(pointLoc);
                        }
                        if (!(mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::AIR)) { //Meets a corner
                            pointLoc = pointLoc + MOVE_XPLUS;
                            solveCord.push_back(pointLoc);
std::cout << "2.1.1.1" << std::endl;
                        }
                        else if (!(mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::AIR)) { //Meets other corner
                            pointLoc = pointLoc + MOVE_XMINUS;
                            solveCord.push_back(pointLoc);   
std::cout << "2.1.1.2" << std::endl;
                        } 
                        quit++;
                    }
                    else if ((mc.getBlock(solveCord[(solveCord.size() - 1)] + MOVE_XMINUS) == mcpp::Blocks::AIR) && solveCord.size() > 0) { //Retrace back - There's an alternate path
                        pointLoc = solveCord[(solveCord.size() - 1)] + MOVE_XMINUS;
                        solveCord.push_back(pointLoc);
                        quit++;
std::cout << "2.2.2" << std::endl;
                    }
                    else if ((mc.getBlock(solveCord[(solveCord.size() - 1)] + MOVE_XPLUS) == mcpp::Blocks::AIR) && solveCord.size() > 0) { // ^
                        pointLoc = solveCord[(solveCord.size() - 1)] + MOVE_XPLUS;
                        solveCord.push_back(pointLoc);
                        quit++;
std::cout << "movXp" << std::endl;
                    }
                    else { //Remove wrong path from vector
                        solveCord.pop_back();
                        pointLoc = solveCord[(solveCord.size() - 1)];
std::cout << "2.2.4" << std::endl;
                    }
                    
                }
                quit = 0;
            }
            else if ((mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::AIR && solveCord[(solveCord.size() - 2)] == pointLoc + MOVE_ZPLUS) || (mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::AIR && solveCord.size() == 0))  {
                while ((mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::AIR)) {
                    pointLoc = pointLoc + MOVE_ZMINUS;
                    solveCord.push_back(pointLoc);
                    if (!(mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::AIR)) { //Meets a corner
                            pointLoc = pointLoc + MOVE_XPLUS;
                            solveCord.push_back(pointLoc);
std::cout << "moveXp" << std::endl;
                        }
                        else if (!(mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::AIR)) { //Meets other corner
                            pointLoc = pointLoc + MOVE_XMINUS;
                            solveCord.push_back(pointLoc);   
std::cout << "moveXm" << std::endl;
                        } 
                }
            }
            else if ((mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::AIR && solveCord[(solveCord.size() - 2)] == pointLoc + MOVE_ZMINUS) || (mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::AIR && solveCord.size() == 0) ) {
                while ((mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::AIR)) {
                    pointLoc = pointLoc + MOVE_ZPLUS;
                    solveCord.push_back(pointLoc);
                    if (!(mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::AIR)) { //Meets a corner
                            pointLoc = pointLoc + MOVE_XPLUS;
                            solveCord.push_back(pointLoc);
std::cout << "2.4.1" << std::endl;
                        }
                        else if (!(mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::AIR) && !(mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::AIR)) { //Meets other corner
                            pointLoc = pointLoc + MOVE_XMINUS;
                            solveCord.push_back(pointLoc); 
std::cout << "2.4.2" << std::endl;
                        } 
                }
                
            }
        }    
        else if ((mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::BLUE_CARPET) || (mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::BLUE_CARPET) || 
        (mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::BLUE_CARPET) || (mc.getBlock(pointLoc + MOVE_ZPLUS) == mcpp::Blocks::BLUE_CARPET)) {
std::cout << "3" << std::endl;
            if ((mc.getBlock(pointLoc + MOVE_XMINUS) == mcpp::Blocks::BLUE_CARPET)) { // BlueCarpet Found
                pointLoc = pointLoc + MOVE_XMINUS;
            }
            else if ((mc.getBlock(pointLoc + MOVE_XPLUS) == mcpp::Blocks::BLUE_CARPET)) {
                pointLoc = pointLoc + MOVE_XPLUS;
            }
            else if ((mc.getBlock(pointLoc + MOVE_ZMINUS) == mcpp::Blocks::BLUE_CARPET)) {
                pointLoc = pointLoc + MOVE_ZMINUS;
            }
            else {
                pointLoc = pointLoc + MOVE_ZPLUS;
            }
            solveCord.push_back(pointLoc);
            bCarpetFound = true;
        }
    }
    printAndGuideSolve(solveCord);   
}
    


void Agent::printAndGuideSolve (std::vector<mcpp::Coordinate> completeVec) {
    mcpp::MinecraftConnection mc;

    for (int i = 0; i < completeVec.size(); i++) {
        int j = i + 1;
        std::cout << "Step[" << j << "]: (" << completeVec[i].x << ", " << completeVec[i].y << ", " << completeVec[i].z << ")"  << std::endl;
        mc.setBlock(completeVec[i], mcpp::Blocks::LIME_CARPET);
        sleep(2);
        mc.setBlock(completeVec[i], mcpp::Blocks::AIR);
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