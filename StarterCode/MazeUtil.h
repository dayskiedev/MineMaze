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

        void CreateStructure();
        void CreateStructureTerminal();
        void CreatureStructureRandom(bool mode);
        void CreateMazeEntrance();

        void PrintMazeInfo();

        void RecursiveFill(int minh, int minw, int maxh, int maxw, int d);

        mcpp::Coordinate MazeRandStartCoord();

        int getLength() { return length; }
        int getWidth() { return width; }
        char** GetStructure() { return MazeStructure; }
        mcpp::Coordinate getBasePoint() { return basePoint; }

    private:
         int width = 0;
        int length = 0;
        char** MazeStructure = nullptr; // 2d array of chars
        mcpp::Coordinate basePoint;
        bool testmode = false;
};