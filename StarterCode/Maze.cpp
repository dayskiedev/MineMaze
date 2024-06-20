#include "Maze.h"
#include <mcpp/mcpp.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <string>

Maze::Maze()
{
    this->length = 0;
    this->width = 0;
    this->mode = false;
    this->headBlock = nullptr;
    this->headCoord = nullptr;
}

void Maze::setFields(mcpp::Coordinate basePoint, int xlen,
           int zlen, char **mazeStructure, bool mode)
{
    this->length = xlen;
    this->width = zlen;
    this->mode = mode;
    this->mazeStructure = mazeStructure;
    this->headBlock = nullptr;
    this->headCoord = nullptr;

    if(basePoint.y > (mc.getHeight(basePoint.x, basePoint.z)) + 1) {

        this->basePoint = mcpp::Coordinate(basePoint.x, ((mc.getHeight(basePoint.x, basePoint.z)) + 1), basePoint.z);
    }
    else {
        this->basePoint = basePoint;
    }
}

CoordNode::CoordNode(mcpp::Coordinate coord)
{
    this->coord = coord;
    this->nextCoord = nullptr;
}

BlockNode::BlockNode(int id, int mod)
{
    this->id = id;
    this->modifier = mod;
    this->nextBlock = nullptr;
}

void Maze::addCoordToStart(mcpp::Coordinate coord)
{
    CoordNode *newCoord = new CoordNode(coord);
    newCoord->nextCoord = this->headCoord;
    this->headCoord = newCoord;
}

void Maze::addBlockToStart(int id, int mod)
{
    BlockNode *newBlock = new BlockNode(id, mod);
    newBlock->nextBlock = this->headBlock;
    this->headBlock = newBlock;
}

void Maze::flattenTerrain()
{
    mcpp::Coordinate cornerFromBase(basePoint.x + length + 2, basePoint.y, basePoint.z + width + 2);

    /**
    std::cout << "BASEPOINT" << std::endl;
    print(basePoint);
    std::cout << "\n";
    std::cout << "CORNERPOINT" << std::endl;
    print(cornerFromBase);
    std::cout << "\n";
    for (size_t i = 0; i < mc.getHeights(basePoint, cornerFromBase).size(); ++i)
    {
        for (size_t j = 0; j < mc.getHeights(basePoint, cornerFromBase)[i].size(); ++j)
        {
            std::cout << mc.getHeights(basePoint, cornerFromBase)[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    std::cout << "\n";
    */

    int axisIndex_x = 0;
    for (size_t i = 0; i < mc.getHeights(basePoint, cornerFromBase).size(); ++i)
    {
        int axisIndex_z = 0;
        for (size_t j = 0; j < mc.getHeights(basePoint, cornerFromBase)[i].size(); ++j)
        {
            /**
            std::cout << "Height from getHeights() " << mc.getHeights(basePoint, cornerFromBase)[i][j] << std::endl;
            std::cout << "X AXIS INDEX " << axisIndex_x << std::endl;
            std::cout << "Z AXIS INDEX " << axisIndex_z << std::endl;
            */

            if (mc.getHeights(basePoint, cornerFromBase)[i][j] < (basePoint.y - 1))
            {
                int yAxis_diff = basePoint.y - mc.getHeights(basePoint, cornerFromBase)[i][j];
                int level_yAxis = 0;
                int height_atIndex = mc.getHeights(basePoint, cornerFromBase)[i][j];
                mcpp::Coordinate getBlockCoord((basePoint.x + axisIndex_x), height_atIndex, (basePoint.z + axisIndex_z));

                while (level_yAxis != yAxis_diff)
                {
                    mcpp::Coordinate coordinate((basePoint.x + axisIndex_x), (height_atIndex + level_yAxis), (basePoint.z + axisIndex_z));
                    this->addCoordToStart(coordinate.clone());
                    mcpp::BlockType block(mc.getBlock(getBlockCoord));
                    this->addBlockToStart(block.id, block.mod);
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    mc.setBlock(coordinate, block);

                    /**
                    // TEST OUTPUT //
                    std::cout << "Coordinate ";
                    print(coordinate);
                    std::cout << "Block ";
                    print(block);
                    std::cout << "yAxis_diff " << yAxis_diff << std::endl;
                    std::cout << "level_yAxis " << level_yAxis << std::endl;
                    std::cout << "\n";
                    std::cout << "\n";
                    // TEST OUTPUT //
                    */

                    ++level_yAxis;
                }
            }
            else if (mc.getHeights(basePoint, cornerFromBase)[i][j] > (basePoint.y -1))
            {
                int yAxis_diff = mc.getHeights(basePoint, cornerFromBase)[i][j] - (basePoint.y - 1);
                int level_yAxis = 0;
                while (level_yAxis != yAxis_diff)
                {
                    mcpp::Coordinate coordinate((basePoint.x + axisIndex_x), (mc.getHeights(basePoint, cornerFromBase)[i][j] - level_yAxis), (basePoint.z + axisIndex_z));
                    this->addCoordToStart(coordinate.clone());
                    mcpp::BlockType block(mcpp::Blocks::AIR);
                    this->addBlockToStart(block.id, block.mod);
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    mc.setBlock(coordinate, block);
                    ++level_yAxis;

                    /**
                    // TEST OUTPUT //
                    std::cout << "Coordinate ";
                    print(coordinate);
                    std::cout << "Block ";
                    print(block);
                    std::cout << "yAxis_diff " << yAxis_diff << std::endl;
                    std::cout << "level_yAxis " << level_yAxis << std::endl;
                    std::cout << "\n";
                    std::cout << "\n";
                    // TEST OUTPUT //
                    */
                }
            }
            else
            {
                mcpp::Coordinate coordinate((basePoint.x + axisIndex_x), basePoint.y, (basePoint.z + axisIndex_z));
                if(mc.getBlock(coordinate) == mcpp::BlockType(mcpp::Blocks::AIR)) {}
                else
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    mc.setBlock(coordinate, mcpp::BlockType(mcpp::Blocks::AIR));
                }
            }
            ++axisIndex_z;
        }
        ++axisIndex_x;
    }
}

