// Handle empty container correctly
#include <cstddef>

template <typename Container>
void sort(Container& C, size_t from, size_t to)
{
    if (from == to) return;
    for (size_t i = from + 1; i != to; ++i) {
        if (C[i] < C[i - 1]) {
            auto tmp = C[i];
            size_t j = i;
            do {
                C[j] = C[j - 1];
            } while ((--j > from) && (tmp < C[j - 1]));
            C[j] = tmp;
        }
    }
}
