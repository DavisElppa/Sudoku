#include "pch.h"
#include "CppUnitTest.h"
#include "../sudoku.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SudokuUnitTest
{
	TEST_CLASS(SudokuUnitTest)
	{
	public:
		TEST_METHOD(TestMethod1)
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
		TEST_METHOD(TestMethod2)
		{
			bool res = Generate_NewGame("../end_game.txt", "./test_output.txt", 100, true, HARD, MIN_SPACE, MAX_SPACE, true);
			Assert::AreEqual(res, true);
		}
		TEST_METHOD(TestMethod2)
		{
			bool res = Generate_NewGame("../end_game.txt", "./test_output.txt", 100, true, HARD, MIN_SPACE, MAX_SPACE, true);
			Assert::AreEqual(res, true);
		}
	};
}
