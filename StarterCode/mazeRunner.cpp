#include <iostream>

#include <mcpp/mcpp.h>

#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"

#define NORMAL_MODE 0
#define TESTING_MODE 1

enum States{
    ST_Main,
    ST_GetMaze,
    ST_SolveMaze,
    ST_Creators,
    ST_Exit
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

    //State machine for menu        
    while (curState != ST_Exit)
    {

    }

    printExitMassage();


    return EXIT_SUCCESS;

}