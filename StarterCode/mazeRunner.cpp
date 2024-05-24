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
    if(!mode) {
        mc.postToChat("RUNNING IN NORMAL MODE");
    }
    if(mode) {
        mc.postToChat("RUNNING IN TEST MODE");
    }
    
    mc.doCommand("time set day"); 

    std::string input;
    States curState = ST_Main;
    printStartText();

    int num = 0;
    //State machine for menu        
    while (curState != ST_Exit)
    {
        if(curState == ST_Main) {
            do {
                printMainMenu();  
            } while(!sanatise_input(5, num));
            curState = States(num);
        }

        if(curState ==  ST_Creators){
            do {
                printGenerateMazeMenu();
            } while (!sanatise_input(3, num));
            
            // move to create maze functions 
            // move to create maze functions random
        }

        if( curState == ST_Creators) {
            printTeamInfo();
            curState = ST_Main;
        }
    }

    printExitMassage();


    return EXIT_SUCCESS;

}