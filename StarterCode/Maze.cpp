#include "Maze.h"
#include <mcpp/mcpp.h>
#include <chrono>
#include <thread>

/**
Maze::Maze()
{
    this->length = 0;
    this->width = 0;
    this->mode = 0;
    this->headBlock = nullptr;
    this->headCoord = nullptr;
}
*/

Maze::Maze(mcpp::Coordinate basePoint, int xlen,
           int zlen, char **mazeStructure, bool mode)
{
    this->basePoint = basePoint;
    this->length = xlen;
    this->width = zlen;
    this->mode = mode;
    this->mazeStructure = mazeStructure;
    this->headBlock = nullptr;
    this->headCoord = nullptr;

    flattenTerrain();
    buildMaze();
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
    CoordNode * newCoord = new CoordNode(coord);
    newCoord->nextCoord = this->headCoord;
    this->headCoord = newCoord;

}

void Maze::addBlockToStart(int id, int mod)
{
    BlockNode * newBlock = new BlockNode(id, mod);
    newBlock->nextBlock = this->headBlock;
    this->headBlock = newBlock;
}

void Maze::flattenTerrain()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    mcpp::Coordinate cornerFromBase(basePoint.x + length + 2, basePoint.y, basePoint.z + width + 2);

    std::vector<mcpp::Coordinate*> tempCoords;
    std::vector<mcpp::BlockType*> tempBlocks;
    
    int axisIndex_z = 0;
    for (size_t i = 0; i < mc.getHeights(basePoint, cornerFromBase).size(); ++i)
    {
        int axisIndex_x = 0;
        for (size_t j = 0; j < mc.getHeights(basePoint, cornerFromBase)[i].size(); ++j)
        {
            if (mc.getHeights(basePoint, cornerFromBase)[i][j] < basePoint.y)
            {
                int yAxis_diff = basePoint.y - mc.getHeights(basePoint, cornerFromBase)[i][j];
                int level_yAxis = 1;
                mcpp::Coordinate *getBlockCoord = new mcpp::Coordinate((basePoint.x + axisIndex_x) + mc.getHeights(basePoint, cornerFromBase)[i][j], (basePoint.z + axisIndex_z));
                while (level_yAxis != yAxis_diff)
                {
                    mcpp::Coordinate *coordinate = new mcpp::Coordinate((basePoint.x + axisIndex_x),
                                                                        (mc.getHeights(basePoint, cornerFromBase)[i][j] + level_yAxis), (basePoint.z + axisIndex_z));
                    tempCoords.push_back(coordinate); //std::move?? or do i nedd to use clone() from mcpp
                    mcpp::BlockType *block = new mcpp::BlockType(mc.getBlock(*getBlockCoord));
                    tempBlocks.push_back(block);
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    mc.setBlock(*coordinate, *block);
                    ++level_yAxis;
                }
                delete getBlockCoord;
            }
            else if (mc.getHeights(basePoint, cornerFromBase)[i][j] > basePoint.y)
            {
                int yAxis_diff = mc.getHeights(basePoint, cornerFromBase)[i][j] - basePoint.y;
                while (yAxis_diff != 0)
                {
                    mcpp::Coordinate *coordinate = new mcpp::Coordinate((basePoint.x + axisIndex_x),
                                                                        (mc.getHeights(basePoint, cornerFromBase)[i][j] + yAxis_diff), (basePoint.z + axisIndex_z));
                    tempCoords.push_back(coordinate);
                    mcpp::BlockType *block = new mcpp::BlockType(mcpp::Blocks::AIR);
                    tempBlocks.push_back(block);
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    mc.setBlock(*coordinate, *block);
                    --yAxis_diff;
                }
            }
            ++axisIndex_x;
        }
        ++axisIndex_z;
    }
    for(auto& coord : tempCoords){
        this->addCoordToStart(coord->clone());
    }
    for(auto& block : tempBlocks){
        this->addBlockToStart(block->id, block->mod);
    }
    for(auto& coord : tempCoords){
        delete coord;
    }
    for(auto& block : tempBlocks){
        delete block;
    }
}

void Maze::buildMaze()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    std::vector<mcpp::Coordinate*> tempCoords;
    std::vector<mcpp::BlockType*> tempBlocks;

    for (int row = 0; row < length; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            if (this->mazeStructure[row][col] == 'x')
            {
                for (int i = 1; i < 4; ++i)
                {
                    mcpp::Coordinate *cooridnate = new mcpp::Coordinate((basePoint.x + row + 1), (basePoint.y + i), (basePoint.z + col + 1));
                    tempCoords.push_back(cooridnate);
                    mcpp::BlockType *block = new mcpp::BlockType(mc.getBlock(*cooridnate));
                    tempBlocks.push_back(block);

                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    mc.setBlock(*cooridnate, mcpp::BlockType(mcpp::Blocks::ACACIA_WOOD_PLANK));
                }
            }
            else if ((this->mazeStructure[row][col] == '.') && (row == 0 || row == length - 1))
            {
                mcpp::Coordinate *cooridnate = new mcpp::Coordinate(basePoint.x, (basePoint.y + 1), (basePoint.z + col + 1));
                tempCoords.push_back(cooridnate);
                mcpp::BlockType *block = new mcpp::BlockType(mc.getBlock(*cooridnate));
                tempBlocks.push_back(block);

                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                mc.setBlock(*cooridnate, mcpp::BlockType(mcpp::Blocks::BLUE_CARPET));
            }
            else if ((this->mazeStructure[row][col] == '.') && (col == 0 || col == width - 1))
            {
                mcpp::Coordinate *cooridnate = new mcpp::Coordinate((basePoint.x + row + 1), (basePoint.y + 1), basePoint.z);
                tempCoords.push_back(cooridnate);
                mcpp::BlockType *block = new mcpp::BlockType(mc.getBlock(*cooridnate));
                tempBlocks.push_back(block);

                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                mc.setBlock(*cooridnate, mcpp::BlockType(mcpp::Blocks::BLUE_CARPET));
            }
        }
    }
    for(auto& coord : tempCoords){
        this->addCoordToStart(coord->clone());
    }
    for(auto& block : tempBlocks){
        this->addBlockToStart(block->id, block->mod);
    }
    for(auto& coord : tempCoords){
        delete coord;
    }
    for(auto& block : tempBlocks){
        delete block;
    }
}

void Maze::restore()
{
    CoordNode * currentCoord = this->headCoord;
    BlockNode * currentBlock = this->headBlock;
    while(currentCoord != nullptr)
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

    while (headCoord != nullptr) {
        CoordNode* temp = headCoord;
        headCoord = headCoord->nextCoord;
        delete temp;
        this->headCoord = nullptr;
    }

    while (headBlock!= nullptr) {
        BlockNode* temp = headBlock;
        headBlock = headBlock->nextBlock;
        delete temp;
        this->headBlock = nullptr;
    }
}