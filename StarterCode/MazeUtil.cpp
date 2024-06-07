#include "MazeUtil.h"
#include <mcpp/mcpp.h>
#include <stdlib.h>

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
    std::cin >> length;
    std::cin >> width;

    MazeStructure = new char*[length];
    for(int i = 0; i < width; i++) {
        MazeStructure[i] = new char[width];
    }
}

void MazeUtil::CreateStructureTerminal() {
    CreateStructure();

    std::cout << "Enter the maze structure (" << length << "x" << width << "): " << std::endl;
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
    // week 2 class 1
    char w = 'x';
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
    // odd for walls
    // even for open

    // start with open maze
    // pick horizontal 0 or vertical 1
    // pick random odd number between 1 and width (niether of these tho)
    // place wall pick even number and place opening

    RecursiveFill(0,0, length - 1, width - 1);

    //PrintMazeInfo();

    PrintMazeInfo();
}

void MazeUtil::RecursiveFill(int minh, int minw, int maxh, int maxw) {
    // shrink array each iteration
    // generateMaze(1,2,3,4)
    //  generateMaze(UPPPER)
    //  generateMaze(lower)
    // xxxxxxx 6
    // walls can only go on even spaces 
    //passages must be on odd spaces
    std::cout << "Inside recursion " << std::endl;
    if(maxh - 2 == minh) { return; }
    // exit condition

    // rand() % 2; // 0 = horizontal 1 = vertical
    //int direction = 0;

    int heightIndex;

    // 0 -> 5(1,2,3,4) +1 becomes 1 -> 6 (2,3,4,5)
    do { heightIndex = rand() % (maxh- 1) + minh + 1; }
    while((int)heightIndex % 2 != 0);
    // // pick even number between min and max height of 
    // std::cout << "SELECTED ROW " << heightIndex << std::endl;
    for(int i = minw; i < maxw; ++i) { MazeStructure[heightIndex][i] = 'x'; }
    //int minHeight = mh;
    //PrintMazeInfo();
    // do checks to see if we can call function again then call it again
    // supposd to call it twice
    // newrecursive(m)

    // upper function once this breaks call lower function
    // lower function 
    ///std::cout << "SELECTED ROW " << heightIndex << std::endl;
    RecursiveFill(minh, 0, heightIndex, 0); // lower maze
    RecursiveFill(heightIndex, 0, maxh, 0); // upper maze
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