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

vector<int> ParseLine(string line) {
    istringstream lineToParse(line);

    vector<int> ivec;

    int number = 0;
    char comma = '0';

    while(lineToParse >> number >> comma && comma == ',') {
        ivec.push_back(number);
    }
    return ivec;
}

vector<vector<int>> ReadBoardFile() {
    ifstream boardFile;
    boardFile.open(fileName::boardFileName);
    
    vector<vector<int>> gridRow;

    if (boardFile) {
        cout << "Board file successfully opened" << std::endl;
        string line;
        while(getline(boardFile, line)) {
            gridRow.push_back(ParseLine(line));
        }
    }
    return gridRow;
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