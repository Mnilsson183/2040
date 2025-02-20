#include "sort.hpp"

#include <iostream>

void merge(std::vector<int>& B, std::vector<int>& C, std::vector<int>& A) {

    const int p = B.size();
    const int q = C.size();

    int i = 0;
    int j = 0;
    int k = 0;

    while(i < p && j < q) {
        if (B[i] <= C[j]) {
            A[k] = B[i];
            ++i;
        } else {
            A[k] = C[j];
            ++j;
        }
        ++k;
    }

    if (i == p) {
        for (int l = j; l < q; l++) {
            A[k] = C[l];
            ++k;
        }
    } else {
        for (int l = i; l < p; l++) {
            A[k] = B[l];
            ++k;
        }
    }
}

void merge_sort(std::vector<int>& A) {
    const int n = A.size();
    if (n > 1) {
        std::vector<int> B;
        std::vector<int> C;

        for (int i = 0; i < n / 2; i++) {
            B.push_back(A[i]);
        }

        for (int i = n / 2; i < n; i++) {
            C.push_back(A[i]);
        }

        merge_sort(B);
        merge_sort(C);
        merge(B, C, A);
    }
}
