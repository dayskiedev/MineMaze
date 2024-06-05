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

    basePoint = mcpp::Coordinate(0,0,0);
    
    std::cout << "Enter the length and width of the maze:" << std::endl;
    std::cin >> length; //TODO ADD SAFTEY CHECKS CHECK IF INPUT IS NOT A NUMBER *OR* IF IT IS AN EVEN NUMBER, WE CANT HAVE THAT!
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

    RecursiveFill(0,0, false, false);

    PrintMazeInfo();
}

void MazeUtil::RecursiveFill(int mh, int mw, bool sh, bool sv) {
    // what is true when the function is called?
    // the inside of the maze has not been filled

    // what is true when the function returns
    // when there are no more possible spots for it to place walls

    // CURRENT ISSUES
    // - DOESNT KNOW IF HORIZONTAL / VERTICAL SLAB HAS ALREADY BEEN PLACED
    // - DOESNT CUT OUT A GAP TO GET IN


    // for a 7x7 grid
    // 0123456
    // xxxxxxx 0
    // x     x 1
    // x     x 2
    // x     x 3
    // x     x 4
    // x     x 5
    // xxxxxxx 6
    // walls can only go on even spaces 
    //passages must be on odd spaces

    // rand() % 2; // 0 = horizontal 1 = vertical
    int direction = rand() % 2;
    //int minHeight = mh;
    int minWidth = mw;  
    int minHeight = mh;

    bool stopHorizontal = sh;
    bool stopVertical = sv;

    if(stopHorizontal && stopVertical) { return;}

    if(direction == 0 && !stopHorizontal) {

        int heightIndex;
        do{ heightIndex = rand() % (length - 4 - minHeight) + minHeight + 2; }
        while (heightIndex % 2 != 0);

       //std::cout << "HEIGHT PICKED: " << heightIndex << std::endl;
        // then create horizontal wall
        for(int i = minWidth; i < width; ++i) { MazeStructure[heightIndex][i] = 'x'; }

        // check if current position minus 2 is equal to the minimum heihgt 
        std::cout << "cur ht index: " << heightIndex << " cur minheight " << minHeight << std::endl;
        if(heightIndex - 2 == minHeight) { 
            if(heightIndex + 2 != length - 1) { minHeight = heightIndex; } // if this condition runs it means we still have room to fill!
            else {
                std::cout << "it should stop here"  << std::endl;
                stopHorizontal = true;
            }
        }
    }

    if(direction == 1 && !stopVertical) {
        int widthIndex;
        do { widthIndex = rand() % (width - 4 - minWidth) + minWidth + 2; }
        while(widthIndex % 2 != 0);

        for(int i = minHeight; i < length; ++i) { MazeStructure[i][widthIndex] = 'x'; }

        if(widthIndex - 2 == minWidth) {
            if(widthIndex + 2 != width - 1) { minWidth = widthIndex; }
            else { stopVertical = true; } 
        }
    }

    // do checks to see if we can call function again then call it again
    RecursiveFill(minHeight, minWidth, stopHorizontal, stopVertical);
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