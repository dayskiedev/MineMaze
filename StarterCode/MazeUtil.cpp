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
    int direction = rand() % 2;
    if(maxw - 2 <= minw) { return; }
    if(maxh - 2 <= minh) { return; }
    std::cout << "DIRECTION " << direction << std::endl;

    int heightIndex = maxh;
    int widthIndex = maxw;

    int hole = 0;

    // 0 -> 5(1,2,3,4) +1 becomes 1 -> 6 (2,3,4,5)

    // 0 -> 3 {1,2} +1 -> 1 -> 4 {2,3}
    if(direction == 0) {
        do { heightIndex = rand() % (maxh- 1) + minh + 1; }
        while((int)heightIndex % 2 != 0 || heightIndex == maxh || heightIndex == minh);
        for(int i = 0; i < 6; ++i) { MazeStructure[heightIndex][i] = 'x'; }

        do{hole = rand() % (maxh- 1) + minh + 1; }
        while(hole % 2 == 0);
        MazeStructure[heightIndex][hole] = '.';
        RecursiveFill(minh, minw, heightIndex, maxw); // lower maze
        RecursiveFill(heightIndex, minw, maxh, maxw); // upper maze
    }
    if(direction == 1){
        // 0 - > 
        do { widthIndex = rand() % (maxw- 1) + minw + 1; }
        while((int)widthIndex % 2 != 0 || widthIndex == maxw || widthIndex == minw);
        for(int i = 0; i < 6; ++i) { MazeStructure[i][widthIndex] = 'x'; }

        do{hole = rand() % (maxw- 1) + minw + 1; }
        while (hole % 2 == 0);
        MazeStructure[hole][widthIndex] = '.';
        RecursiveFill(minh, minw, maxh, widthIndex); // lower maze
        RecursiveFill(minh, widthIndex, maxh, maxw); // upper maze
    }
    //PrintMazeInfo();
    // split call 


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