#ifndef ASSIGN_MAZE_H
#define ASSIGN_MAZE_H

#include <mcpp/mcpp.h>
#include <string>
#include <sstream>
#include <iostream>

class Maze
{

public:
    Maze(mcpp::Coordinate basePoint, unsigned int xlen,
                                        unsigned int zlen,
                                        bool mode);

    /**
     * void Maze::flattenTerrain(); TODO?? might need to implement this function
     * but also could also be implemented in maze constructor?
     */

    // header file doesnt need Maze:: before functions as this is where the function is created not where they're referenced/called -B

    std::vector<std::vector<char>> readMaze(const std::string& mazeStr);

    void buildMaze(std::vector<std::vector<char>>& mazeChars);
    ~Maze();

private:
    mcpp::Coordinate basePoint;
    unsigned int length;
    unsigned int width;
    bool mode;
};


#endif //ASSIGN_MAZE_H
