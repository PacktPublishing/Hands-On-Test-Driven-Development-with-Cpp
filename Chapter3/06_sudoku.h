// 05 with a copy/set constructor.
#ifndef SUDOKU_H_
#define SUDOKU_H_
#include <cstdlib>

class Sudoku {
    public:
    // Initialize empty puzzle.
    Sudoku();
    // Create a copy of the puzzle, with an additional cell initialized. See
    // set() for restrictions on the position and value.
    Sudoku(const Sudoku& S, size_t i, size_t j, unsigned char value);
    // Return the value from the specified cell, or 0 if the cell is not initialized.
    // Indices i and j must be 0 <= i,j < 9, otherwise std::logic_error is thrown
    unsigned char get(size_t i, size_t j) const;
    // Assign the cell value. 
    // Indices i and j must be 0 <= i,j < 9, otherwise std::logic_error is thrown
    // Exception std::logic_error is thrown if the value is already assigned.
    // Exception std::logic_error is thrown if the value is not valid for this
    // cell because it is already used in the same row, column, or square.
    void set(size_t i, size_t j, unsigned char value);
    // Return the mask for all possible values for an uninitialized cell. 0 is
    // returned if no values are possible. This method should not be called if
    // the cell is initialized, result is undefined.
    unsigned short get_mask(size_t i, size_t j) const;
    // Return the mask for the value (0 < value <= 9) or the mask for all
    // values (value == 0).
    static unsigned short mask(unsigned char value);
    // Disable operators we don't need.
    Sudoku(const Sudoku& rhs) = delete;
    Sudoku(Sudoku&&) = delete;
    Sudoku& operator=(const Sudoku&) = delete;
    Sudoku& operator=(Sudoku&&) = delete;
    private:
    unsigned char cells[9][9];
};
#endif // SUDOKU_H_
