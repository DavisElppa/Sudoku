#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <ctime>
#include <random>

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

void Permutate_Step(int temp1[2][2], int temp2[6][3], int temp3[6][3], int max_num, int move_step[80][Maxm]) {
    int cnt = 0;
    for (int i = 0; i < 2; i++) {
        //  ���������������У���ѡһ
        for (int j = 0; j < 6; j++) {
            //  ��������������ȫ���У���ѡһ
            for (int k = 0; k < 6; k++) {
                //  �߰˾���������ȫ���У���ѡһ
                for (int r = 0; r < 8; r++) {
                    //  ÿ��������8��Ԫ�أ���Ԫ�ز�����
                    if (r < 2)
                        move_step[cnt][r] = temp1[i][r];
                    else if (r < 5)
                        move_step[cnt][r] = temp2[j][r - 2];
                    else
                        move_step[cnt][r] = temp3[k][r - 5];
                }
                cnt++;
                if (cnt >= max_num)
                    return;
            }
        }
    }
}

void Permutate_Permutation(int source[], int start, int end, int target[Maxn][Maxm], int &line, int max_num)  //ȫ����
{
    if (start > end)  // ��ֹ������󣬵���Խ��
        start = end;

    if (start == end)    //  ��ֹ����
    {
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

void Generate_EndGame(const string &path, int num) {
    ofstream fout;
    fout.open(path);

    int source2[] = {1, 4, 7}, source3[] = {2, 5, 8};
    int temp1[2][2], temp2[6][3], temp3[6][3];
    int line2 = 0, line3 = 0;
    temp1[0][0] = 3, temp1[0][1] = 6;
    temp1[1][0] = 6, temp1[1][1] = 3;
    Permutate_Temp(source2, 0, 2, temp2, line2);
    Permutate_Temp(source3, 0, 2, temp3, line3);
    Permutate_Step(temp1, temp2, temp3, min(num, 72), Step);

    int source[] = {5, 1, 2, 9, 8, 7, 4, 3, 6};
    int line = 0;
    Permutate_Permutation(source, 1, 8, Permutation, line, num / 72 + 1);
    for (int cnt = 0; cnt < num; cnt++) {
        //ͨ��ƽ�ƣ����������վ�
        int pl = cnt / 72;
        int ml = cnt % 72;
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
        if (cnt != num - 1) {
            fout << "\n";
        }
    }
}

void Generate_NewGame(const string &input_path, const string &output_path, int num, bool set_difficulty,
                      int difficulty = EASY,
                      int min_space = MIN_SPACE, int max_space = MAX_SPACE, bool only_solution = false) {
    char game[9][9] = {0};
    srand(time(nullptr));
    ifstream fin;
    fin.open(input_path);
    ofstream fout;
    fout.open(output_path);
    for (int cnt = 0; cnt < num; cnt++) {
        //��ȡ�վ�
        if (fin.eof()) {
            fin.clear();
            fin.seekg(0, ios::beg);
        }
        bool err = false;
        for (auto &i: game) {
            for (char &j: i) {
                fin >> j;
                if (j == '.') {
                    err = true;
                    break;
                }
            }
        }
        if (err) {
            cnt--;
            continue;
        }
        //������Ϸ
        if (only_solution) {

        } else {
            int num_space = 0;
            if (set_difficulty) {
                switch (difficulty) {
                    case EASY:
                        //20~31��
                        num_space = rand() % 12 + 20;
                        break;
                    case NORMAL:
                        //32~47��
                        num_space = rand() % 16 + 32;
                        break;
                    case HARD:
                        //48~64��
                        num_space = rand() % 17 + 48;
                        break;
                    default:
                        break;
                }
            } else {
                num_space = rand() % (max_space - min_space + 1) + min_space;
            }
            random_device rd;
            mt19937 r_eng(rd());
            bool ret = false;
            for (int i = 0; i < num_space; i++) {
                int row = r_eng() % 9;
                int col = r_eng() % 9;
                if (game[row][col] != '.') {
                    game[row][col] = '.';
                } else {
                    if (!ret) {
                        ret = true;
                        for (auto &m: game) {
                            bool if_break = false;
                            for (char &n: m) {
                                if (n != '.') {
                                    n = '.';
                                    if_break = true;
                                    break;
                                }
                            }
                            if (if_break)
                                break;
                        }
                    } else {
                        ret = false;
                        for (int m = 8; m >= 0; m--) {
                            bool if_break = false;
                            for (int n = 8; n >= 0; n--) {
                                if (game[m][n] != '.') {
                                    game[m][n] = '.';
                                    if_break = true;
                                    break;
                                }
                            }
                            if (if_break)
                                break;
                        }
                    }
                }
            }
        }
        //д����Ϸ�ļ�
        for (auto &i: game) {
            for (int j = 0; j < 8; j++) {
                fout << i[j] << " ";
            }
            fout << i[8] << endl;
        }
        fout << endl;
    }
    fin.close();
    fout.close();
}

//***************************************************************************
//***************************************************************************
//******************************���������Ϸ����******************************
//***************************************************************************
//***************************************************************************

int a[11][11];//�洢������Ϸ
int b[11];//ÿ����֪�����
int bid[11];//b��id
int bbid;//bid�ڼ���
int c[11];//ÿ����֪�����
int cid[11];//c��id
int ccid;//cid�ڼ���
int alltheanswer;//���н�
int wanttheanswer = 1;

bool checkx(int x) {//xΪ�ڼ���
    for (int i = 1; i <= 9; i++) {
        if (a[x][i] == 0)
            continue;
        for (int j = 1; j < i; j++)
            if (a[x][i] == a[x][j])
                return false;
    }
    return true;
}

bool checky(int y) { //yΪ�ڼ���
    for (int i = 1; i <= 9; i++) {
        if (a[i][y] == 0)
            continue;
        for (int j = 1; j < i; j++)
            if (a[i][y] == a[j][y])
                return false;
    }
    return true;
}

bool jggfz(int djgg) {
    int x, y;
    if (djgg == 1)
        x = 1, y = 1;
    else if (djgg == 2)
        x = 1, y = 4;
    else if (djgg == 3)
        x = 1, y = 7;
    else if (djgg == 4)
        x = 4, y = 1;
    else if (djgg == 5)
        x = 4, y = 4;
    else if (djgg == 6)
        x = 4, y = 7;
    else if (djgg == 7)
        x = 7, y = 1;
    else if (djgg == 8)
        x = 7, y = 4;
    else
        x = 7, y = 7;
    for (int k = 1; k <= 9; k++) {
        bool f = false;
        for (int i = x; i < x + 3; i++) {
            for (int j = y; j < y + 3; j++) {
                if (a[i][j] == 0)
                    continue;
                if (a[i][j] == k && !f)
                    f = true;
                else if (a[i][j] == k)
                    return false;
            }
        }
    }
    return true;
}

void dfs(int na, int nb, const string &output_path) { //�ڼ��еڼ���
    if (alltheanswer >= 10000) //����̫���Ӵ������ٶȾͻ��ú���
        return;
    if (bbid == 10) {
        alltheanswer++;
        if (wanttheanswer >= alltheanswer) {
            ofstream answer(output_path, ios::app);
            if (answer.is_open()) {
                for (int i = 1; i <= 9; i++) {
                    for (int j = 1; j <= 8; j++) {
                        //ֱ�Ӱѵ�һ����д���ļ�answer.txt
                        //ÿ����׷�ӵķ�ʽд��
                        answer << a[i][j] << " ";
                    }
                    answer << a[i][9] << endl;
                }
                answer.close();
            }
        }
        return;
    }
    if (a[na][nb] != 0) {
        int bbidd = bbid, ccidd = ccid;
        if (ccid == 9)
            bbid++, ccid = 1;
        else
            ccid++;
        dfs(bid[bbid], cid[ccid], output_path);
        bbid = bbidd, ccid = ccidd;
        return;
    }
    for (int i = 1; i <= 9; i++) {
        a[na][nb] = i;
        int djgg = (na - 1) / 3 * 3 + (nb - 1) / 3 + 1;//�ڼ����Ź���
        if (!checkx(na) || !checky(nb) || !jggfz(djgg)) {
            a[na][nb] = 0;
            continue;
        }
        int nna = na, nnb = nb, bbidd = bbid, ccidd = ccid;
        if (ccid == 9)
            bbid++, ccid = 1;
        else
            ccid++;
        dfs(bid[bbid], cid[ccid], output_path);
        na = nna, nb = nnb, bbid = bbidd, ccid = ccidd;
        a[nna][nnb] = 0;
    }
}

void solve_single_sudoku(const string &output_path) {
    for (int i = 1; i < 10; i++) {
        for (int j = 1; j < 10; j++) {
            if (a[i][j] != 0)
                b[i]++;
            if (a[j][i] != 0)
                c[i]++;
        }
    }

    for (int i = 1; i <= 9; i++)
        bid[i] = i, cid[i] = i;
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9 - i; j++) {
            if (b[j] < b[j + 1])
                swap(b[j], b[j + 1]), swap(bid[j], bid[j + 1]);
            if (c[j] < c[j + 1])
                swap(c[j], c[j + 1]), swap(cid[j], cid[j + 1]);
        }
    }

    dfs(bid[++bbid], cid[++ccid], output_path); //ֱ��������д�,��дһ���𰸵�txt��
    ofstream answer(output_path, ios::app);
    if (answer.is_open()) {
        if (alltheanswer < 10000)
            answer << "number of answers : " << alltheanswer << endl << endl;
        else
            answer << "number of answers exceed 10000" << endl << endl;
        answer.close();
    }
}

