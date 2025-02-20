#include "sort.hpp"

#include <iostream>

void bubble_sort(std::vector<int>& v) {
    int size = v.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
            }
        }
    }
}