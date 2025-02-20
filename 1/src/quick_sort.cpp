#include "sort.hpp"

#include <iostream>

int HoarePartition(std::vector<int>& A, int low, int high) {
    int p = A[low];
    int i = low;
    int j = high + 1;
    do {
        do {
            ++i;
        } while(i < high && A[i] < p);

        do {
            --j;
        } while(j > low && A[j] > p);

        std::swap(A[i], A[j]);

    } while (i < j);
    std::swap(A[i], A[j]);
    std::swap(A[low], A[j]);
    return j;
}

void private_quick_sort(std::vector<int>& A, int low, int high) {

    if (low < high) {
        int s = HoarePartition(A, low, high);
        private_quick_sort(A, low, s - 1);
        private_quick_sort(A, s + 1, high);
    }
}

void quick_sort(std::vector<int>& A) {
    private_quick_sort(A, 0, A.size() - 1);
}