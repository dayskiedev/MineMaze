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
    ~Maze();

    /**
     * void Maze::flattenTerrain(); TODO?? might need to implement this function
     * but also could also be implemented in maze constructor?
     */

    std::vector<std::vector<char>> readMaze(const std::string& mazeStr);

    void buildMaze(std::vector<std::vector<char>>& mazeChars);

private:
/*   mcpp::MinecraftConnection maze;
    mcpp::Coordinate basePoint;
    unsigned int length;
    unsigned int width;
    bool mode;
    std::vector<mcpp::Coordinate*> terrainCoordinates;
    std::vector<mcpp::BlockType*> terrainBlocks;
    std::vector<std::vector<mcpp::Coordinate*>> mazeCoordinates;
    std::vector<std::vector<mcpp::BlockType*>> MazeBlocks;
*/
};




#endif //ASSIGN_MAZE_H