void Maze::buildMaze()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    for (int row = 0; row < length; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            //PLACES ACACIA_WOOD_PLANKS
            if (this->mazeStructure[row][col] == 'x')
            {
                for (int i = 0; i < 3; ++i)
                {
                    mcpp::Coordinate coordinate((basePoint.x + row + 1), (basePoint.y + i), (basePoint.z + col + 1));
                    this->addCoordToStart(coordinate.clone());
                    mcpp::BlockType block(mc.getBlock(coordinate));
                    this->addBlockToStart(block.id, block.mod);

                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    mc.setBlock(coordinate, mcpp::BlockType(mcpp::Blocks::ACACIA_WOOD_PLANK));
                }
            }
            //PLACES BLUE CARPET AT ENTRANCE
            else if ((this->mazeStructure[row][col] == '.') && (row == 0 || row == length - 1))
            {
                mcpp::Coordinate coordinate(basePoint.x, (basePoint.y), (basePoint.z + col + 1));
                this->addCoordToStart(coordinate.clone());
                mcpp::BlockType block(mc.getBlock(coordinate));
                this->addBlockToStart(block.id, block.mod);

                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                mc.setBlock(coordinate, mcpp::BlockType(mcpp::Blocks::BLUE_CARPET));
            }
            //PLACES BLUE CARPET AT ENTRANCE
            else if ((this->mazeStructure[row][col] == '.') && (col == 0 || col == width - 1))
            {
                mcpp::Coordinate coordinate((basePoint.x + row + 1), (basePoint.y), basePoint.z);
                this->addCoordToStart(coordinate.clone());
                mcpp::BlockType block(mc.getBlock(coordinate));
                this->addBlockToStart(block.id, block.mod);

                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                mc.setBlock(coordinate, mcpp::BlockType(mcpp::Blocks::BLUE_CARPET));
            }
        }
    }
}

void Maze::restore()
{
    CoordNode *currentCoord = this->headCoord;
    BlockNode *currentBlock = this->headBlock;
    while (currentCoord != nullptr)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        mc.setBlock(currentCoord->coord, mcpp::BlockType(currentBlock->id, currentBlock->modifier));
        currentCoord = currentCoord->nextCoord;
        currentBlock = currentBlock->nextBlock;
    }
}

Maze::~Maze()
{
    restore();

    while (headCoord != nullptr)
    {
        CoordNode *temp = headCoord;
        headCoord = headCoord->nextCoord;
        delete temp;
        this->headCoord = nullptr;
    }

    while (headBlock != nullptr)
    {
        BlockNode *temp = headBlock;
        headBlock = headBlock->nextBlock;
        delete temp;
        this->headBlock = nullptr;
    }
}