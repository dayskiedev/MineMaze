#include "Maze.h"
#include <random>
#include <string>
#include <sstream>
#include <iostream>

Maze::Maze(mcpp::Coordinate basePoint, unsigned int xlen,
                                    unsigned int zlen,
                                    bool mode)
{
/*    this->basePoint=basePoint;
    this->length=xlen; //TODO remove this var and just pass it into the coordinate vectors
    this->width=zlen; //TODO remove this var and just pass it into the coordinate vectors
    this->mode=mode;
*/
}

std::vector<std::vector<char>> Maze::readMaze(const std::string& mazeStr)
{
    std::vector<std::vector<char>> mazeChars;
    std::istringstream iSS(mazeStr);
    std::string line;
    while(std::getline(iSS, line)){
        mazeChars.emplace_back();
        for(char c : line){
            if(c != '/n'){
                mazeChars.back().push_back(c);
            }
        }
    }
    return mazeChars;
}

void Maze::buildMaze(std::vector<std::vector<char>>& mazeChars)
{
    std::vector<std::vector<mcpp::MinecraftConnection>> mazeBlocks;
}

Maze::~Maze()
{
}
*/