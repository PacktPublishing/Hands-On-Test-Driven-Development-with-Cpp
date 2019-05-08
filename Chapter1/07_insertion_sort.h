// 06 with a bug fix
#include <cstddef>

template <typename Iterator>
void sort(Iterator from, Iterator to)
{
    if (from == to) return;
    for (Iterator i = from + 1; i != to; ++i) {
        if (*i < *(i - 1)) {
            auto tmp = *i;
            Iterator j = i;
            do {
                *j = *(j - 1);
            } while ((--j != from) && (tmp < *(j - 1)));
            *j = tmp;
        }
    }
}
