// 01 with the implementation.
#ifndef SUDOKU_H_
#define SUDOKU_H_
#include <cstdlib>

class Sudoku {
    public:
    // Initialize empty puzzle.
    Sudoku();
    // Return the value from the specified cell, or 0 if the cell is not initialized.
    // Indices i and j must be 0 <= i,j < 9, otherwise std::logic_error is thrown
    unsigned char get(size_t i, size_t j) const;
    // Assign the cell value. 
    // Indices i and j must be 0 <= i,j < 9, otherwise std::logic_error is thrown
    // Exception std::logic_error is thrown if the value is already assigned.
    void set(size_t i, size_t j, unsigned char value);
    // Disable operators we don't need.
    Sudoku(const Sudoku& rhs) = delete;
    Sudoku(Sudoku&&) = delete;
    Sudoku& operator=(const Sudoku&) = delete;
    Sudoku& operator=(Sudoku&&) = delete;
    private:
    unsigned char cells[9][9];
};
#endif // SUDOKU_H_
