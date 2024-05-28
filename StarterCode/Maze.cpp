#include "Maze.h"
#include <random>
#include <string>
#include <sstream>
#include <iostream>

Maze::Maze(mcpp::Coordinate basePoint, unsigned int xlen,
                                    unsigned int zlen,
                                    bool mode)
{
    this->basePoint=basePoint;
    this->length=xlen;
    this->width=zlen;
    this->mode=mode;
}


Maze::~Maze()
{
}