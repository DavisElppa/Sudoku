#include <iostream>
#include <fstream>
#include<string>
using namespace std;

int a[11][11];//存储数独游戏
int b[11];//每行已知数最多
int bid[11];//b的id
int bbid;//bid第几个
int c[11];//每列已知数最多
int cid[11];//c的id
int ccid;//cid第几个
int maxx;
int alltheanswer;
int wanttheanswer;
bool checkx(int x) {//x为第几行
	for (int i = 1; i <= 9; i++) {
		if (a[x][i] == 0)
			continue;
		for (int j = 1; j < i; j++)
			if (a[x][i] == a[x][j])
				return false;
	}
	return true;
}
bool checky(int y) { //y为第几列
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
void dfs(int na, int nb) { //第几行第几个
	if (bbid == 10) {
		alltheanswer++;
		if (wanttheanswer >= alltheanswer) {
			printf("\n");
			printf("此题解%d\n", alltheanswer);
			for (int i = 1; i <= 9; i++) {
				for (int j = 1; j <= 9; j++) {
					if ((i == 4 && j == 1) || (i == 7 && j == 1))
						printf(" -------------------\n");
					else if (j == 4 || j == 7)
						printf("|");
					printf("%2d", a[i][j]);
				}
				printf("\n");
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
		int djgg = (na - 1) / 3 * 3 + (nb - 1) / 3 + 1;//第几个九宫格
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

//先测试读入数据
int main()
{
	ifstream game("game.txt");  // 替换为您的文件名

	int row = 1;
	int col = 1;
	if (game.is_open())
	{
		string line;
		while (getline(game, line))
		{
			for (char c : line)
			{
				if (c == '.')
				{
					a[row][col] = 0;
					col++;
				}
				else if (c >= '1' && c <= '9')
				{
					a[row][col] = c - '0';
					col++;
				}
			}

			col = 1;
			row++;
			if (row == 10)
				break;
		}

	}

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

	printf("请输入你期望得到的解数：\n");
	cin >> wanttheanswer;
	dfs(bid[++bbid], cid[++ccid]);
	printf("此题所有解为：%d\n\n", alltheanswer);

	system("pause");
	return 0;
}