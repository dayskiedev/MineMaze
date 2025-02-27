#include <iostream>
#include <mcpp/mcpp.h>
#include <cstdlib>
#include <ctime>

// maze will be stored in a 2d array
// x.x 
// x.x 
// x.x

// using chars

class MazeUtil {
    public:
        MazeUtil(bool mode, bool enhance);
        ~MazeUtil(); // place to dealocate memory

        void CreateStructure();
        void CreateStructureTerminal();

        void CreatureStructureRandom();
        void RecursiveFill(int minh, int minw, int maxh, int maxw, int d);
        void CreateMazeEntrance();

        void PrintMazeInfo();

        // enhancment
        void ValidMaze();
        void FloodFill(int** compArr, int sl, int sw, char c);
        void CheckFloodFill(int** arr, int sl, int sw, char c);

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
        bool enhancemode = false;
};