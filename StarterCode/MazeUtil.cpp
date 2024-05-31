#include "MazeUtil.h"
#include <mcpp/mcpp.h>

char** MazeUtil::GetStructure() { return MazeStructure; } 

void MazeUtil::CreateStructureTerminal() {
    // get basepoint for maze
    mcpp::MinecraftConnection mc;
    std::cout << "In Minecraft, navigate to where you need the maze to be built and type - done" << std::endl;
    std::string input;
    std::cin >> input; 
    while (!input.compare("done"))
    {
        std::cout << "Invalid input! please enter 'done' when you have found a desirable location!" << std::endl;
        std::cin >> input;
    }

    basePoint = mcpp::Coordinate(mc.getPlayerPosition());
    
    std::cout << "Enter the length and width of the maze:" << std::endl;
    std::cin >> length; //TODO ADD SAFTEY CHECKS 
    std::cin >> width;

    MazeStructure = new char*[length];
    for(int i  = 0; i < width; i++) {
        MazeStructure[i] = new char[width];
    }

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

void MazeUtil::PrintMazeInfo() {
    std::cout << "**Printing Maze**" << std::endl;
    std::cout << "BasePoint: (" << basePoint << ")" << std::endl;
    std::cout << "Structure:" << std::endl;
    for(int i = 0; i < length; ++i) {
        for(int j = 0; j < width; ++j) {
            std::cout << MazeStructure[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << "**End Printing Maze**" << std::endl;
}

void MazeUtil::TestPrintMaze() {
    for(int i = 0; i < length; ++i) {
        for(int j = 0; j < width; ++j) {
            std::cout << MazeStructure[i][j];
        }
        std::cout << std::endl;
    }
}

MazeUtil::~MazeUtil() {
    if(length <= 0 || width <= 0) { return; }

}