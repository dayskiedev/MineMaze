#ifndef ASSIGN_MAZE_H
#define ASSIGN_MAZE_H

#include <mcpp/mcpp.h>
#include <chrono>
#include <thread>

class MazeCoord
{
public:
    // MazeCoord(mcpp::Coordinate* coord);
    mcpp::Coordinate *coord;
    MazeCoord *next;
};

class MazeBlock
{
public:
    // MazeBlock(mcpp::BlockType block);
    mcpp::BlockType *block;
    MazeBlock *next;
};

class Maze
{
public:
    Maze(mcpp::Coordinate basePoint, unsigned int xlen,
         unsigned int zlen,
         bool mode);
    void flattenTerrain();

    void buildMaze(char **mazeStructure);

    ~Maze();

private:
    mcpp::MinecraftConnection mc;
    mcpp::Coordinate basePoint;
    MazeCoord *headCoord;
    MazeBlock *headBlock;
    int length;
    int width;
    bool mode;

    void coordPushBack(mcpp::Coordinate *coord);
    void coordPopBack();
    void blockPushBack(mcpp::BlockType *block);
    void blockPopBack();
    int mazeSize() const;
};

#endif // ASSIGN_MAZE_H
