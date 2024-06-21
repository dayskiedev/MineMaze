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
    bool mazeExist = false; // check if there is maze present
    if (argc > 1)
    {
        for (int i = 0; i < argc; ++i)
        {
            if (!mode) { mode = compareCharStr(argv[i], "-testmode"); }
            if (!enhance) { enhance = compareCharStr(argv[i], "-enhance"); }
        } // loops through every extra argument provided to see if they match either of these checks if they are false to then see if they are true, because the current input could be -enhance
          // and while testmode is already true this could otherwise set it back to false unintentionally
    }

    if (!mode) { mc.postToChat("RUNNING IN NORMAL MODE"); }
    if (mode) { mc.postToChat("RUNNING IN TEST MODE"); }
    if (enhance) { mc.postToChat("RUNNING WITH ENHANCMENTS"); }

    mc.doCommand("time set day");

    MazeUtil mu(mode, enhance);
    Agent agent;
    Maze maze;

    std::string input;
    States curState = ST_Main;
    printStartText();

    int stateNum = 0;
    // State machine for menu
    while (curState != ST_Exit)
    {
        if (curState == ST_Main) {
            do {
                printMainMenu();
            } while (!sanatiseInput(5, stateNum));
            curState = States(stateNum);
        }

        if (curState == ST_CreateMaze) {
            do {
                printGenerateMazeMenu();
            } while (!sanatiseInput(3, stateNum));

            // due to the input being sanatised it should only ever be 1-3 when it reaches here
            if (stateNum == 1) { mu.CreateStructureTerminal(); }
            if (stateNum == 2) { mu.CreatureStructureRandom(); }

            curState = ST_Main; // third option already takes us here so no nude for a third if statement
        }

        if (curState == ST_BuildMaze) {
            std::cout << "BUILDING MAZE..." << std::endl;
            curState = ST_Main;
            maze.setFields(mu.getBasePoint().clone(), mu.getLength(), mu.getWidth(), mu.GetStructure(), mode);
            maze.flattenTerrain();
            maze.buildMaze();
            mazeExist = true; //Once maze is built, mazeExist is true
        }

        if (curState == ST_SolveMaze) {
            do {
                printSolveMazeMenu();
            } while (!sanatiseInput(3, stateNum));

            if (stateNum == 1 && mazeExist)
            {
                // if in testmode we want to place the player furtherst from the
                if (mode) { agent.placePlayer(agent.furtherstFromEntrance(mu.getBasePoint(), mu.getLength(), mu.getWidth())); }
                else { agent.placePlayer(agent.randStartCord(mu.getBasePoint(), mu.getLength(), mu.getWidth())); }
            }
            if (stateNum == 2 && mazeExist) { agent.solveMaze(mu.getBasePoint(), mu.getLength(), mu.getWidth()); }

            if (!mazeExist) { //If maze does not exist then the message is printed
                std::cout << std::endl << "Please ensure a Maze is built." << std::endl;
            }

            curState = ST_Main;
        }

        if (curState == ST_Creators) {
            printTeamInfo();
            curState = ST_Main;
        }
    }
    printExitMassage();

    return EXIT_SUCCESS;
}