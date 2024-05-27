#include <iostream>

#include <mcpp/mcpp.h>

#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"

#define NORMAL_MODE 0
#define TESTING_MODE 1

enum States{
    ST_Main = 0,
    ST_CreateMaze = 1,
    ST_BuildMaze = 2,
    ST_SolveMaze = 3,
    ST_Creators = 4,
    ST_Exit = 5
};

int main(void){
    mcpp::MinecraftConnection mc; 

    bool mode = NORMAL_MODE;
    //read Mode
    if(!mode) { mc.postToChat("RUNNING IN NORMAL MODE"); }
    if(mode) { mc.postToChat("RUNNING IN TEST MODE"); }
    
    mc.doCommand("time set day"); 

    std::string input;
    States curState = ST_Main;
    printStartText();

    int stateNum = 0;
    //State machine for menu        
    while (curState != ST_Exit)
    {
        if(curState == ST_Main) {
            do {
                printMainMenu();  
            } while(!sanatiseInput(5, stateNum));
            curState = States(stateNum);
        }

        if(curState == ST_CreateMaze){
            do {
                printGenerateMazeMenu();
            } while (!sanatiseInput(3, stateNum));

            // due to the input being sanatised it should only ever be 1-3 when it reaches here
            // move to create maze functions 
            if(stateNum == 1) { std::cout << "move to function to generate a maze from the terminal" << std::endl; }
            // move to create maze functions random
            if(stateNum == 2) { std::cout << "move to function to generate random maze from height width" << std::endl; }
            if(stateNum == 3) { curState = ST_Main; }
        }

        if(curState == ST_BuildMaze) {
            std::cout << "BUILDING MAZE..." << std::endl;
            curState = ST_Main;
        }

        if(curState == ST_SolveMaze) {
            std::cout << "SOLVING MAZE..." << std::endl;
            curState = ST_Main;
        }

        if(curState == ST_Creators) {
            printTeamInfo();
            curState = ST_Main;
        }
    }

    printExitMassage();

    return EXIT_SUCCESS;

}