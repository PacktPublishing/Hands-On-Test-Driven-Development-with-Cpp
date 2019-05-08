// Test for the container sort
#include "00_insertion_sort.h"
#include <iterator>
#include <iostream>

int main() {
    int C[] {2, 8, 1, 4};
    sort(C, 0, std::size(C));
    for (size_t i = 1; i != std::size(C); ++i) {
        if (C[i-1] > C[i]) {
            std::cout << "Bad sort: "
                "C[" << i-1 << "](" << C[i-1] << ") > "
                "C[" << i << "](" << C[i] << ")" << std::endl;
        }
    }
}
