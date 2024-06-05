#include <iostream>
#include <mcpp/mcpp.h>

// maze will be stored in a 2d array
// x.x 
// x.x 
// x.x

// using chars

class MazeUtil {
    public:
        ~MazeUtil(); // place to dealocate memory
        char** GetStructure();

        void CreateStructure();
        void CreateStructureTerminal();
        void CreatureStructureRandom(bool mode);

        void PrintMazeInfo();

        void RecursiveFill(int mh, int mw, bool sh, bool sv);

        mcpp::Coordinate MazeRandStartCoord();

    private:
        char** MazeStructure; // 2d array of chars
        // ms[height][width]
        mcpp::Coordinate basePoint;
        int width = 0;
        int length = 0;
};