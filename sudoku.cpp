#include<iostream>
#include <fstream>

using namespace std;

typedef struct Point {
    int row;
    int col;
    int val;
} Point;

void Generate_Sudoku(string path) {
    ofstream fout;
    fout.open(path);
    fout.close();
}

int main() {
    string generate_path = "../sudoku.txt";
    Generate_Sudoku(generate_path);
    return 0;
}