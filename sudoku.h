#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H
#include "./SudokuUnitTest/pch.h"
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <ctime>
#include <random>
using namespace std;

#define MAX_SPACE 64
#define MIN_SPACE 20

#define EASY 1
#define NORMAL 2
#define HARD 3

const int Maxn = 1e6 + 10;
const int Maxm = 10;

static int Step[80][Maxm];
static int Permutation[Maxn][Maxm];

bool Permutate_Temp(int source[], int start, int end, int target[6][3], int& line);
bool Permutate_Step(int temp1[2][2], int temp2[6][3], int temp3[6][3], int max_num, int move_step[80][Maxm]);
bool Permutate_Permutation(int source[], int start, int end, int target[Maxn][Maxm], int& line, int max_num);
bool Generate_EndGame(const string& path, int num);
bool checkx(int x);
bool checky(int y);
bool jggfz(int djgg);
bool dfs(int na, int nb, const string& output_path);
bool solve_single_sudoku(const string& output_path, bool need_output);
bool Play_Game(const string& input_path, const string& output_path);
bool Generate_NewGame(const string& input_path, const string& output_path, int num, bool set_difficulty, int difficulty, int min_space, int max_space, bool only_solution);

#endif //SUDOKU_SUDOKU_H
