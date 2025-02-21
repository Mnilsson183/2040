#include "sort.hpp"

#include <chrono>
#include <iostream>

#include <array>

#define DEBUG 0
#define VERIFY 0

const std::array<int, 3> array_sizes = {10, 100, 1000};
//const std::array<int, 7> array_sizes = {10, 100, 1000, 10000, 100000, 1000000, 10000000};
#define ARRAY_NUMBER_OF_SIZES array_sizes.size()

const std::array<std::string, 5> algorithm_names = {"Bubble Sort", "Insertion Sort", "Selection Sort", "Merge Sort", "Quick Sort"};
#define NUMBER_OF_ALGORITHMS algorithm_names.size()

const std::array<std::string, 3> generation_names = {"Random", "Ordered", "Reverse"};
#define NUMBER_OF_ORDERINGS generation_names.size()

#define ARRAY_SAMPLE_SIZE 10

void generate_random_array(const int size, std::vector<int>& v) {
    for (int i = 0; i < size; i++) {
        v.push_back(rand() % size);
    }
}

void generate_ordered_array(const int size, std::vector<int>& v) {
    for (int i = 0; i < size; i++) {
        v.push_back(i);
    }
}

void generate_reverse_array(const int size, std::vector<int>& v) {
    for (int i = size; i > 0; i--) {
        v.push_back(i);
    }
}

int verify_sorted(const std::vector<int>& v) {
    for (int i = 0; i < v.size() - 1; i++) {
        if (v[i] > v[i + 1]) {
            return 0;
        }
    }
    return 1;
}

int main(void) {

    std::chrono::milliseconds elapsed_times[NUMBER_OF_ALGORITHMS][ARRAY_NUMBER_OF_SIZES][NUMBER_OF_ORDERINGS][ARRAY_SAMPLE_SIZE];

    std::vector<int> src_arrays[ARRAY_SAMPLE_SIZE];
    std::vector<int> arrays[ARRAY_SAMPLE_SIZE];

    // array of the sorting functions
    void (*sorting_functions[NUMBER_OF_ALGORITHMS])(std::vector<int>&) = {bubble_sort, insertion_sort, selection_sort, merge_sort, quick_sort};
    // array of generating data functions
    void (*generating_functions[3])(const int, std::vector<int>&) = {generate_random_array, generate_ordered_array, generate_reverse_array};


    for (int arr_size = 0; arr_size < ARRAY_NUMBER_OF_SIZES; arr_size++) {
        int size = array_sizes[arr_size];

        #if DEBUG
        std::cout << "Array size: " << size << std::endl;
        #endif

        for (int ordering = 0; ordering < NUMBER_OF_ORDERINGS; ordering++) {

            // generate arrays
            for (int sample = 0; sample < ARRAY_SAMPLE_SIZE; sample++) {
                src_arrays[sample].clear();
                (generating_functions[ordering])(size, src_arrays[sample]);
            }

            // sort arrays
            for (int sample = 0; sample < ARRAY_SAMPLE_SIZE; sample++) {

                for (int algorithm = 0; algorithm < NUMBER_OF_ALGORITHMS; algorithm++) {
                    // if using selection insertion or bubble and array > 100 000 skip
                    if (algorithm < 3 && size > 100000) {
                        elapsed_times[algorithm][arr_size][ordering][sample] = std::chrono::milliseconds(-1);
                        continue;
                    }
                    // if using merge or quick and array < 100 000 skip
                    if (algorithm >= 3 && size < 100000) {
                        elapsed_times[algorithm][arr_size][ordering][sample] = std::chrono::milliseconds(-1);
                        continue;
                    }

                    if (algorithm)
                    // deep copy the array
                    arrays[sample].clear();
                    for (int i = 0; i < size; i++) {
                        arrays[sample].push_back(src_arrays[sample][i]);
                    }

                    auto start = std::chrono::high_resolution_clock::now();
                    (sorting_functions[algorithm])(arrays[sample]);
                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                    elapsed_times[algorithm][arr_size][ordering][sample] = duration;

                    #if VERIFY
                    if (!verify_sorted(arrays[sample])) {
                        std::cout << "Array not sorted! " << algorithm_names[algorithm] << std::endl;
                    }
                    #endif
                }

            }
        }
    }

//std::chrono::milliseconds elapsed_times[NUMBER_OF_ALGORITHMS][ARRAY_NUMBER_OF_SIZES][ARRAY_SAMPLE_SIZE];

    for (int algorithm = 0; algorithm < NUMBER_OF_ALGORITHMS; algorithm++) {
        std::cout << "Algorithm: " << algorithm_names[algorithm] << std::endl << std::endl;
        for (int arr_size = 0; arr_size < ARRAY_NUMBER_OF_SIZES; arr_size++) {
            std::cout << "Array size: " << array_sizes[arr_size] << std::endl;
            for (int ordering = 0; ordering < NUMBER_OF_ORDERINGS; ordering++) {
                std::cout << generation_names[ordering] << ": ";
                for (int sample = 0; sample < ARRAY_SAMPLE_SIZE; sample++) {
                    if (elapsed_times[algorithm][arr_size][ordering][sample].count() == -1) {
                        std::cout << "N/A";
                        if (sample != ARRAY_SAMPLE_SIZE - 1) {
                            std::cout << ", ";
                        }
                    } else {
                        std::cout << elapsed_times[algorithm][arr_size][ordering][sample].count() << "ms";
                        if (sample != ARRAY_SAMPLE_SIZE - 1) {
                            std::cout << ", ";
                        }
                    }
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }

    // print best times for each time highlight the best of each group
    for (int arr_size = 0; arr_size < ARRAY_NUMBER_OF_SIZES; arr_size++) {
        std::cout << "Array size: " << array_sizes[arr_size] << std::endl;
        for (int ordering = 0; ordering < NUMBER_OF_ORDERINGS; ordering++) {
            std::cout << "  " << generation_names[ordering] << ": ";

            std::chrono::milliseconds best_times[NUMBER_OF_ALGORITHMS];

            for (int sample = 0; sample < ARRAY_SAMPLE_SIZE; sample++) {
                for (int algorithm = 0; algorithm < NUMBER_OF_ALGORITHMS; algorithm++) {
                    if (sample == 0 || elapsed_times[algorithm][arr_size][ordering][sample] < best_times[algorithm]) {
                        best_times[algorithm] = elapsed_times[algorithm][arr_size][ordering][sample];
                    }
                }
            }


            for (int algorithm = 0; algorithm < NUMBER_OF_ALGORITHMS; algorithm++) {
                // calculate the min time of the best times
                std::chrono::milliseconds min_time = best_times[0];
                for (int i = 1; i < NUMBER_OF_ALGORITHMS; i++) {
                    if (best_times[i] < min_time && best_times[i].count() != -1) {
                        min_time = best_times[i];
                    }
                }

                if (best_times[algorithm].count() == -1) {
                    std::cout << "N/A";
                    if (algorithm != NUMBER_OF_ALGORITHMS - 1) {
                        std::cout << ", ";
                    }
                } else {
                    // print best time in red
                    if (best_times[algorithm] == min_time) {
                        std::cout << "\033[1;31m";
                    }
                    std::cout << best_times[algorithm].count() << "ms";

                    if (algorithm != NUMBER_OF_ALGORITHMS - 1) {
                        std::cout << ", ";
                    }

                    // clear color
                    std::cout << "\033[0m";
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}