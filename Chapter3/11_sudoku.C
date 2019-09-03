#include "11_sudoku.h"

#include <stdexcept>
#include <cstring>
#include <istream>
#include <ostream>

Sudoku::Sudoku()
{
    for (size_t i = 0; i < 9; ++i) {
        for (size_t j = 0; j < 9; ++j) {
            cells[i][j] = 0;
        }
    }
}

Sudoku::Sudoku(const Sudoku& S, size_t i, size_t j, unsigned char value)
    : Sudoku(S)
{
    set(i, j, value);
}

Sudoku::state_t Sudoku::verify() const
{
    return VALID;
}

unsigned char Sudoku::get(size_t i, size_t j) const
{
    if (i >= 9 || j >= 9) throw std::logic_error("Invalid index");
    return cells[i][j];
}

namespace {
    // masks[i] = 1 << (i - 1), element 0 is not used as a value mask but is
    // the combination of all mask bits.
    const unsigned short masks[] = { 0x1FF, 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100 };
}

unsigned short Sudoku::mask(unsigned char value) {
    return masks[value];
}

unsigned short Sudoku::get_mask(size_t i, size_t j) const
{
    if (i >= 9 || j >= 9) throw std::logic_error("Invalid index");
    unsigned short mask = masks[0];
    // Check the row and the column.
    for (size_t k = 0; k < 9; ++k) {
        if (cells[k][j] != 0) mask &= ~masks[cells[k][j]];
        if (cells[i][k] != 0) mask &= ~masks[cells[i][k]];
    }
    // Check the square.
    for (size_t i0 = (i/3)*3, j0 = (j/3)*3, ii = 0; ii < 3; ++ii) {
        for (size_t jj = 0; jj < 3; ++jj) {
            if (cells[i0 + ii][j0 + jj] != 0) mask &= ~masks[cells[i0 + ii][j0 + jj]];
        }
    }
    return mask;
}

void Sudoku::set(size_t i, size_t j, unsigned char value)
{
    if (i >= 9 || j >= 9) throw std::logic_error("Invalid index");
    if (cells[i][j] != 0) throw std::logic_error("Reinitialization");
    if (value == 0 || value > 9) throw std::logic_error("Invalid value");
    if ((get_mask(i, j) & masks[value]) == 0) throw std::logic_error("Forbidden value");
    cells[i][j] = value;
}

std::ostream& operator<<(std::ostream& out, const Sudoku& S)
{
    for (size_t i = 0; i < 9; ++i) {
        for (size_t j = 0; j < 9; ++j) {
            if (S.cells[i][j]) out << static_cast<int>(S.cells[i][j]);
            else out << '.';
        }
        out << std::endl;
    }
    return out;
}

std::istream& operator>>(std::istream& in, Sudoku& S)
{
    for (size_t i = 0; i < 9; ++i) {
        for (size_t j = 0; j < 9; ++j) {
            S.cells[i][j] = 0;
        }
    }
    for (size_t i = 0; i < 9; ++i) {
        for (size_t j = 0; j < 9; ++j) {
            char c;
            in >> c;
            if (c != '.') S.set(i, j, c - '0');
        }
    }
    return in;
}

std::optional<Sudoku> solve(const Sudoku& S)
{
    // Find the first cell that does not have a value.
    bool solved = true;
    for (size_t i = 0; i < 9; ++i) {
        for (size_t j = 0; j < 9; ++j) {
            if (S.get(i, j)) continue;                                  // Has value
            solved = false;
            // Try all possible values for this cell.
            unsigned short mask = S.get_mask(i, j);
            for (unsigned char value = 1; value <= 9; ++value) {
                if ((mask & Sudoku::mask(value)) == 0) continue;        // Invalid value
                Sudoku SS(S, i, j, value);
                std::optional<Sudoku> res = solve(SS);
                if (res) {                                              // Solution found
                    return res;
                }
            }
            // There is no value in this cell that leads to a solution.
            return std::optional<Sudoku>();
        }
    }
    if (solved) {                                                       // S is filled
        return S;
    } else {                                                            // No solution
        return std::optional<Sudoku>();
    }
}
