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
        static void private_quick_sort(std::vector<int64_t>& A, const size_t low, const size_t high);
        static size_t HoarePartition(std::vector<int64_t>& A, const size_t low, const size_t high);
        static size_t LomutoPartition(std::vector<int64_t>& A, const size_t low, const size_t high);
        static void merge(const std::vector<int64_t>& B, const std::vector<int64_t>& C, std::vector<int64_t>& A);
};

#endif