#include <iostream>
#include <fstream>
#include<string>
using namespace std;

int a[11][11];//�洢������Ϸ
int b[11];//ÿ����֪�����
int bid[11];//b��id
int bbid;//bid�ڼ���
int c[11];//ÿ����֪�����
int cid[11];//c��id
int ccid;//cid�ڼ���
int alltheanswer;//���н�
int wanttheanswer=1;
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
				if (a[i][j] == k && f == false)
					f = true;
				else if (a[i][j] == k)
					return false;
			}
		}
	}
	return true;
}
void dfs(int na, int nb) { //�ڼ��еڼ���
	if (bbid == 10) {
		alltheanswer++;
		if (wanttheanswer >= alltheanswer) {
			ofstream answer("answer.txt", ios::app);
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
		int nna = na, nnb = nb, bbidd = bbid, ccidd = ccid;
		if (ccid == 9)
			bbid++, ccid = 1;
		else
			ccid++;
		dfs(bid[bbid], cid[ccid]);
		na = nna, nb = nnb, bbid = bbidd, ccid = ccidd;
		return;
	}
	for (int i = 1; i <= 9; i++) {
		a[na][nb] = i;
		int xx, yy;
		int djgg = (na - 1) / 3 * 3 + (nb - 1) / 3 + 1;//�ڼ����Ź���
		if (checkx(na) == false || checky(nb) == false || jggfz(djgg) == false) {
			a[na][nb] = 0;
			continue;
		}
		int nna = na, nnb = nb, bbidd = bbid, ccidd = ccid;
		if (ccid == 9)
			bbid++, ccid = 1;
		else
			ccid++;
		dfs(bid[bbid], cid[ccid]);
		na = nna, nb = nnb, bbid = bbidd, ccid = ccidd;
		a[nna][nnb] = 0;
	}
}

void solve_single_sudoku()
{
	for (int i = 1; i < 10; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			cout << a[i][j] << " ";
			if (a[i][j] != 0)
				b[i]++;
			if (a[j][i] != 0)
				c[i]++;
		}
		cout << endl;
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

	dfs(bid[++bbid], cid[++ccid]); //ֱ��������д�,��дһ���𰸵�txt��
	ofstream answer("answer.txt", ios::app);
	if (answer.is_open()){
		answer << "number of answers : " << alltheanswer << endl << endl;
		answer.close();
	}
}


//�Ҹо�ÿ����⣬��������һЩԪ��
void solve()
{
	ofstream answer("answer.txt", ios::trunc);
	answer.close();
	ifstream game("game.txt");  // �滻Ϊ�����ļ���

	//��ȡ����������һ����ά������
	int row = 1;
	int col = 1;
	if (game.is_open()){
		string line;
		while (getline(game, line)){
			if (row != 0 && row % 10 == 0){
				//˵����ȡ��һ������
				//��Ҫ�������
				//�����󣬸���������Ϊ��ֵ
				solve_single_sudoku();

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
				continue;
			}
			for (char c : line){
				if (c == '.'){
					a[row][col] = 0;
					col++;
				}
				else if (c >= '1' && c <= '9'){
					a[row][col] = c - '0';
					col++;
				}
			}
			col = 1;
			row++;
		}
	}
}

//�Ȳ��Զ�������
int main()
{
	//ifstream game("game.txt");  // �滻Ϊ�����ļ���

	//int row = 1;
	//int col = 1;
	//if (game.is_open())
	//{
	//	string line;
	//	while (getline(game, line))
	//	{
	//		for (char c : line)
	//		{
	//			if (c == '.')
	//			{
	//				a[row][col] = 0;
	//				col++;
	//			}
	//			else if (c >= '1' && c <= '9')
	//			{
	//				a[row][col] = c - '0';
	//				col++;
	//			}
	//		}

	//		col = 1;
	//		row++;
	//		if (row == 10)
	//			break;
	//	}

	//}

	//for (int i = 1; i < 10; i++)
	//{
	//	for (int j = 1; j < 10; j++)
	//	{
	//		cout << a[i][j] << " ";
	//		if (a[i][j] != 0)
	//			b[i]++;
	//		if (a[j][i] != 0)
	//			c[i]++;
	//	}
	//	cout << endl;
	//}

	//for (int i = 1; i <= 9; i++)
	//	bid[i] = i, cid[i] = i;
	//for (int i = 1; i <= 9; i++) {
	//	for (int j = 1; j <= 9 - i; j++) {
	//		if (b[j] < b[j + 1])
	//			swap(b[j], b[j + 1]), swap(bid[j], bid[j + 1]);
	//		if (c[j] < c[j + 1])
	//			swap(c[j], c[j + 1]), swap(cid[j], cid[j + 1]);
	//	}
	//}

	//printf("�������������õ��Ľ�����\n");
	//cin >> wanttheanswer;
	//dfs(bid[++bbid], cid[++ccid]);
	//printf("�������н�Ϊ��%d\n\n", alltheanswer);

	solve();

	system("pause");
	return 0;
}