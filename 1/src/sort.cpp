// COPYRIGHT 2025 MORGAN NILSSON ALL RIGHTS RESERVED

#include <vector>
#include <utility>

#include "sort.hpp"

void Sort::bubble_sort(std::vector<int64_t>& A) {

    const size_t size = A.size();

    for (size_t i = 0; i < size; i++) {

        for (size_t j = 0; j < size - i - 1; j++) {

            if (A[j] > A[j + 1]) {

                std::swap(A[j], A[j + 1]);

            }

        }
    }
}

void Sort::insertion_sort(std::vector<int64_t>& A) {

    const size_t n = A.size() + 1;

    for (size_t i = 1; i < n - 1; i++) {

        const int64_t v = A[i];

        int64_t j = i - 1;

        while(j >= 0 && A[j] > v) {

            A[j + 1] = A[j];
            --j;

        }
        A[j + 1] = v;

    }

}

void Sort::selection_sort(std::vector<int64_t>& A) {

    const size_t n = A.size() + 1;

    for (size_t i = 0; i < n - 2; i++) {

        int min = i;

        for (size_t j = i + 1; j < n - 1; j++) {

            if (A[j] < A[min]) min = j;
        }
        std::swap(A[i], A[min]);

    }

    return;
    
}

void Sort::merge(const std::vector<int64_t>& B, const std::vector<int64_t>& C, std::vector<int64_t>& A) {

    const size_t p = B.size();
    const size_t q = C.size();

    A.resize(p + q);

    uint64_t i = 0;
    uint64_t j = 0;
    uint64_t k = 0;

    while(i < p && j < q) {

        if (B[i] <= C[j])
            A[k++] = B[i++];

        else
            A[k++] = C[j++];
    }

    if (i == p) {

        for (uint64_t l = j; l < q; l++) {

            A[k++] = C[l];

        }

    } else {

        for (uint64_t l = i; l < p; l++) {

            A[k++] = B[l];

        }

    }

}

void Sort::merge_sort(std::vector<int64_t>& A) {

    size_t n = A.size();

    if (n > 1) {

        std::vector<int64_t> B;
        std::vector<int64_t> C;

        for (size_t i = 0; i < n / 2; i++) {
            B.push_back(A[i]);
        }

        for (size_t i = n / 2; i < n; i++) {
            C.push_back(A[i]);
        }

        merge_sort(B);
        merge_sort(C);
        merge(B, C, A);

    }

    return;
    
}

size_t Sort::HoarePartition(std::vector<int64_t>& A, const size_t low, const size_t high) {
    const int64_t p = A[low];
    size_t i = low;
    size_t j = high + 1;

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


void Sort::private_quick_sort(std::vector<int64_t>& A, const size_t low, const size_t high) {

    if (low < high) {

        const size_t s = HoarePartition(A, low, high);
        private_quick_sort(A, low, s - 1);
        private_quick_sort(A, s + 1, high);
    }
}


void Sort::quick_sort(std::vector<int64_t>& A) {

    private_quick_sort(A, 0, A.size() - 1);
    
}
