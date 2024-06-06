#include "Maze.h"
#include <random>
// #include <string>
// #include <sstream>
// #include <iostream>

Maze::Maze(mcpp::Coordinate basePoint, unsigned int xlen,
           unsigned int zlen,
           bool mode)
{
    this->basePoint = basePoint;
    this->length = xlen;
    this->width = zlen;
    this->mode = mode;

    // sleep function 50ms delay
    // flattenTerrain();
    // buildMaze();
}

void Maze::coordPushBack(mcpp::Coordinate *coordinate)
{
    MazeCoord *newCoord = new MazeCoord();
    newCoord->coord = coordinate;
    newCoord->next = headCoord;
    headCoord = newCoord;
}

void Maze::coordPopBack()
{
}

void Maze::blockPushBack(mcpp::BlockType *block)
{
    MazeBlock *newBlock = new MazeBlock();
    newBlock->block = block;
    newBlock->next = headBlock;
    headBlock = newBlock;
}

void Maze::blockPopBack()
{
}

int Maze::mazeSize() const
{
}

// TODO might need to have getBlockCoord in this part as well to keep track of what blocktype was before changing to air --
//  still unsure if deleting memory will reverse a block at coordinate to its orgianal state
void Maze::flattenTerrain()
{
    mcpp::Coordinate *cornerFromBase = new mcpp::Coordinate((basePoint.x + length + 2), basePoint.y, (basePoint.z + width + 2));
    int axisIndex_z = 0;
    for (size_t i = 0; i < mc.getHeights(basePoint, *cornerFromBase).size(); ++i)
    {
        int axisIndex_x = 0;
        for (size_t j = 0; j < mc.getHeights(basePoint, *cornerFromBase)[i].size(); ++j)
        {

            if (mc.getHeights(basePoint, *cornerFromBase)[i][j] < basePoint.y)
            {
                int yAxis_diff = basePoint.y - mc.getHeights(basePoint, *cornerFromBase)[i][j];
                int level_yAxis = 1;
                mcpp::Coordinate *getBlockCoord = new mcpp::Coordinate((basePoint.x + axisIndex_x) + mc.getHeights(basePoint, *cornerFromBase)[i][j], (basePoint.z + axisIndex_z));

                while (level_yAxis != yAxis_diff)
                {
                    mcpp::Coordinate *coordinate = new mcpp::Coordinate((basePoint.x + axisIndex_x),
                                                                        (mc.getHeights(basePoint, *cornerFromBase)[i][j] + level_yAxis), (basePoint.z + axisIndex_z));
                    this->coordPushBack(coordinate);
                    mcpp::BlockType *block = new mcpp::BlockType(mc.getBlock(*getBlockCoord));
                    this->blockPushBack(block);
                    mc.setBlock(*coordinate, *block);
                    //delete coordinate; TODO not sure if this will tamper with the function being able to recall where and what blocks were placed in minecraft
                    //delete block; TODO not sure if this will tamper with the function being able to recall where and what blocks were placed in minecraft
                    ++level_yAxis;
                }
                delete getBlockCoord;
            }
            else if (mc.getHeights(basePoint, *cornerFromBase)[i][j] > basePoint.y)
            {
                int yAxis_diff = mc.getHeights(basePoint, *cornerFromBase)[i][j] - basePoint.y;
                while (yAxis_diff != 0)
                {
                    mcpp::Coordinate *coordinate = new mcpp::Coordinate((basePoint.x + axisIndex_x),
                                                                        (mc.getHeights(basePoint, *cornerFromBase)[i][j] + yAxis_diff), (basePoint.z + axisIndex_z));
                    this->coordPushBack(coordinate);
                    mcpp::BlockType *block = new mcpp::BlockType(mcpp::Blocks::AIR);
                    this->blockPushBack(block);
                    mc.setBlock(*coordinate, *block);
                    //delete coordinate; TODO not sure if this will tamper with the function being able to recall where and what blocks were placed in minecraft
                    //delete block; TODO not sure if this will tamper with the function being able to recall where and what blocks were placed in minecraft
                    --yAxis_diff;
                }
            }
            ++axisIndex_x;
        }
        ++axisIndex_z;
    }
    delete cornerFromBase;
}

void Maze::buildMaze(char **mazeStructure)
{
    for(int row = 0; row < length; ++row)
    {
        for(int col = 0; col < width; ++col)
        {
            if(mazeStructure[row][col] == 'X') {
                for(int i = 1; i < 4; ++i)
                {
                mcpp::Coordinate *cooridnate = new mcpp::Coordinate((basePoint.x + row + 1), (basePoint.y + i), (basePoint.z + col + 1));
                this->coordPushBack(cooridnate);
                mcpp::BlockType *block = new mcpp::BlockType(mcpp::Blocks::ACACIA_WOOD_PLANK);
                this->blockPushBack(block);
                mc.setBlock(*cooridnate, *block);
                //delete cooridnate; TODO not sure if this will tamper with the function being able to recall where and what blocks were placed in minecraft
                //delete block; TODO not sure if this will tamper with the function being able to recall where and what blocks were placed in minecraft
                }
            }
            else if((mazeStructure[row][col] == '.' && row == 0 || row == length - 1) ||
                (mazeStructure[row][col] == '.' && col == 0 || col == width - 1))
                {
                mcpp::Coordinate *cooridnate = new mcpp::Coordinate((basePoint.x + row + 1), (basePoint.y + 1), (basePoint.z + col + 1));
                this->coordPushBack(cooridnate);
                mcpp::BlockType *block = new mcpp::BlockType(mcpp::Blocks::BLUE_CARPET);
                this->blockPushBack(block);
                mc.setBlock(*cooridnate, *block);
                //delete cooridnate; TODO not sure if this will tamper with the function being able to recall where and what blocks were placed in minecraft
                //delete block; TODO not sure if this will tamper with the function being able to recall where and what blocks were placed in minecraft
                }
        }

    }
}

Maze::~Maze()
{
}