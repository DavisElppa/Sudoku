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
    cout << "�����վ� " << num << " ��" << endl;
}

void Generate_NewGame(string path, int num, int difficulty = EASY, int min_space = MIN_SPACE, int max_space = MAX_SPACE,
                      bool only_solution = false) {
    cout << "·����" << path << endl
         << "������" << num << endl
         << "�Ѷȣ�" << difficulty << endl
         << "�ո�������Χ��" << min_space << '~' << max_space << endl
         << "�Ƿ�Ψһ�⣺" << only_solution << endl;
}

void Play_Game(string path) {
    cout << "��ȡ��Ϸ�����" << endl;
}

int main(int n_argc, char *argv[]) {
    //��������
    vector<string> argvList;
    for (int i = 0; i < n_argc; i++)
        argvList.push_back(argv[i]);
    if (argvList[1] == "-c") {
        //�����վ��ļ�
        int num = atoi(argvList[2].c_str());
        string generate_path = "./end_game.txt";
        Generate_EndGame(generate_path, num);
    } else if (argvList[1] == "-s") {
        //��ȡ�����ļ������
        string game_path = argvList[2];
        Play_Game(game_path);
    } else if (argvList[1] == "-n") {
        //������Ϸ
        int num = atoi(argvList[2].c_str());
        string generate_path = "./game.txt";
        if (argvList.size() == 3) {
            //����ָ����������Ϸ
            Generate_NewGame(generate_path, num);
        } else if (argvList.size() > 3) {
            if (argvList[3] == "-m") {
                //����ָ���Ѷȵ���Ϸ
                int difficulty = atoi(argvList[4].c_str());
                Generate_NewGame(generate_path, num, difficulty);
            } else if (argvList[3] == "-r") {
                //����ָ���ո�������Χ����Ϸ
                string scope = argvList[4];
                size_t pos = scope.find('~');
                int min_space = atoi(scope.substr(0, pos).c_str());
                int max_space = atoi(scope.substr(pos + 1, scope.size()).c_str());
                Generate_NewGame(generate_path, num, EASY, min_space, max_space);
            } else if (argvList[3] == "-u") {
                //����Ψһ�����Ϸ
                Generate_NewGame(generate_path, num, EASY, MIN_SPACE, MAX_SPACE, true);
            }
        }
    }
    return 0;
}