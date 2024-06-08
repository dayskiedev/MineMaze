#include "MazeUtil.h"
#include <mcpp/mcpp.h>
#include <stdlib.h>
#include <random>

char** MazeUtil::GetStructure() { return MazeStructure; } 

mcpp::Coordinate MazeUtil::MazeRandStartCoord() {
    mcpp::MinecraftConnection mc;
    int x;
    int y = mc.getPlayerPosition().y;
    int z;

    do{
        x = rand() % width;
        z = rand() % length;
    }
    while (MazeStructure[y][z] != '.');
    
    return mcpp::Coordinate(x,y,z);
}

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

    basePoint = mc.getPlayerPosition();
    
    std::cout << "Enter the length and width of the maze:" << std::endl; 
    std::cin >> length;// no input validation
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

// void CreateMazeEntrance() {
//     int dir = rand() % 4 // 0 = up 1 = left 2 = right 3 = down
// }

void MazeUtil::CreatureStructureRandom(bool mode) {
    CreateStructure();

    char w = 'x';
    char a = '.';   


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
    RecursiveFill(0,0, length-1, width - 1);
    // place entrance

    PrintMazeInfo();
}

void MazeUtil::RecursiveFill(int minh, int minw, int maxh, int maxw) {
    // works when len and wid are same but not when different?
    std::random_device rnd;

    std::uniform_int_distribution<int> dir(0,1);
    std::uniform_int_distribution<int> rndWidth(minw + 1, maxw - 1);
    std::uniform_int_distribution<int> rndHeight(minh + 1, maxh -1);

    int direction = dir(rnd); // where 0 = horizontal
    int wall = 0;

    if(maxh - 2 <= minh) { return; }
    if(maxw - 2 <= minw) { return; }

    if(direction == 0) {
        int horizontalSplit = 0;
        do{ horizontalSplit = rndHeight(rnd); }
        while(horizontalSplit % 2); // repeat until even number
        for(int i = minw; i < maxw; ++i) { MazeStructure[horizontalSplit][i] = 'x'; }

        //generate hole
        do{ wall = rndWidth(rnd); }
        while ( wall % 2 == 0);
        MazeStructure[horizontalSplit][wall] = '.';

        // now we treat the horizontal split as the max for the top square and the min for the bottom square
        RecursiveFill(minh, minw, horizontalSplit, maxw);
        RecursiveFill(horizontalSplit, minw, maxh, maxw);
    }
    if(direction == 1) {
        int verticalSplit = 0;
        do { verticalSplit = rndWidth(rnd); }
        while(verticalSplit % 2 != 0);
        // genertaing vertical line
        for(int i = minh; i < maxh; ++i) { MazeStructure[i][verticalSplit] = 'x'; }

        // generating hole
        do{ wall = rndHeight(rnd); }
        while (wall % 2 == 0);
        MazeStructure[wall][verticalSplit] = '.'; 

        RecursiveFill(minh, minw, maxh, verticalSplit);
        RecursiveFill(minh, verticalSplit, maxh, maxw);
    }
}

void MazeUtil::PrintMazeInfo() {
    std::cout << "**Printing Maze**" << std::endl;
    std::cout << "BasePoint: " << basePoint << std::endl;
    std::cout << "Structure:" << std::endl;
    for(int i = 0; i < length; ++i) {
        for(int j = 0; j < width; ++j) {
            std::cout << MazeStructure[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "**End Printing Maze**" << std::endl;
}


MazeUtil::~MazeUtil() {
    for(int i = 0; i < length; ++i) {
        delete[] MazeStructure[i]; // delete inner arrays
    }

    delete[] MazeStructure;
}