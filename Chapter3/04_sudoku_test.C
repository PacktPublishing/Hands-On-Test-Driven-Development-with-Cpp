#include "04_sudoku.h"
#include "04_sudoku.C"

#include <gtest/gtest.h>

class SudokuTest : public ::testing::Test {
    public:
    Sudoku S;
};

TEST_F(SudokuTest, Construct) {
    EXPECT_EQ(0, S.get(0, 0));
    EXPECT_EQ(0, S.get(8, 8));
}

TEST_F(SudokuTest, Set) {
    S.set(0, 0, 5);
    EXPECT_EQ(5, S.get(0, 0));
    EXPECT_EQ(0, S.get(0, 2));
}

TEST_F(SudokuTest, Set1) { // With a test loop
    S.set(0, 0, 5);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (i == 0 && j == 0) 
                EXPECT_EQ(5, S.get(i, j));
            else
                EXPECT_EQ(0, S.get(i, j)) <<
                    "i=" << i << " j=" << j;
        }
    }
}

class SudokuTestP : public SudokuTest,
                    public ::testing::WithParamInterface<int>
{
};

TEST_P(SudokuTestP, Set) { // Parameterized test
    const int i0 = GetParam()/9, j0 = GetParam() % 9;
    S.set(i0, j0, 5);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (i == i0 && j == j0) 
                EXPECT_EQ(5, S.get(i, j)) <<
                    "i0=" << i0 << " j0=" << j0;
            else
                EXPECT_EQ(0, S.get(i, j)) <<
                    "i=" << i << " j=" << j <<
                    "i0=" << i0 << " j0=" << j0;
        }
    }
}

INSTANTIATE_TEST_CASE_P(SetEach, SudokuTestP, ::testing::Range(0, 81));

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

TEST_F(SudokuTest, GetMask) {
    EXPECT_EQ(Sudoku::mask(0), S.get_mask(1, 1));
    S.set(0, 0, 1);
    EXPECT_EQ(Sudoku::mask(0) & ~Sudoku::mask(1), S.get_mask(1, 1));
    S.set(0, 1, 2);
    EXPECT_EQ(Sudoku::mask(0) & ~Sudoku::mask(1) & ~Sudoku::mask(2), S.get_mask(1, 1));
    S.set(5, 1, 3);
    EXPECT_EQ(Sudoku::mask(0) & ~Sudoku::mask(1) & ~Sudoku::mask(2) & ~Sudoku::mask(3), S.get_mask(1, 1));
    S.set(1, 8, 4);
    EXPECT_EQ(Sudoku::mask(0) & ~Sudoku::mask(1) & ~Sudoku::mask(2) & ~Sudoku::mask(3) & ~Sudoku::mask(4), S.get_mask(1, 1));
}

