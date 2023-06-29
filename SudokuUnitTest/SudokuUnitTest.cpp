#include "pch.h"
#include "SudokuUnitTest.h"
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

			Producer soduku1;
			int re = soduku1.AllisNum("1213");
			Assert::AreEqual(re, 1);
		}
		TEST_METHOD(TestMethod2)
		{

			Producer soduku2;
			int re = soduku2.AllisNum("-10");
			Assert::AreEqual(re, 0);
		}
		TEST_METHOD(TestMethod3)
		{
			Producer soduku3;
			int re = soduku3.AllisNum("abc");
			Assert::AreEqual(re, 0);
		}
	};
}
