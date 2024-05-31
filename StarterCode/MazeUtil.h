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
        void CreateStructureTerminal();
        void CreatureStructureRandom();

        void PrintMazeInfo();

        //testing
        void TestFill(char c);
        void TestPrintMaze();

    private:
        char** MazeStructure; // 2d array of chars
        // ms[height][width]
        mcpp::Coordinate basePoint;
        int width = 0;
        int length = 0;
};