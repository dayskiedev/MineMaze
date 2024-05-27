#include <iostream>

bool sanatiseInput(int menuLen, int& num) {
    std::string input;
    std::cin >> input;

    for (long unsigned int i = 0; i < input.length(); ++i) {
        if (!isdigit(input[i])) { 
            std::cout << "Input must be an intger!" << std::endl;
            return false; 
            } // if input contains a string we dont want to treat it like a number
    }

    int intInput = std::stoi(input);
    if(intInput <= 0 || intInput >   menuLen) { 
        std::cout << "Input must be a number between 1 and " << menuLen << "!" << std::endl;
        return false; 
    }

    num = intInput;
    return true;
}

void printStartText(void)
{
    std::cout << std::endl;
    std::cout << "Welcome to MineCraft MazeRunner!" << std::endl;
    std::cout << "--------------------------------" << std::endl;
}

void printMainMenu(void)
{
    std::cout << std::endl;
    std::cout << "------------- MAIN MENU -------------" << std::endl;
    std::cout << "1) Create a Maze" << std::endl;
    std::cout << "2) Build Maze in MineCraft" << std::endl;
    std::cout << "3) Solve Maze" << std::endl;
    std::cout << "4) Show Team Information" << std::endl;
    std::cout << "5) Exit" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter Menu item to continue: " << std::endl;

}

void printGenerateMazeMenu(void)
{
    std::cout << std::endl;
    std::cout << "------------- CREATE A MAZE -------------" << std::endl;
    std::cout << "1) Read Maze from terminal" << std::endl;
    std::cout << "2) Generate Random Maze" << std::endl;
    std::cout << "3) Back" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter Menu item to continue: " << std::endl;
}

void printSolveMazeMenu(void)
{
    std::cout << std::endl;
    std::cout << "------------- SOLVE MAZE -------------" << std::endl;
    std::cout << "1) Solve Manually" << std::endl;
    std::cout << "2) Show Escape Route" << std::endl;
    std::cout << "3) Back" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter Menu item to continue: " << std::endl;
}

void printTeamInfo(void)
{
    std::cout << std::endl;
    std::cout << "Team members:" << std::endl;

    std::cout << "\t [1] Darcy Platt (s3657395@student.rmit.edu.au)" << std::endl;
    std::cout << "\t [2] Sidney Zeng (s4042149@student.rmit.edu.au)" << std::endl;
    std::cout << "\t [3] Brody Watson (s4040831@student.rmit.edu.au)" << std::endl;

    std::cout << std::endl;
}

void printExitMassage(void)
{
    std::cout << std::endl;
    std::cout << "The End!" << std::endl;
    std::cout << std::endl;
}