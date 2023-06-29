#pragma once

#include<iostream>
#include<string.h>
#include<iostream>
#include<math.h>
#include<fstream>
#include<algorithm>
using namespace std;

class Judger
{
private:
public:
	int JudgeCommand(const char* argv) {
		if (strcmp(argv, "-c") == 0 || strcmp(argv, "-s") == 0 || strcmp(argv, "-n") == 0)
			return 0;
		else
			return 1;
	}
};


class Producer
{
private:
	
public:
	bool AllisNum(string str) {
		for (int i = 0; i < (int)str.size(); i++)
		{
			int tmp = (int)str[i];
			if (tmp >= 48 && tmp <= 57)
				continue;
			else
				return false;
		}
		return true;
	}
};

class Solve
{
private:
	
public:
	int pcheck(const char* argv) {
		fstream f;
		f.open(argv, ios::in);
		if (!f)
		{
			cout << "文件不存在" << endl;
			return 0;
		}
		else
		{
			cout << "文件已经存在" << endl;
			return 1;
		}
	}
};