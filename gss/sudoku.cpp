#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <ctime>

#define MAX_SPACE 64
#define MIN_SPACE 20

#define EASY 1
#define NORMAL 2
#define HARD 3

const int Maxn = 1e6 + 10;
const int Maxm = 10;

int Step[80][Maxm];
int Permutation[Maxn][Maxm];

using namespace std;

typedef struct Point {
    int row;
    int col;
    int val;
} Point;

void Permutate_Temp(int source[], int start, int end, int target[6][3], int &line) {
    if (start > end)
        start = end;
    if (start == end) {
        for (int i = 0; i <= end; i++)
            target[line][i] = source[i];
        line++;
    } else {
        for (int i = start; i <= end; i++) {
            swap(source[i], source[start]);
            Permutate_Temp(source, start + 1, end, target, line);
            swap(source[i], source[start]);
        }
    }
}

void Permutate_Permutation(int source[], int start, int end, int target[Maxn][Maxm], int &line, int max_num)  //全排序
{
    if (start > end)
        start = end;
    if (start == end) {
        for (int i = 0; i <= end; i++)
            target[line][i] = source[i];
        line++;
    } else {
        for (int i = start; i <= end; i++) {
            if (line >= max_num)
                return;
            swap(source[i], source[start]);
            Permutate_Permutation(source, start + 1, end, target, line, max_num);
            swap(source[i], source[start]);
        }
    }
}

void Generate_EndGame(string path, int num) {
    ofstream fout;
    fout.open(path);

    int source2[] = {1, 4, 7}, source3[] = {2, 5, 8};
    int temp1[2][2], temp2[6][3], temp3[6][3];
    int line2 = 0, line3 = 0;
    temp1[0][0] = 3, temp1[0][1] = 6;
    temp1[1][0] = 6, temp1[1][1] = 3;
    Permutate_Temp(source2, 0, 2, temp2, line2);
    Permutate_Temp(source3, 0, 2, temp3, line3);
    int cnt = 0;
    for (int i = 0; i < 2; i++) {
        //  二三行有两个排列，二选一
        for (int j = 0; j < 6; j++) {
            //  四五六行有六个全排列，六选一
            for (int k = 0; k < 6; k++) {
                //  七八九行有六个全排列，六选一
                for (int r = 0; r < 8; r++) {
                    //  每个排列有8个元素（首元素不动）
                    if (r < 2)
                        Step[cnt][r] = temp1[i][r];
                    else if (r < 5)
                        Step[cnt][r] = temp2[j][r - 2];
                    else
                        Step[cnt][r] = temp3[k][r - 5];
                }
                cnt++;
                if (cnt >= min(num, 72))
                    return;
            }
        }
    }

    int source[] = {5, 1, 2, 9, 8, 7, 4, 3, 6};
    int line = 0;
    Permutate_Permutation(source, 1, 8, Permutation, line, num / 72 + 1);
    for (int t = 0; t < num; t++) {
        //通过平移，生成数独终局
        int pl = t / 72;
        int ml = t % 72;
        char temp[200];
        int temp_site = 0;
        memset(temp, 0, sizeof(char) * 200);
        for (int i = 0; i < 9; i++) {
            temp[temp_site] = Permutation[pl][i] + '0';
            temp_site++;
            if (i == 8) {
                temp[temp_site] = '\n';
                temp_site++;
            } else {
                temp[temp_site] = ' ';
                temp_site++;
            }
        }
        for (int i = 1; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                int site = (j + Step[ml][i - 1]) % 9;
                temp[temp_site] = Permutation[pl][site] + '0';
                temp_site++;
                if (j == 8) {
                    temp[temp_site] = '\n';
                    temp_site++;
                } else {
                    temp[temp_site] = ' ';
                    temp_site++;
                }
            }
        }
        int index = 0;
        while (temp[index] != 0) {
            fout << temp[index];
            index++;
        }
        if (t != num - 1) {
            fout << "\n";
        }
    }
}

void Generate_NewGame(string input_path, string output_path, int num, bool set_difficulty, int difficulty = EASY,
                      int min_space = MIN_SPACE, int max_space = MAX_SPACE, bool only_solution = false) {
    char game[9][9] = {0};
    srand(time(nullptr));
    ifstream fin;
    fin.open(input_path);
    ofstream fout;
    fout.open(output_path);
    for (int cnt = 0; cnt < num; cnt++) {
        //读取终局
        if (fin.eof()) {
            fin.clear();
            fin.seekg(0, ios::beg);
        }
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                fin >> game[i][j];
        //生成游戏
        int num_space = 0;
        if (set_difficulty) {
            switch (difficulty) {
                case EASY:
                    //20~31空
                    num_space = rand() % 12 + 20;
                    break;
                case NORMAL:
                    //32~47空
                    num_space = rand() % 16 + 32;
                    break;
                case HARD:
                    //48~64空
                    num_space = rand() % 17 + 48;
                    break;
                default:
                    break;
            }
        } else {
            num_space = rand() % (max_space - min_space + 1) + min_space;
        }
        cout << num_space << endl;
        int nums = num_space;
        while (nums > 0) {
            int row = rand() % 9;
            int col = rand() % 9;
            if (game[row][col] != '.') {
                game[row][col] = '.';
                nums--;
            }
        }
        //写入游戏文件
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 8; j++) {
                fout << game[i][j] << " ";
            }
            fout << game[i][8] << endl;
        }
        fout << endl;
    }
    fin.close();
    fout.close();
}

void Play_Game(string input_path, string output_path) {

}

int main(int n_argc, char *argv[]) {
    //解析参数
    vector<string> argvList;
    for (int i = 0; i < n_argc; i++)
        argvList.push_back(argv[i]);
    if (argvList[1] == "-c") {
        //生成终局文件
        int num = atoi(argvList[2].c_str());
        string generate_path = "./end_game.txt";
        Generate_EndGame(generate_path, num);
    } else if (argvList[1] == "-s") {
        //读取棋盘文件并求解
        string game_path = argvList[2];
        string output_path = "./sudoku.txt";
        Play_Game(game_path, output_path);
    } else if (argvList[1] == "-n") {
        //生成游戏
        int num = atoi(argvList[2].c_str());
        string input_path = "./end_game.txt";
        string generate_path = "./game.txt";
        if (argvList.size() == 3) {
            //生成指定数量的游戏
            Generate_NewGame(input_path, generate_path, num, false);
        } else if (argvList.size() > 3) {
            if (argvList[3] == "-m") {
                //生成指定难度的游戏
                int difficulty = atoi(argvList[4].c_str());
                Generate_NewGame(input_path, generate_path, num, true, difficulty);
            } else if (argvList[3] == "-r") {
                //生成指定空格数量范围的游戏
                string scope = argvList[4];
                size_t pos = scope.find('~');
                int min_space = atoi(scope.substr(0, pos).c_str());
                int max_space = atoi(scope.substr(pos + 1, scope.size()).c_str());
                Generate_NewGame(input_path, generate_path, num, false, EASY, min_space, max_space);
            } else if (argvList[3] == "-u") {
                //生成唯一解的游戏
                Generate_NewGame(input_path, generate_path, num, false, EASY, MIN_SPACE, MAX_SPACE, true);
            }
        }
    }
    return 0;
}