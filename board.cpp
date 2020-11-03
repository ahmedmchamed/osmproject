#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>

using std::sort;
using std::cout;
using std::string;
using std::vector;
using std::ifstream;
using std::istringstream;

namespace fileName {
    string boardFileName = "1.board";
}

namespace pathFeatures {
    enum class State {kStart, kEmpty, kObstacle, kClosed, kPath, kFinish};
}

namespace directionDeltas {
    const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
} 


vector<pathFeatures::State> ParseLine(string line) {

    istringstream lineToParse(line);

    vector<pathFeatures::State> stateVec;

    int number = 0;
    char comma = '0';

    while(lineToParse >> number >> comma && comma == ',') {
        switch(number) {
            case 0: stateVec.push_back(pathFeatures::State::kEmpty);
                break;
            case 1: stateVec.push_back(pathFeatures::State::kObstacle);
                break;
            default: cout << "Invalid data to push back";
                break; 
        }
    }
    return stateVec;
}

bool CheckValidCell(int xValue, int yValue, vector<vector<pathFeatures::State>> &grid) {
    if (grid.begin() != grid.end()) {
        if (xValue > 0 && xValue < grid.size()) {
            if (yValue > 0 && yValue < grid[xValue].size()) {
                return grid[xValue][yValue] == pathFeatures::State::kEmpty;
            }
        }
    }
    return false;
}

bool Compare(vector<int> node, vector<int> neighbourNode) {
    return node[2] + node[3] > neighbourNode[2] + neighbourNode[3];
}

vector<vector<pathFeatures::State>> ReadBoardFile(string filePath) {

    ifstream boardFile;
    boardFile.open(filePath);
    
    vector<vector<pathFeatures::State>> grid;

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

string CellString(pathFeatures::State state) {

    if (state == pathFeatures::State::kEmpty) {
        return "0 ";
    }
    if (state == pathFeatures::State::kObstacle) {
        return "⛰️ ";
    }

    return string();
}

void PrintBoard(const vector<vector<pathFeatures::State>> &grid) {

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
    vector<vector<pathFeatures::State>> &grid) {

        vector<int> node{x, y, g, h};

        openNodes.push_back(node);

        grid[x][y] = pathFeatures::State::kClosed;
}

vector<vector<pathFeatures::State>> Search(
    vector<vector<pathFeatures::State>> grid, 
    int *initNode, 
    int *goalNode) {

        vector<vector<int>> openNodes{};

        int xInit = initNode[0];
        int yInit = initNode[1];
        int xGoal = goalNode[0];
        int yGoal = goalNode[1];
        int g = 0;
        int h = Heuristic(xInit, yInit, xGoal, yGoal);

        AddToOpen(xInit, yInit, g, h, openNodes, grid);

        while (openNodes.begin() != openNodes.end()) {
            sort(openNodes.begin(), openNodes.end(), Compare);

            auto currentNode = openNodes.back();
            openNodes.pop_back();

            int xCurrent = currentNode[0];
            int yCurrent = currentNode[1];
            grid[xCurrent][yCurrent] = pathFeatures::State::kPath;

            if (xCurrent == goalNode[0] && yCurrent == goalNode[1]) {
                grid[initNode[0]][initNode[1]] = pathFeatures::State::kStart;
                grid[goalNode[0]][goalNode[1]] = pathFeatures::State::kFinish;
            }

        }

        cout << "No path found!" << std::endl;
        vector<vector<pathFeatures::State>> emptyGrid{};
        return emptyGrid;
}

void ExpandNeighbours(
    const vector<int> &currentNode,
    vector<vector<int>> &openNodes,
    vector<vector<pathFeatures::State>> &grid,
    int *goalCoords) {

        int xNode = currentNode[0];
        int yNode = currentNode[1];
        int gNode = currentNode[2];
        int hNode = currentNode[3];

        for (int i = 0; i < 4; i++) {
            int xNeighbour = xNode + directionDeltas::delta[i][0];
            int yNeighbour = yNode + directionDeltas::delta[i][1];

            if (CheckValidCell(xNeighbour, yNeighbour, grid)) {
                int gNeighbour = ++gNode;
                int hNeighbour = Heuristic(xNeighbour, yNeighbour, goalCoords[0], goalCoords[1]);

                AddToOpen(xNeighbour, yNeighbour, gNeighbour, hNeighbour, openNodes, grid);
            }
        }

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

    vector<vector<pathFeatures::State>> solution  = Search(boardGrid,start, goal);

    PrintBoard(solution);
    
}