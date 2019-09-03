#include "11_sudoku.h"
#include "11_sudoku.C"

#include <sstream>
#include <iostream>

#include <gtest/gtest.h>

class SudokuTest : public ::testing::Test {
    public:
    Sudoku S;
};

TEST_F(SudokuTest, Construct) {
    EXPECT_EQ(Sudoku::PARTIAL, S.verify());
    EXPECT_EQ(0, S.get(0, 0));
    EXPECT_EQ(0, S.get(8, 8));
    EXPECT_EQ(Sudoku::PARTIAL, S.verify());
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

TEST_F(SudokuTest, Output) {
    S.set(2, 1, 5);
    S.set(2, 2, 7);
    std::stringstream s;
    s << S;
    EXPECT_EQ(".........\n.........\n.57......\n.........\n.........\n.........\n.........\n.........\n.........\n", s.str());
}

TEST_F(SudokuTest, Input) {
    {
        std::stringstream s;
        s << "123456789\n456789123\n789123456\n234567891\n567891234\n891234567\n345678912\n678912345\n912345678\n";
        s >> S;
    }
    EXPECT_EQ(1, S.get(0, 0));
    EXPECT_EQ(2, S.get(0, 1));
    EXPECT_EQ(9, S.get(8, 0));
    EXPECT_EQ(8, S.get(8, 8));
    {
        std::stringstream s;
        s << S;
        EXPECT_EQ("123456789\n456789123\n789123456\n234567891\n567891234\n891234567\n345678912\n678912345\n912345678\n", s.str());
    }
}

TEST_F(SudokuTest, Solve) {
    {
        std::stringstream s;
        s << "123456789\n456789123\n789123456\n234567891\n567891234\n891234567\n345678912\n678912345\n91234567.\n";
        s >> S;
    }
    std::optional<Sudoku> res(solve(S));
    ASSERT_TRUE(res);
    Sudoku S1(*res);
    {
        std::stringstream s;
        s << S1;
        EXPECT_EQ("123456789\n456789123\n789123456\n234567891\n567891234\n891234567\n345678912\n678912345\n912345678\n", s.str());
    }
    EXPECT_EQ(Sudoku::VALID, S1.verify());
}

TEST_F(SudokuTest, NoSolution) {
    {
        std::stringstream s;
        s << "123456789\n456789123\n789123456\n234567891\n567891234\n891234567\n345678912\n67.912348\n91234567.\n";
        s >> S;
    }
    EXPECT_EQ(Sudoku::PARTIAL, S.verify());
    std::optional<Sudoku> res(solve(S));
    EXPECT_FALSE(res);
}
