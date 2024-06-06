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
    mcpp::Coordinate *cornerFromBase = new mcpp::Coordinate((basePoint.x + length + 1), basePoint.y, (basePoint.z + width + 1));
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
                    mc.setBlock(*coordinate, mc.getBlock(*getBlockCoord));
                    mcpp::BlockType *block = new mcpp::BlockType(mc.getBlock(*coordinate));
                    this->blockPushBack(block);
                    ++level_yAxis;
                }
            }
            else if (mc.getHeights(basePoint, *cornerFromBase)[i][j] > basePoint.y)
            {
                int yAxis_diff = mc.getHeights(basePoint, *cornerFromBase)[i][j] - basePoint.y;
                while (yAxis_diff != 0)
                {
                    mcpp::Coordinate *coordinate = new mcpp::Coordinate((basePoint.x + axisIndex_x),
                                                                        (mc.getHeights(basePoint, *cornerFromBase)[i][j] + yAxis_diff), (basePoint.z + axisIndex_z));
                    this->coordPushBack(coordinate);
                    mc.setBlock(*coordinate, mcpp::Blocks::AIR);
                    mcpp::BlockType *block = new mcpp::BlockType(mcpp::Blocks::AIR);
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
}

Maze::~Maze()
{
}