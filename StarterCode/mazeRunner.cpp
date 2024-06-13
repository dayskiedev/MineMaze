#include <iostream>

#include <mcpp/mcpp.h>

#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"
#include "MazeUtil.h"

enum States
{
    ST_Main = 0,
    ST_CreateMaze = 1,
    ST_BuildMaze = 2,
    ST_SolveMaze = 3,
    ST_Creators = 4,
    ST_Exit = 5
};

int main(int argc, char *argv[])
{
    mcpp::MinecraftConnection mc;
    bool mode = false;
    bool enhance = false; // enchance mode
    if (argc > 1) { 
        for(int i = 0; i < argc; ++i) {
            if(!mode) { mode = compareCharStr(argv[i], "-testmode"); } 
            if(!enhance) { enhance = compareCharStr(argv[i], "-enhance"); } 
        } // loops through every extra argument provided to see if they match either of these
        // checks if they are false to then see if they are true, because the current input could be -enhance
        // and while testmode is already true this could otherwise set it back to false unintentionally
    }

    if (!mode) { mc.postToChat("RUNNING IN NORMAL MODE"); }
    if (mode) { mc.postToChat("RUNNING IN TEST MODE"); }

    if (enhance) { mc.postToChat("RUNNING WITH ENHANCMENTS"); }

    mc.doCommand("time set day");

    MazeUtil mu;
    Agent agent;

    std::string input;
    States curState = ST_Main;
    printStartText();

    int stateNum = 0;
    // State machine for menu
    while (curState != ST_Exit)
    {
        if (curState == ST_Main) {
            do
            {
                printMainMenu();
            } while (!sanatiseInput(5, stateNum));
            curState = States(stateNum);
        }

        if (curState == ST_CreateMaze) {
            do
            {
                printGenerateMazeMenu();
            } while (!sanatiseInput(3, stateNum));

            // due to the input being sanatised it should only ever be 1-3 when it reaches here
            if (stateNum == 1) { mu.CreateStructureTerminal(enhance); }
            if (stateNum == 2) { mu.CreatureStructureRandom(mode); }
            if (stateNum == 3) { curState = ST_Main; }

            curState = ST_Main;
        }

        if (curState == ST_BuildMaze) {
            std::cout << "BUILDING MAZE..." << std::endl;
            curState = ST_Main;

            Maze(mu.getBasePoint(), mu.getLength(), mu.getWidth(), mu.GetStructure(), mode);
        }

        if (curState == ST_SolveMaze) {
            do
            {
                printSolveMazeMenu();
            } while (!sanatiseInput(3, stateNum));

            if (stateNum == 1)
            {
                std::cout << "Solve Manually" << std::endl;
                agent.placePlayer(mu.MazeRandStartCoord(), mode);
            }
            if (stateNum == 2)
            {
                std::cout << "Show escape route" << std::endl;
                agent.solveMaze();
            }
            if (stateNum == 3)
            {
                curState = ST_Main;
            }

            curState = ST_Main;
        }

        if (curState == ST_Creators)
        {
            printTeamInfo();
            curState = ST_Main;
        }
    }

    printExitMassage();

    return EXIT_SUCCESS;
}