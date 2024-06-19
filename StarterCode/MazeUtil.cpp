#include "MazeUtil.h"
#include <mcpp/mcpp.h>
#include <stdlib.h>
#include <random>

// describe class/what it does

// TODO: 
// make sure test mode walls generate at centre
// fix validate mazw

MazeUtil::MazeUtil(bool mode, bool enhance) {
     testmode = mode;
     enhancemode = enhance;
}


/// @brief 
/// Code for creating the 2d array that will hold the maze Structure
/// @return
void MazeUtil::CreateStructure() {
    // get basepoint for maze
    mcpp::MinecraftConnection mc;
    std::cout << "In Minecraft, navigate to where you need the maze to be built and type - done" << std::endl;
    std::string input;
    std::cin >> input; 
    while (input.compare("done"))
    {
        std::cout << "Invalid input! please enter 'done' when you have found a desirable location!" << std::endl;
        std::cin >> input;
    }

    basePoint = mc.getPlayerPosition();

    // make sure length and width are valid inputs (odd numbers)
    while(true) {
        std::cout << "Enter the length and width of the maze:" << std::endl; 
        std::cin >> length;// no input validation
        if(std::cin.good()) { input = true; }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Length must be an integer!" << std::endl;
            continue;
        }
        if(length % 2 == 0) {
            std::cout << "Length must be an odd number!" << std::endl;
            continue;
        }

        std::cin >> width;
        if(std::cin.good()) { input = true; }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Width must be an integer!" << std::endl;
            continue;
        }

        if(width % 2 == 0 ) {
            std::cout << "Width must be an odd number!" << std::endl;
            continue;
        }
        break;
    }

    MazeStructure = new char*[length];
    for(int i = 0; i < length; i++) {
        MazeStructure[i] = new char[width];
    }
}

///
///  Terminal Section - Function for creating the maze from the terminal
///                     as well as validating / fixing this maze if it contains loops
///

void MazeUtil::CreateStructureTerminal() {
    CreateStructure();

    // kind of a scuffed way to do this but we need to teleport the player to a certain coordinate if in testmode for the terminal

    std::cout << "Enter the maze structure (" << length << "x" << width << "): " << std::endl;
    // read in input from terminal
    char c;
    for(int i = 0; i < length; ++i) {
        for(int j = 0; j < width; ++j) {
            std::cin >> c;
            MazeStructure[i][j] = c;
        }
    }

    if(enhancemode) {
        std::cout << "running in enhanced mode" << std::endl;
        ValidMaze();
    }

    std::cout << "Maze read successfully!" << std::endl;
    PrintMazeInfo();
}


void MazeUtil::ValidMaze() {
    int** compArr = new int*[length];
    for(int i = 0; i < length; ++i) {
        compArr[i] = new int[width];
    }
    for(int i = 0; i < length; ++i) { for(int j = 0; j < width; ++j) { compArr[i][j] = 0; } }
    // fill with 0's

    // finding the entrance point for the maze to start the floodfills
    int startL = 0;
    int startW = 0;
    for(int i = 0; i < length; ++i) {
        if(MazeStructure[i][0] == '.') {
            startL = i;
            startW = 0;
            break;
        }
        else if(MazeStructure[i][width-1] == '.') {
            startL = i;
            startW = width - 1;
            break;
        }
    };
    for(int i = 0; i < width; ++i) {
        if(MazeStructure[0][i] == '.') {
            startL = 0;
            startW = i;
            break;
        }
        else if(MazeStructure[length-1][i] == '.') {
            startL = length-1;
            startW = i;
            break;
        }
    }

    FloodFill(compArr, startL, startW);

    for(int i = 0; i < length; ++i) {
        for(int j = 0; j < width; ++j) {
            std::cout << compArr[i][j] << " ";
        }
        std::cout <<std::endl;
    }

    for(int i = 0; i < length; ++i) {
            for(int j = 0; j < width; ++j) {
                if(MazeStructure[i][j] == '.' && compArr[i][j] == 0) {
                    std::cout << "isolation/loop detected at (" << i << "." << j << ")" << std::endl;      
                }
            }
        }
    
    //std::cout << "no loops detected." << std::endl;

    for(int x = 0; x < length; ++x) {
        delete[] compArr[x];
            }
            delete[] compArr;
    return;
    // pick starting point
    // swap to 1 if applicable
    // check if direction can move (ie next spot is 0)
    // move to that direction
    // repeat

    // return if not equal to a . or if it goes out of bounds
}

void MazeUtil::FloodFill(int** compArr, int sl, int sw) {
    if(sl < 0 || sw < 0 || sl >= length || sw >= width 
    || MazeStructure[sl][sw] != '.' || compArr[sl][sw] == 1) { return; }
    // if current spot is not a dot we go back
    // but we also need to make sure the spot isnt filled already
    // this video helped with flood fill https://youtu.be/aehEcTEPtCs?si=4c3jc9xTELWiEXmG

    compArr[sl][sw] = 1;
    // move onto 4 other directions
    FloodFill(compArr, sl - 1, sw); // up
    FloodFill(compArr, sl + 1, sw); // down
    FloodFill(compArr, sl, sw - 1); // left
    FloodFill(compArr, sl, sw + 1); // right
}

///
/// Random Generation  Section - Contains functions for creating the maze with a random
///                              structure as well as a valid but random entry point
///

