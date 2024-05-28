#include "MazeUtil.h"

char** MazeUtil::GetStructure() { return MazeStructure; } 

void MazeUtil::CreateStructureTerminal() {
    width = 7;
    height = 7;

    MazeStructure = new char*[height];
    for(int i  = 0; i < width; i++) {
        MazeStructure[i] = new char[width];
    }
}

void MazeUtil::TestFill(char c) {
    for(int i  = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            MazeStructure[i][j] = c;
        }
    }
}

void MazeUtil::TestPrintMaze() {
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            std::cout << MazeStructure[i][j];
        }
        std::cout << std::endl;
    }
}