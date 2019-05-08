// 07 using only bidirectional iterators - refactoring
#include <cstddef>

template <typename Iterator>
void sort(Iterator from, Iterator to)
{
    if (from == to) return;
    for (Iterator i = from, i1 = i++; i != to; i1 = i, ++i) {
        if (*i < *i1) {
            auto tmp = *i;
            Iterator j1 = i, j = j1--;
            do {
                *j = *j1;
            } while ((--j != from) && (tmp < *(--j1)));
            *j = tmp;
        }
    }
}
