#include "01_sudoku.h"
#include "01_sudoku.C"

#include <gtest/gtest.h>

TEST(Sudoku, Construct) {
    Sudoku S;
    EXPECT_EQ(0, S.get(0, 0));
    EXPECT_EQ(0, S.get(8, 8));
}

TEST(Sudoku, Set) {
    Sudoku S;
    S.set(0, 0, 5);
    EXPECT_EQ(5, S.get(0, 0));
    EXPECT_EQ(0, S.get(0, 2));
}

class SudokuTest : public ::testing::Test {
    public:
    Sudoku S;
};

TEST_F(SudokuTest, OutOfRange) {
    EXPECT_THROW(S.get(9, 0), std::logic_error);
    EXPECT_THROW(S.set(2, 10, 1), std::logic_error);
}

TEST_F(SudokuTest, BadValue) {
    EXPECT_THROW(S.set(2, 1, 0), std::logic_error);
    EXPECT_THROW(S.set(2, 1, 10), std::logic_error);
}

TEST_F(SudokuTest, Reset) {
    S.set(2, 1, 5);
    EXPECT_THROW(S.set(2, 1, 6), std::logic_error);
}
