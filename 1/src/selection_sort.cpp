#include "sort.hpp"

void selection_sort(std::vector<int>& A) {
    // + 1 to match to textbook
    int n = A.size() + 1;
    for (int i = 0; i < n - 2; i++) {
        int min = i;
        for (int j = i + 1; j < n - 1; j++) {
            if (A[j] < A[min]) min = j;
        }
        std::swap(A[i], A[min]);
    }
}