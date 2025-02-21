// COPYRIGHT 2025 MORGAN NILSSON ALL RIGHTS RESERVED

#ifndef SORT_HPP
#define SORT_HPP

#include <vector>

class Sort {
    public:
        static void bubble_sort(std::vector<int64_t>& A);
        static void insertion_sort(std::vector<int64_t>& A);
        static void selection_sort(std::vector<int64_t>& A);
        static void merge_sort(std::vector<int64_t>& A);
        static void quick_sort(std::vector<int64_t>& A);
    private:
        static void private_quick_sort(std::vector<int64_t>& A, const unsigned int low, const unsigned int high);
        static unsigned int HoarePartition(std::vector<int64_t>& A, const unsigned int low, const unsigned int high);
        static void merge(std::vector<int64_t>& B, std::vector<int64_t>& C, std::vector<int64_t>& A);
};

#endif