void Play_Game(const string &input_path, const string &output_path) {
    ofstream answer(output_path, ios::trunc); //�������ļ�
    answer.close();
    ifstream game(input_path);  // �滻Ϊ�����ļ���

    //��ȡ����������һ����ά������
    int sudoku_num = 1;//ͳ���������������
    int row = 1;
    int col = 1;
    if (game.is_open()) {
        string line;
        while (getline(game, line)) {
            if (row != 0 && row % 10 == 0) {
                //˵����ȡ��һ������
                //��Ҫ�������
                //�����󣬸���������Ϊ��ֵ
                solve_single_sudoku(output_path);
                cout << "������" << sudoku_num << "������" << endl;
                memset(a, 0, sizeof(a));
                memset(b, 0, sizeof(b));
                memset(bid, 0, sizeof(bid));
                bbid = 0;
                memset(c, 0, sizeof(c));
                memset(cid, 0, sizeof(cid));
                ccid = 0;
                alltheanswer = 0;
                wanttheanswer = 1;
                row = 1;
                sudoku_num++;
                continue;
            }
            for (char ch: line) {
                if (ch == '.') {
                    a[row][col] = 0;
                    col++;
                } else if (ch >= '1' && ch <= '9') {
                    a[row][col] = ch - '0';
                    col++;
                }
            }
            col = 1;
            row++;
        }
    }
}

