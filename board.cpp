#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using std::cout;
using std::string;
using std::vector;
using std::ifstream;
using std::istringstream;

namespace fileName {
    string boardFileName = "1.board";
}

namespace obstacles {
    enum class State {kEmpty, kObstacle, kClosed};
}

vector<obstacles::State> ParseLine(string line) {

    istringstream lineToParse(line);

    vector<obstacles::State> stateVec;

    int number = 0;
    char comma = '0';

    while(lineToParse >> number >> comma && comma == ',') {
        switch(number) {
            case 0: stateVec.push_back(obstacles::State::kEmpty);
                break;
            case 1: stateVec.push_back(obstacles::State::kObstacle);
                break;
            default: cout << "Invalid data to push back";
                break; 
        }
    }
    return stateVec;
}

vector<vector<obstacles::State>> ReadBoardFile(string filePath) {

    ifstream boardFile;
    boardFile.open(filePath);
    
    vector<vector<obstacles::State>> grid;

    if (boardFile) {
        cout << "Board file successfully opened" << std::endl;
        string line;
        while(getline(boardFile, line)) {
            grid.push_back(ParseLine(line));
        }
    }
    return grid;
}

int Heuristic(int x1, int y1, int x2, int y2) {

    int result = std::abs(x2 -x1) + std::abs(y2 - y1);

    return result;
}

vector<vector<obstacles::State>> Search(

    vector<vector<obstacles::State>> grid, 
    int *start, 
    int *end) {
    
    cout << "No path found!" << std::endl;
    vector<vector<obstacles::State>> emptyGrid{};

    return emptyGrid;
}

string CellString(obstacles::State state) {

    if (state == obstacles::State::kEmpty) {
        return "0 ";
    }
    if (state == obstacles::State::kObstacle) {
        return "⛰️ ";
    }

    return string();
}

void PrintBoard(const vector<vector<obstacles::State>> &grid) {

    for(const auto &row : grid) {
        for(const auto &number : row) {
            cout << CellString(number);
        }
        cout << std::endl;
    }
}

void AddToOpen(
    int x, 
    int y, 
    int g, 
    int h, 
    vector<vector<int>> &openNodes, 
    vector<vector<obstacles::State>> &grid) {

        vector<int> node{x, y, g, h};

        openNodes.push_back(node);

        grid[x][y] = obstacles::State::kClosed;
}

int main() {

    int start[2]{0, 0};
    int goal[2]{4, 5};

    auto boardGrid = ReadBoardFile(fileName::boardFileName);
    // vector<vector<int>> board{
    //     {0, 1, 0, 0, 0, 0},
    //     {0, 1, 0, 0, 0, 0},
    //     {0, 1, 0, 0, 0, 0},
    //     {0, 1, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 1, 0}
    // };

    vector<vector<obstacles::State>> solution  = Search(boardGrid,start, goal);

    PrintBoard(solution);
    
}