#include <iostream>
#include <vector>
#include <fstream>
using std::cout;
using std::vector;

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

}