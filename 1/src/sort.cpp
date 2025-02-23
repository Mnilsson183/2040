// COPYRIGHT 2025 MORGAN NILSSON ALL RIGHTS RESERVED

#include <vector>
#include <utility>
#include <iostream>
#include <cstdint>

#include "sort.hpp"

/**
 * @brief Sorts a vector of integers using the bubble sort algorithm.
 * 
 * CS2040
 * @author Morgan Nilsson
 * @date 2025-01-01
 * 
 * @param A A reference to the vector of integers to be sorted.
 */
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

/**
 * @brief Sorts a vector of integers using the insertion sort algorithm.
 * 
 * CS2040
 * @author Morgan Nilsson
 * @date 2025-01-01
 * 
 * @param A A reference to the vector of integers to be sorted.
 */
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

/**
 * @brief Sorts a vector of integers using the selection sort algorithm.
 * 
 * CS2040
 * @author Morgan Nilsson
 * @date 2025-01-01
 * 
 * @param A A reference to the vector of integers to be sorted.
 */
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

/**
 * @brief Merges two sorted vectors into a single sorted vector.
 * 
 * CS2040
 * @author Morgan Nilsson
 * @date 2025-01-01
 * 
 * @param B The first sorted vector.
 * @param C The second sorted vector.
 * @param A The vector to store the merged sorted vectors.
 */
void Sort::merge(const std::vector<int64_t>& B, const std::vector<int64_t>& C, std::vector<int64_t>& A) {

    const size_t p = B.size();
    const size_t q = C.size();

    A.resize(p + q);

    uint64_t i = 0;
    uint64_t j = 0;
    uint64_t k = 0;

    while(i < p && j < q) {

        if (B[i] <= C[j]) A[k++] = B[i++];

        else A[k++] = C[j++];

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

/**
 * @brief Sorts a vector of integers using the merge sort algorithm.
 * 
 * CS2040
 * @author Morgan Nilsson
 * @date 2025-01-01
 * 
 * @param A A reference to the vector of integers to be sorted.
 */
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

/**
 * @brief Finds the median of three elements in a vector.
 * 
 * CS2040
 * @author Morgan Nilsson
 * @date 2025-01-01
 * 
 * @param A The vector of integers to find the median of.
 * @param low The starting index of the portion of the vector to find the median of.
 * @param high The ending index of the portion of the vector to find the median of.
 * @return size_t The index of the median element.
 */
size_t Sort::median_of_three(std::vector<int64_t>& A, size_t low, size_t high) {

    size_t mid = low + (high - low) / 2;

    if (A[low] > A[mid]) std::swap(A[low], A[mid]);

    if (A[low] > A[high]) std::swap(A[low], A[high]);

    if (A[mid] > A[high]) std::swap(A[mid], A[high]);

    return mid;

}

/**
 * @brief Partitions the given vector using Hoare's partitioning scheme with median of three partitioning.
 *
 * CS2040
 * @author Morgan Nilsson
 * @date 2025-01-01
 *
 * @param A The vector of integers to be partitioned.
 * @param low The starting index of the portion of the vector to be partitioned.
 * @param high The ending index of the portion of the vector to be partitioned.
 * @return The index of the pivot element after partitioning.
 */
size_t Sort::HoarePartition(std::vector<int64_t>& A, const size_t low, const size_t high) {

    const int64_t p = A.at(median_of_three(A, low, high));
    size_t i = low - 1;
    size_t j = high + 1;

    while (1) {

        do {
            ++i;
        } while(A[i] < p);

        do {
            --j;
        } while(A[j] > p);

        if (i >= j) return j;

        std::swap(A[i], A[j]);
    
    }

}

/**
 * @brief Performs a quick sort on a subarray of integers.
 * 
 * CS2040
 * @author Morgan Nilsson
 * @date 2025-01-01
 * 
 * @param A The vector of integers to be sorted.
 * @param low The starting index of the subarray to be sorted.
 * @param high The ending index of the subarray to be sorted.
 */
void Sort::private_quick_sort(std::vector<int64_t>& A, const size_t low, const size_t high) {

    if (low < high) {

        const size_t s = HoarePartition(A, low, high);
        private_quick_sort(A, low, s);
        private_quick_sort(A, s + 1, high);

    }
}


/**
 * @brief Sorts a vector of integers using the Quick Sort algorithm.
 * 
 * @note This function is a wrapper for the private_quick_sort function.
 * 
 * CS2040
 * @author Morgan Nilsson
 * @date 2025-01-01
 * 
 * @param A A reference to a vector of int64_t integers to be sorted.
 */
void Sort::quick_sort(std::vector<int64_t>& A) {

    private_quick_sort(A, 0, A.size() - 1);

}


/**
 * @brief Generates a random array of integers.
 * 
 * CS2040
 * @author Morgan Nilsson
 * @date 2025-01-01
 * 
 * @param size The number of random integers to generate.
 * @param v The vector to be filled with random integers.
 */
void Sort::generate_random_array(const size_t size, std::vector<int64_t>& v) {

    for (size_t i = 0; i < size; i++) {

        v.push_back(rand() % size);

    }

}

/**
 * @brief Generates an ordered array of integers.
 * 
 * CS2040
 * @author Morgan Nilsson
 * @date 2025-01-01
 * 
 * @param size The number of elements to generate.
 * @param v The vector to be filled with ordered integers.
 */
void Sort::generate_ordered_array(const size_t size, std::vector<int64_t>& v) {

    for (size_t i = 0; i < size; i++) {

        v.push_back(i);

    }

}

/**
 * @brief Generates a reverse sorted array of integers.
 * 
 * CS2040
 * @author Morgan Nilsson
 * @date 2025-01-01
 * 
 * @param size The number of elements to generate in the array.
 * @param v The vector to be filled with reverse ordered integers.
 */
void Sort::generate_reverse_array(const size_t size, std::vector<int64_t>& v) {

    for (int64_t i = size; i > 0; i--) {

        v.push_back(i);

    }

}

/**
 * @brief Verifies if a given vector of integers is sorted in non-decreasing order.
 * 
 * CS2040
 * @author Morgan Nilsson
 * @date 2025-01-01
 * 
 * @param v The vector of integers to be checked.
 * @return int Returns 1 if the vector is sorted in non-decreasing order, otherwise returns 0.
 */
int Sort::verify_sorted(const std::vector<int64_t>& v) {

    for (size_t i = 0; i < v.size() - 1; i++) {

        if (v.at(i) > v.at(i + 1)) {

            return 0;

        }

    }

    return 1;

}
