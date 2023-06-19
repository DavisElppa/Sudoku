#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

#define MAX_SPACE 64
#define MIN_SPACE 20

#define EASY 1
#define NORMAL 2
#define HARD 3

using namespace std;

typedef struct Point {
    int row;
    int col;
    int val;
} Point;

void Generate_EndGame(string path, int num) {
    cout << "生成终局 " << num << " 个" << endl;
}

void Generate_NewGame(string path, int num, int difficulty = EASY, int min_space = MIN_SPACE, int max_space = MAX_SPACE,
                      bool only_solution = false) {
    cout << "路径：" << path << endl
         << "数量：" << num << endl
         << "难度：" << difficulty << endl
         << "空格数量范围：" << min_space << '~' << max_space << endl
         << "是否唯一解：" << only_solution << endl;
}

void Play_Game(string path) {
    cout << "读取游戏并求解" << endl;
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
        Play_Game(game_path);
    } else if (argvList[1] == "-n") {
        //生成游戏
        int num = atoi(argvList[2].c_str());
        string generate_path = "./game.txt";
        if (argvList.size() == 3) {
            //生成指定数量的游戏
            Generate_NewGame(generate_path, num);
        } else if (argvList.size() > 3) {
            if (argvList[3] == "-m") {
                //生成指定难度的游戏
                int difficulty = atoi(argvList[4].c_str());
                Generate_NewGame(generate_path, num, difficulty);
            } else if (argvList[3] == "-r") {
                //生成指定空格数量范围的游戏
                string scope = argvList[4];
                size_t pos = scope.find('~');
                int min_space = atoi(scope.substr(0, pos).c_str());
                int max_space = atoi(scope.substr(pos + 1, scope.size()).c_str());
                Generate_NewGame(generate_path, num, EASY, min_space, max_space);
            } else if (argvList[3] == "-u") {
                //生成唯一解的游戏
                Generate_NewGame(generate_path, num, EASY, MIN_SPACE, MAX_SPACE, true);
            }
        }
    }
    return 0;
}