void MazeUtil::CreatureStructureRandom() {
    CreateStructure();
    // creates the x outline for maze and fills with .'s
    for(int i = 0; i < width; ++i) { 
        MazeStructure[0][i] = 'x';
        MazeStructure[length-1][i] = 'x';
    }
    for(int i = 1; i < length - 1; ++i) {
        MazeStructure[i][width-1] = 'x';
        MazeStructure[i][0] = 'x';
        for(int j = 1; j < width - 1; ++j) {
            MazeStructure[i][j] = '.';
        }
    }
    if(testmode) {
        std::cout << "creating in testmode.." << std::endl;
    }

    RecursiveFill(0,0, length-1, width - 1, 1);
    // place entrance
    CreateMazeEntrance();
    PrintMazeInfo();
}

void MazeUtil::RecursiveFill(int minh, int minw, int maxh, int maxw, int d) {
    // works when len and wid are same but not when different?
    // mode true means running in testmode
    int direction;
    std::random_device rnd;

    std::uniform_int_distribution<int> dir(0,1);
    std::uniform_int_distribution<int> rndWidth(minw + 1, maxw - 1);
    std::uniform_int_distribution<int> rndHeight(minh + 1, maxh -1);

    if(maxh - 2 <= minh) { return; }
    if(maxw - 2 <= minw) { return; }

    if(!testmode) { 
        direction = dir(rnd); 
    }
    // if not in test mode direction will be random, if in test mode direction depends on previous direction
    if(testmode) { // really cursed testmode direction check
        direction = d;
        direction = 1 - direction;
    }

    int wall = 0;


    std::cout << "current direction: " << direction << std::endl;

    if(direction == 0) {
        int horizontalSplit = 0;
        do{ horizontalSplit = rndHeight(rnd); }
        while(horizontalSplit % 2); // repeat until even number
        for(int i = minw; i < maxw; ++i) { MazeStructure[horizontalSplit][i] = 'x'; }

        //generate hole
        if(!testmode) { // pick random spot
            do{ wall = rndWidth(rnd); }
            while ( wall % 2 == 0);
            MazeStructure[horizontalSplit][wall] = '.';

        } else{
            // needs to be wall closest to centre 
            // if there are less than 2 options go random
            // for example [1 - 5]
            // could be 1 3 or 5
            // 3 is centre so we want that
            
            // floor of (min + maxw / 2) gives a value close to the centre of the wall
            wall = std::floor( (minw + maxw ) / 2);
            if(wall % 2 == 0) { wall += 1;} // could change to be random but atm its right biased
            std::cout << "middle position of horiontal wall is: " << wall << std::endl;
            MazeStructure[horizontalSplit][wall] = '.';
        }

        // now we treat the horizontal split as the max for the top square and the min for the bottom square
        // and if in test mode set the direction to the opposite (dont need to check with another if statement it already checks at the start)

        RecursiveFill(minh, minw, horizontalSplit, maxw, direction);
        RecursiveFill(horizontalSplit, minw, maxh, maxw, direction);
    }
    if(direction == 1) {
        int verticalSplit = 0;
        do { verticalSplit = rndWidth(rnd); }
        while(verticalSplit % 2 != 0);
        // genertaing vertical line
        for(int i = minh; i < maxh; ++i) { MazeStructure[i][verticalSplit] = 'x'; }

        // generating hole
        if(!testmode) {
            do{ wall = rndHeight(rnd); }
            while (wall % 2 == 0);
            MazeStructure[wall][verticalSplit] = '.'; 
        }
        else {
            wall = std::floor( (minh + maxh ) / 2);
            if(wall % 2 == 0) { wall += 1; }
            std::cout << "middle position of vertical wall is: " << wall << std::endl;
            MazeStructure[wall][verticalSplit] = '.'; 
        }

        RecursiveFill(minh, minw, maxh, verticalSplit, direction);
        RecursiveFill(minh, verticalSplit, maxh, maxw, direction);
    }
}

void MazeUtil::CreateMazeEntrance() {
    std::random_device rnd;
    std::uniform_int_distribution<int> dir(0,3);
    std::uniform_int_distribution<int> rndWidth(0, width - 1);
    std::uniform_int_distribution<int> rndHeight(0, length - 1);
    //int dir = rand() % 4; // 0 = up 1 = left 2 = right 3 = down

    int direction = dir(rnd);
    int pos;

    std::cout << "entrance direction: " << direction << std::endl;
    if(direction == 0) {
        do{pos = rndWidth(rnd); }
        while (MazeStructure[1][pos] == 'x');
        MazeStructure[0][pos] = '.';
    }
    if(direction == 1) {
        do{pos = rndHeight(rnd); }
        while (MazeStructure[pos][1] == 'x');
        MazeStructure[pos][0] = '.';
    }
    if(direction == 2) {
        do{pos = rndHeight(rnd); }
        while(MazeStructure[pos][width - 2] == 'x');
        MazeStructure[pos][width - 1] = '.';
    }
    if(direction == 3) {
        do{pos = rndWidth(rnd); }
        while(MazeStructure[length - 2][pos] == 'x');
        MazeStructure[length - 1][pos] = '.';
    } 
}

///
/// Helper Section - Contains functions to get info
///                  about the maze and to clean it up
///

void MazeUtil::PrintMazeInfo() {
    std::cout << "**Printing Maze**" << std::endl;
    std::cout << "BasePoint: " << basePoint << std::endl;
    std::cout << "Structure:" << std::endl;
    for(int i = 0; i < length; ++i) {
        for(int j = 0; j < width; ++j) {
            std::cout << MazeStructure[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "**End Printing Maze**" << std::endl;
}

MazeUtil::~MazeUtil() {
    for(int i = 0; i < length; ++i) {
        delete[] MazeStructure[i]; // delete inner arrays
    }

    delete[] MazeStructure;
    MazeStructure = nullptr;
}