#include <iostream>
#include "sudoku.h"
#include "googletest/include/gtest/gtest.h"

TEST(TestCase, test1) {
    ASSERT_EQ(1, 1);
}

TEST(TestCase, test2) {
    ASSERT_EQ(1, 1);
}

TEST(TestCase, test3) {
    ASSERT_EQ(1, 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}