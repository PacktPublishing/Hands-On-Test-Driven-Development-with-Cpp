// Same as 02 but with custom checked container
#include "02_insertion_sort.h"
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
    sort(C, from, to);
    return test(C, from, to);
}

class checked_array {
    std::vector<int> v_;
    void check_index(size_t i) const {
        if (i >= v_.size()) {
            std::cout << "Invalid index " << i << ", valid range: [0, " << v_.size() << ")" << std::endl;
            abort();
        }
    }
    public:
    explicit checked_array(std::initializer_list<int> l) : v_(l) {}
    int& operator[](size_t i) { check_index(i); return v_[i]; }
    const int& operator[](size_t i) const { check_index(i); return v_[i]; }
    size_t size() const { return v_.size(); }
};

int main() {
    {
        int C[] {2, 8, 1, 4};
        sort_and_test(C, 0, std::size(C));
    }
    {
        checked_array C{2, 8, 1, 4};
        sort_and_test(C, 0, std::size(C));
    }
}
