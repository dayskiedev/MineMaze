#ifndef ASSIGN_MAZE_H
#define ASSIGN_MAZE_H

#include <mcpp/mcpp.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <string>

// class to store an mcpp::Coordinate object as a node in a linked list.
class CoordNode {
public:
    CoordNode(mcpp::Coordinate);
    mcpp::Coordinate coord;
    CoordNode *nextCoord;
};

// class to store the id and modifier integers from a
// mcpp::Blocktype object as a node in a linked list.
class BlockNode {
public:
    BlockNode(int id, int modifier);
    int id;
    int modifier;
    BlockNode *nextBlock;
};

class Maze {
public:
    // default constructor that initialises the relevant member variables in maze.
    // allows for basePoint to be set to the coordinates (4848, 71, 4369) if mode
    // is true for -testmode functionality
    Maze(bool mode);

    // method to let relevant member variables for maze to be set after default maze constructor has been called.
    void setFields(mcpp::Coordinate basePoint, int xlen,
         int zlen, char **mazeStructure);

    // method to flatten the terrain at basePoint to the passed length and width of the maze
    // call this function first before buildMaze().
    void flattenTerrain();

    // method to build the maze based on the passed in mazeStructure.
    void buildMaze();

    // destructor for maze that deletes all the memory allocated for both linked lists,
    // called when mazeRunner program exits.
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

    // private member method to add a CoordNode object to the start of a linked list.
    // need to pass in the mcpp::Coordinate member method clone()
    // when calling this function to copy coordinate over to list
    void addCoordToStart(mcpp::Coordinate coord);

    // private member method to add a BlockNode object to the start of a linked list.
    void addBlockToStart(int id, int mod);

    // private member method that iterates through both linked lists of CoordNodes and BlockNodes
    // and restores blocks that were removed by flattenTerrain() or buildMaze().
    // called by ~Maze() when program exits and is not to be called explicitly outside this
    void restore();
};

#endif // ASSIGN_MAZE_H
