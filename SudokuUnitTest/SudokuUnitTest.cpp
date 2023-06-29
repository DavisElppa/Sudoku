#include "pch.h"
#include "CppUnitTest.h"
#include "../sudoku.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SudokuUnitTest
{
	TEST_CLASS(SudokuUnitTest)
	{
	public:
		TEST_METHOD(TestFirstLine)
		{
			//测试终局生成时首行稳定性
			int source[] = { 5, 1, 2, 9, 8, 7, 4, 3, 6 };
			int line = 0;
			Permutate_Permutation(source, 1, 8, Permutation, line, 20 / 72 + 1);
			int result[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			for (int i = 0; i < 9; i++)
				result[i] = Permutation[line - 1][i];
			for (int i = 0; i < 9; i++)
				Assert::AreEqual(result[i], source[i]);
		}
		TEST_METHOD(TestGenerateEndGame)
		{
			//测试终局函数
			bool res = Generate_EndGame("./test_output.txt", 10);
			Assert::AreEqual(res, true);
		}
		TEST_METHOD(TestGenerateNewGame1)
		{ 
			//测试自定义难度
			solution_path = "../../sudoku.txt";
			bool res = Generate_NewGame("../../end_game.txt", "./test_output.txt", 10, true, NORMAL, MIN_SPACE, MAX_SPACE, false);
			Assert::AreEqual(res, true);
		}
		TEST_METHOD(TestGenerateNewGame2)
		{
			//测试自定义空格数范围
			solution_path = "../../sudoku.txt";
			bool res = Generate_NewGame("../../end_game.txt", "./test_output.txt", 10, false, EASY, 40, 50, false);
			Assert::AreEqual(res, true);
		}
		TEST_METHOD(TestGenerateNewGame3)
		{
			//测试唯一解
			solution_path = "../../sudoku.txt";
			bool res = Generate_NewGame("../../end_game.txt", "./test_output.txt", 10, false, EASY, 30, 50, true);
			Assert::AreEqual(res, true);
		}
		TEST_METHOD(TestCheckX)
		{
			Assert::AreEqual(true, checkx(1));
		}
		TEST_METHOD(TestCheckY)
		{
			Assert::AreEqual(true, checky(1));
		}
		TEST_METHOD(TestJggfz1)
		{
			Assert::AreEqual(true, jggfz(1));
		}
		TEST_METHOD(TestJggfz2)
		{
			Assert::AreEqual(true, jggfz(2));
		}
		TEST_METHOD(TestJggfz3)
		{
			Assert::AreEqual(true, jggfz(3));
		}
		TEST_METHOD(TestJggfz4)
		{
			Assert::AreEqual(true, jggfz(4));
		}
		TEST_METHOD(TestJggfz5)
		{
			Assert::AreEqual(true, jggfz(5));
		}
		TEST_METHOD(TestJggfz6)
		{
			Assert::AreEqual(true, jggfz(6));
		}
		TEST_METHOD(TestJggfz7)
		{
			Assert::AreEqual(true, jggfz(7));
		}
		TEST_METHOD(TestJggfz8)
		{
			Assert::AreEqual(true, jggfz(8));
		}
		TEST_METHOD(TestJggfz9)
		{
			Assert::AreEqual(true, jggfz(9));
		}
	};
}
