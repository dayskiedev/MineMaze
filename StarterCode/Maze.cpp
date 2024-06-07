#include "Maze.h"
#include <mcpp/mcpp.h>
#include <chrono>
#include <thread>

Maze::Maze() {}

Maze::Maze(mcpp::Coordinate basePoint, int xlen,
           int zlen, char **mazeStructure,
           bool mode)
{
    this->basePoint = basePoint;
    this->length = xlen;
    this->width = zlen;
    this->mode = mode;
    this->mazeStructure = mazeStructure;

    // flattenTerrain();
    // std::this_thread::sleep_for(std::chrono::milliseconds(50));
    // buildMaze(mazeStructure);
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
    return 1;
}

// TODO might need to have getBlockCoord in this part as well to keep track of what blocktype was before changing to air --
//  still unsure if deleting memory will reverse a block at coordinate to its orgianal state
void Maze::flattenTerrain()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
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
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    mc.setBlock(*coordinate, *block);
                    // delete coordinate; TODO not sure if this will tamper with the function being able to recall where and what blocks were placed in minecraft
                    // delete block; TODO not sure if this will tamper with the function being able to recall where and what blocks were placed in minecraft
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
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    mc.setBlock(*coordinate, *block);
                    // delete coordinate; TODO not sure if this will tamper with the function being able to recall where and what blocks were placed in minecraft
                    // delete block; TODO not sure if this will tamper with the function being able to recall where and what blocks were placed in minecraft
                    --yAxis_diff;
                }
            }
            ++axisIndex_x;
        }
        ++axisIndex_z;
    }
    delete cornerFromBase;
}

void Maze::buildMaze()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    for (int row = 0; row < length; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            if (this->mazeStructure[row][col] == 'X')
            {
                for (int i = 1; i < 4; ++i)
                {
                    mcpp::Coordinate *cooridnate = new mcpp::Coordinate((basePoint.x + row + 1), (basePoint.y + i), (basePoint.z + col + 1));
                    this->coordPushBack(cooridnate);
                    mcpp::BlockType *block = new mcpp::BlockType(mcpp::Blocks::ACACIA_WOOD_PLANK);
                    this->blockPushBack(block);
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    mc.setBlock(*cooridnate, *block);
                    // delete cooridnate; TODO not sure if this will tamper with the function being able to recall where and what blocks were placed in minecraft
                    // delete block; TODO not sure if this will tamper with the function being able to recall where and what blocks were placed in minecraft
                }
            }
            else if ((this->mazeStructure[row][col] == '.') && (row == 0 || row == length - 1))
            {
                mcpp::Coordinate *cooridnate = new mcpp::Coordinate(basePoint.x, (basePoint.y + 1), (basePoint.z + col + 1));
                this->coordPushBack(cooridnate);
                mcpp::BlockType *block = new mcpp::BlockType(mcpp::Blocks::BLUE_CARPET);
                this->blockPushBack(block);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                mc.setBlock(*cooridnate, *block);
                // delete cooridnate; TODO not sure if this will tamper with the function being able to recall where and what blocks were placed in minecraft
                // delete block; TODO not sure if this will tamper with the function being able to recall where and what blocks were placed in minecraft
            }
            else if ((this->mazeStructure[row][col] == '.') && (col == 0 || col == width - 1))
            {
                mcpp::Coordinate *cooridnate = new mcpp::Coordinate((basePoint.x + row + 1), (basePoint.y + 1), basePoint.z);
                this->coordPushBack(cooridnate);
                mcpp::BlockType *block = new mcpp::BlockType(mcpp::Blocks::BLUE_CARPET);
                this->blockPushBack(block);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                mc.setBlock(*cooridnate, *block);
                // delete cooridnate; TODO not sure if this will tamper with the function being able to recall where and what blocks were placed in minecraft
                // delete block; TODO not sure if this will tamper with the function being able to recall where and what blocks were placed in minecraft
            }
        }
    }
}

Maze::~Maze()
{
}