// Tests for iterator range sort - bugs detected
#include "06_insertion_sort.h"
#include <iterator>
#include <iostream>
#include <vector>

template <typename Container>
bool test(const Container& C, size_t from, size_t to)
{
    bool all_good = true;
    for (size_t i = from + 1; i < to; ++i) {
        if (C[i-1] > C[i]) {
            all_good = false;
            std::cout << "Bad sort: "
                "C[" << i-1 << "](" << C[i-1] << ") > "
                "C[" << i << "](" << C[i] << ")" << std::endl;
        }
    }
    return all_good;
}

template <typename Container>
bool sort_and_test(Container& C, size_t from, size_t to)
{
    sort(C.begin() + from, C.begin() + to);
    return test(C, from, to);
}
template <class T, size_t N>
bool sort_and_test(T (&C)[N], size_t from, size_t to)
{
    sort(&C[from], &C[to]);
    return test(C, from, to);
}

int main() {
    {
        int C[] {2, 8, 1, 4};
        sort_and_test(C, 0, std::size(C));
    }
    {
        std::vector<int> C{2, 8, 1, 4};
        sort_and_test(C, 0, std::size(C));
    }
    {
        std::vector<int> C{2};
        sort_and_test(C, 0, std::size(C));
    }
    {
        std::vector<int> C{};
        sort_and_test(C, 0, std::size(C));
    }
}
