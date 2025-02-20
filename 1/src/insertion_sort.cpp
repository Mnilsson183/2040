#include "sort.hpp"

void insertion_sort(std::vector<int>& A) {
    // + 1 to match to textbook
    int n = A.size() + 1;
    for (int i = 1; i < n - 1; i++) {
        int v = A[i];
        int j = i - 1;
        while(j >= 0 && A[j] > v) {
            A[j + 1] = A[j];
            --j;
        }
        A[j + 1] = v;
    }
}