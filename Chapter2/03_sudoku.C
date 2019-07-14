#include "03_sudoku.h"

#include <stdexcept>

Sudoku::Sudoku()
{
    for (size_t i = 0; i < 9; ++i) {
        for (size_t j = 0; j < 9; ++j) {
            cells[i][j] = 0;
        }
    }
}

unsigned char Sudoku::get(size_t i, size_t j) const
{
    if (i >= 9 || j >= 9) throw std::logic_error("Invalid index");
    return cells[i][j];
}

unsigned short Sudoku::mask(unsigned char value) {
    return value;
}

unsigned short Sudoku::get_mask(size_t i, size_t j) const
{
    return i + j;
}

void Sudoku::set(size_t i, size_t j, unsigned char value)
{
    if (i >= 9 || j >= 9) throw std::logic_error("Invalid index");
    if (cells[i][j] != 0) throw std::logic_error("Reinitialization");
    if (value == 0 || value > 9) throw std::logic_error("Invalid value");
    cells[i][j] = value;
}
