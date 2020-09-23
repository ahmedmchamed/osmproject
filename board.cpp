#include <iostream>
#include <vector>
#include <fstream>

using std::cout;
using std::string;
using std::vector;
using std::ifstream;

namespace fileName {
    string boardFileName = "1.board";
}

void ReadBoardFile() {
    ifstream boardFile;
    boardFile.open(fileName::boardFileName);

    if (boardFile) {
        cout << "Board file successfully opened" << std::endl;
        string line;
        while(getline(boardFile, line)) {
            cout << line << std::endl;
        }
    }
}

void PrintBoard(const vector<vector<int>> &board) {
    for(const auto &row : board) {
        for(const auto &number : row) {
            cout << number;
        }
        cout << std::endl;
    }
}

int main() {

    vector<vector<int>> board{
        {0, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0}
    };

    PrintBoard(board);

ReadBoardFile();
}