int main(int n_argc, char *argv[]) {
    //��������
    vector<string> argvList;
    for (int i = 0; i < n_argc; i++)
        argvList.emplace_back(argv[i]);
    if (argvList[1] == "-c") {
        //�����վ��ļ�
        int num = atoi(argvList[2].c_str());
        string generate_path = "./end_game.txt";
        Generate_EndGame(generate_path, num);
    } else if (argvList[1] == "-s") {
        //��ȡ�����ļ������
        string game_path = argvList[2];
        string output_path = "./sudoku.txt";
        Play_Game(game_path, output_path);
    } else if (argvList[1] == "-n") {
        //������Ϸ
        int num = atoi(argvList[2].c_str());
        string input_path = "./end_game.txt";
        string generate_path = "./game.txt";
        if (argvList.size() == 3) {
            //����ָ����������Ϸ
            Generate_NewGame(input_path, generate_path, num, false);
        } else if (argvList.size() > 3) {
            if (argvList[3] == "-m") {
                //����ָ���Ѷȵ���Ϸ
                int difficulty = atoi(argvList[4].c_str());
                Generate_NewGame(input_path, generate_path, num, true, difficulty);
            } else if (argvList[3] == "-r") {
                //����ָ���ո�������Χ����Ϸ
                string scope = argvList[4];
                size_t pos = scope.find('~');
                int min_space = atoi(scope.substr(0, pos).c_str());
                int max_space = atoi(scope.substr(pos + 1, scope.size()).c_str());
                Generate_NewGame(input_path, generate_path, num, false, EASY, min_space, max_space);
            } else if (argvList[3] == "-u") {
                //����Ψһ�����Ϸ
                Generate_NewGame(input_path, generate_path, num, false, EASY, MIN_SPACE, MAX_SPACE, true);
            } else {
                cout << "�����Ƿ���" << endl;
            }
        }
    } else {
        cout << "�����Ƿ���" << endl;
    }

    return 0;
}