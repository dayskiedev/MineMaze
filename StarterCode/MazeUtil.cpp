#include "MazeUtil.h"
#include <mcpp/mcpp.h>

char** MazeUtil::GetStructure() { return MazeStructure; } 

void MazeUtil::CreateStructure() {
    // get basepoint for maze
    mcpp::MinecraftConnection mc;
    std::cout << "In Minecraft, navigate to where you need the maze to be built and type - done" << std::endl;
    std::string input;
    std::cin >> input; 
    while (input.compare("done"))
    {
        std::cout << "Invalid input! please enter 'done' when you have found a desirable location!" << std::endl;
        std::cin >> input;
    }

    basePoint = mcpp::Coordinate(mc.getPlayerPosition());
    
    std::cout << "Enter the length and width of the maze:" << std::endl;
    std::cin >> length; //TODO ADD SAFTEY CHECKS 
    std::cin >> width;

    MazeStructure = new char*[length];
    for(int i = 0; i < width; i++) {
        MazeStructure[i] = new char[width];
    }
}

void MazeUtil::CreateStructureTerminal() {
    CreateStructure();

    std::cout << "Enter the maze structure:" << std::endl;
    // read in input from terminal
    char c;
    for(int i = 0; i < length; ++i) {
        for(int j = 0; j < width; ++j) {
            std::cin >> c;
            MazeStructure[i][j] = c;
        }
    }

    std::cout << "Maze read successfully!" << std::endl;
    PrintMazeInfo();
}

void MazeUtil::CreatureStructureRandom(bool mode) {
    CreateStructure();
    char w = 'X';
    char a = '.';
    // generate an empty maze
    // the top and bottom xxx
    for(int i = 0; i < width; ++i) { 
        MazeStructure[0][i] = w;
        MazeStructure[length-1][i] = w;
    }
    for(int i = 1; i < length - 1; ++i) {
        MazeStructure[i][width-1] = w;
        MazeStructure[i][0] = w;
        for(int j = 1; j < width - 1; ++j) {
            MazeStructure[i][j] = a;
        }
    }
    // could combine them into a single oop

    
    // some kind of linked list to deal with the recursive
    

    PrintMazeInfo();
}

void MazeUtil::PrintMazeInfo() {
    std::cout << "**Printing Maze**" << std::endl;
    std::cout << "BasePoint: " << basePoint << std::endl;
    std::cout << "Structure:" << std::endl;
    for(int i = 0; i < length; ++i) {
        for(int j = 0; j < width; ++j) {
            std::cout << MazeStructure[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << "**End Printing Maze**" << std::endl;
}

mcpp::Coordinate MazeUtil::MazeRandStartCoord() {
    mcpp::MinecraftConnection mc;
    if(length == 0) { 
        mc.postToChat("No Maze Detected Unable To Teleport Player...");
        return mc.getPlayerPosition();
    }

    return mc.getPlayerPosition();
}


MazeUtil::~MazeUtil() {
}