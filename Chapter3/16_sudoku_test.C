#include "16_sudoku.h"
#include "16_sudoku.C"

#include <sstream>
#include <iostream>
#include <ctime>

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
    SudokuSolver SS(S);
    std::optional<Sudoku> res(SS.solve());
    ASSERT_TRUE(res);
    Sudoku S1(*res);
    {
        std::stringstream s;
        s << S1;
        EXPECT_EQ("123456789\n456789123\n789123456\n234567891\n567891234\n891234567\n345678912\n678912345\n912345678\n", s.str());
    }
    EXPECT_EQ(Sudoku::VALID, S1.verify());
    SudokuSolver::complexity_t complexity = SS.complexity();
    EXPECT_EQ(1u, complexity.max_depth);
    EXPECT_EQ(2u, complexity.search_count);
    EXPECT_EQ(0u, complexity.backtrack_count);
}

TEST_F(SudokuTest, NoSolution) {
    {
        std::stringstream s;
        s << "123456789\n456789123\n789123456\n234567891\n567891234\n891234567\n345678912\n67.912348\n91234567.\n";
        s >> S;
    }
    EXPECT_EQ(Sudoku::PARTIAL, S.verify());
    SudokuSolver SS(S);
    std::optional<Sudoku> res(SS.solve());
    EXPECT_FALSE(res);
}

TEST_F(SudokuTest, SolveHard) {
    {
        std::stringstream s;
        s << "8........\n..36.....\n.7..9.2..\n.5...7...\n....457..\n...1...3.\n..1....68\n..85...1.\n.9....4..\n";
        s >> S;
    }
    SudokuSolver SS(S);
    std::optional<Sudoku> res(SS.solve());
    ASSERT_TRUE(res);
    Sudoku S1(*res);
    EXPECT_EQ(Sudoku::VALID, S1.verify());
    SudokuSolver::complexity_t complexity = SS.complexity();
    EXPECT_EQ(60u, complexity.max_depth);
    EXPECT_EQ(49559u, complexity.search_count);
    EXPECT_EQ(49498u, complexity.backtrack_count);
    EXPECT_EQ(49558u, complexity.cell_count);
}

TEST_F(SudokuTest, SolveHardTwice) {
    {
        std::stringstream s;
        s << "8........\n..36.....\n.7..9.2..\n.5...7...\n....457..\n...1...3.\n..1....68\n..85...1.\n.9....4..\n";
        s >> S;
    }
    SudokuSolver SS(S);
    std::clock_t d1, d2;
    {
        std::clock_t t0 = clock();
        std::optional<Sudoku> res(SS.solve());
        d1 = clock() - t0;
        ASSERT_TRUE(res);
        Sudoku S1(*res);
        EXPECT_EQ(Sudoku::VALID, S1.verify());
    }
    {
        std::clock_t t0 = clock();
        std::optional<Sudoku> res(SS.solve());
        d2 = clock() - t0;
        ASSERT_TRUE(res);
        Sudoku S1(*res);
        EXPECT_EQ(Sudoku::VALID, S1.verify());
    }
    EXPECT_LT(d2*100, d1);
}

TEST_F(SudokuTest, SolveEmpty) {
    {
        std::stringstream s;
        s << ".........\n.........\n.........\n.........\n.........\n.........\n.........\n.........\n.........\n";
        s >> S;
    }
    SudokuSolver SS(S);
    std::optional<Sudoku> res(SS.solve());
    ASSERT_TRUE(res);
    Sudoku S1(*res);
    EXPECT_EQ(Sudoku::VALID, S1.verify());
}

TEST_F(SudokuTest, SolveCount) {
    {
        std::stringstream s;
        s << "123456789\n456789123\n789123456\n234567891\n567891234\n891234567\n345678912\n678912345\n91234567.\n";
        s >> S;
    }
    SudokuSolver SS(S);
    EXPECT_EQ(1u, SS.solution_count());
}

TEST_F(SudokuTest, SolveCountSolved) {
    {
        std::stringstream s;
        s << "123456789\n456789123\n789123456\n234567891\n567891234\n891234567\n345678912\n678912345\n91234567.\n";
        s >> S;
    }
    SudokuSolver SS(S);
    EXPECT_EQ(1u, SS.solution_count());
    std::optional<Sudoku> res(SS.solve());
    ASSERT_TRUE(res);
    Sudoku S1(*res);
    {
        std::stringstream s;
        s << S1;
        EXPECT_EQ("123456789\n456789123\n789123456\n234567891\n567891234\n891234567\n345678912\n678912345\n912345678\n", s.str());
    }
    EXPECT_EQ(Sudoku::VALID, S1.verify());
}

TEST_F(SudokuTest, SolveCountHard) {
    {
        std::stringstream s;
        s << "8........\n..36.....\n.7..9.2..\n.5...7...\n....457..\n...1...3.\n..1....68\n..85...1.\n.9....4..\n";
        s >> S;
    }
    SudokuSolver SS(S);
    EXPECT_EQ(1u, SS.solution_count());
    {
        std::clock_t t0 = clock();
        std::optional<Sudoku> res(SS.solve());
        std::clock_t d = clock() - t0;
        ASSERT_TRUE(res);
        Sudoku S1(*res);
        EXPECT_EQ(Sudoku::VALID, S1.verify());
        EXPECT_LE(100u, d);     // Solution not cached, should be slow
    }
}

TEST_F(SudokuTest, SolveCountMany) {
    {
        std::stringstream s;
        s << "8........\n..36.....\n.7..9....\n.5...7...\n....457..\n...1...3.\n..1....68\n..85...1.\n.9....4..\n";
        s >> S;
    }
    SudokuSolver SS(S);
    EXPECT_NE(1u, SS.solution_count());
}

