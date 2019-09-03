#include "07_sudoku.h"
#include "07_sudoku.C"

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

TEST_F(SudokuTest, InvalidValue) {
    S.set(1, 1, 5);
    EXPECT_THROW(S.set(2, 2, 5), std::logic_error);
    EXPECT_THROW(S.set(1, 6, 5), std::logic_error);
    EXPECT_THROW(S.set(8, 1, 5), std::logic_error);
}

TEST_F(SudokuTest, CopySet) {
    Sudoku S1(S, 1, 1, 5);
    EXPECT_EQ(5, S1.get(1, 1));
    EXPECT_EQ(0, S1.get(0, 2));
}
