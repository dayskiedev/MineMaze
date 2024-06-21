#ifndef ASSIGN_MAZE_H
#define ASSIGN_MAZE_H

#include <mcpp/mcpp.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <string>

class CoordNode
{
public:
    CoordNode(mcpp::Coordinate);
    mcpp::Coordinate coord;
    CoordNode *nextCoord;
};

class BlockNode
{
public:
    BlockNode(int id, int modifier);
    int id;
    int modifier;
    BlockNode *nextBlock;
};

class Maze
{
public:
    Maze(bool mode);

    void setFields(mcpp::Coordinate basePoint, int xlen,
         int zlen, char **mazeStructure);

    void flattenTerrain();

    void buildMaze();

    void restore();

    ~Maze();

private:
    mcpp::MinecraftConnection mc;
    mcpp::Coordinate basePoint;
    CoordNode *headCoord;
    BlockNode *headBlock;
    bool mode;
    int length;
    int width;
    char **mazeStructure;

    // need to pass in the [[nodiscard]] Coordinate clone() const;
    // member function when calling this function to copy coordinate over to list
    void addCoordToStart(mcpp::Coordinate coord);

    void addBlockToStart(int id, int mod);
};

#endif // ASSIGN_MAZE_H
