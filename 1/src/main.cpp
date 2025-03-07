// COPYRIGHT 2025 MORGAN NILSSON ALL RIGHTS RESERVED

#include <chrono>
#include <iostream>

#include <array>
#include <vector>
#include <string>

#include "sort.hpp"

#define DEBUG 0
#define VERIFY 0

const std::array<size_t, 7> array_sizes = {10, 100, 1000, 10000, 100000, 1000000, 10000000};
#define ARRAY_NUMBER_OF_SIZES array_sizes.size()

const std::array<std::string, 5> algorithm_names = {"Bubble Sort", "Insertion Sort", "Selection Sort", "Merge Sort", "Quick Sort"};
#define NUMBER_OF_ALGORITHMS 5

const std::array<std::string, 3> generation_names = {"Random", "Ordered", "Reverse"};
#define NUMBER_OF_ORDERINGS 3

#define ARRAY_SAMPLE_SIZE 10

typedef std::array<std::chrono::milliseconds, ARRAY_SAMPLE_SIZE> sampleTimes_t;
typedef std::array<sampleTimes_t, NUMBER_OF_ORDERINGS> orderingTimes_t;
typedef std::array<orderingTimes_t, ARRAY_NUMBER_OF_SIZES> sizeTimes_t;
typedef std::array<sizeTimes_t, NUMBER_OF_ALGORITHMS> sortingTimes_t;


typedef void (*sorting_algorithm_fn_t)(std::vector<int64_t>&);
typedef void (*data_generation_fn_t)(const size_t, std::vector<int64_t>&);

// array of the sorting functions
const std::array<sorting_algorithm_fn_t, NUMBER_OF_ALGORITHMS> sorting_functions = {
    Sort::bubble_sort, Sort::insertion_sort, Sort::selection_sort, Sort::merge_sort, Sort::quick_sort};

// array of generating data functions
const std::array<data_generation_fn_t, NUMBER_OF_ORDERINGS> generating_functions = {
    Sort::generate_random_array, Sort::generate_ordered_array, Sort::generate_reverse_array};

/**
 * @brief Performs a deep copy of a vector.
 * 
 * CS2040
 * @author Morgan Nilsson
 * @date 2025-01-01
 * 
 * @param src The source
 * @param dest The destination
 */
void deep_copy_vector(const std::vector<int64_t>& src, std::vector<int64_t>& dest) {

    dest.clear();
    dest.reserve(src.size());

    for (size_t i = 0; i < src.size(); i++) {

        dest.push_back(src[i]);

    }

}

/**
 * @brief Measures the time taken by a sorting algorithm to sort a vector.
 * 
 * CS2040
 * @author Morgan Nilsson
 * @date 2025-01-01
 * 
 * @param sorting_algorithm A function pointer to the sorting algorithm to be used.
 * @param sortableVector A reference to the vector of integers to be sorted.
 * @return std::chrono::milliseconds The duration taken by the sorting algorithm to sort the vector in milliseconds.
 * 
 * @note If VERIFY is defined, the function will check if the vector is sorted after the sorting algorithm is run.
 *       If the vector is not sorted, it will print an error message.
 */
std::chrono::milliseconds run_sorting_algorithm(sorting_algorithm_fn_t sorting_algorithm, std::vector<int64_t>& sortableVector){

    auto start = std::chrono::high_resolution_clock::now();

    sorting_algorithm(sortableVector);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    #if VERIFY
    int sorted = Sort::verify_sorted(sortableVector);
    if (!sorted) {

        std::cout << "Array not sorted! " << std::endl;

    }
    #endif

    return duration;

}

void print_test_times(const sortingTimes_t times) {

    // for each algorithm
    for (int algorithm = 0; algorithm < NUMBER_OF_ALGORITHMS; algorithm++) {

        std::cout << "Algorithm: " << algorithm_names[algorithm] << std::endl << std::endl;

        // for each input size
        for (size_t arr_size = 0; arr_size < ARRAY_NUMBER_OF_SIZES; arr_size++) {

            std::cout << "Array size: " << array_sizes[arr_size] << std::endl;

            // for each ordering
            for (int ordering = 0; ordering < NUMBER_OF_ORDERINGS; ordering++) {

                std::cout << generation_names[ordering] << ": ";

                // for each sample
                for (int sample = 0; sample < ARRAY_SAMPLE_SIZE; sample++) {

                    if (times[algorithm][arr_size][ordering][sample].count() == -1) {

                        std::cout << "N/A";


                    } else {

                        std::cout << times[algorithm][arr_size][ordering][sample].count() << "ms";

                    }

                    if (sample != ARRAY_SAMPLE_SIZE - 1) {

                        std::cout << ", ";

                    }

                }

                std::cout << std::endl;

            }

            std::cout << std::endl;

        }

    }

    const unsigned int spacing = 8;

    // print best times for each array size and ordering
    for (size_t arr_size = 0; arr_size < ARRAY_NUMBER_OF_SIZES; arr_size++) {

        std::cout << "Array size: " << array_sizes[arr_size] << std::endl;

        std::cout << "            ";
        for (int i = 0; i < NUMBER_OF_ALGORITHMS; i++) {

            std::cout << algorithm_names[i][0];
            for (unsigned int j = 0; j < spacing; j++) {

                std::cout << " ";

            }

        }
        std::cout << std::endl;

        for (int ordering = 0; ordering < NUMBER_OF_ORDERINGS; ordering++) {

            std::cout << "  " << generation_names[ordering] << ":";

            // align the first times with the algorithm names
            const int spacing_start = 9 - generation_names[ordering].length();
            for (int i = 0; i < spacing_start; i++) {

                std::cout << " ";

            }

            // get the best time out of all samples
            std::chrono::milliseconds best_times[NUMBER_OF_ALGORITHMS];

            for (int algorithm = 0; algorithm < NUMBER_OF_ALGORITHMS; algorithm++) {

                best_times[algorithm] = times[algorithm][arr_size][ordering][0];

                for (int sample = 1; sample < ARRAY_SAMPLE_SIZE; sample++) {

                    if (times[algorithm][arr_size][ordering][sample] < best_times[algorithm] && times[algorithm][arr_size][ordering][sample].count() != -1) {

                        best_times[algorithm] = times[algorithm][arr_size][ordering][sample];

                    }

                }

            }

            // identify best times per size and ordering
            for (int algorithm = 0; algorithm < NUMBER_OF_ALGORITHMS; algorithm++) {

                std::chrono::milliseconds min_time = std::chrono::milliseconds(INT64_MAX);

                for (int i = 0; i < NUMBER_OF_ALGORITHMS; i++) {

                    if (best_times[i] < min_time && best_times[i].count() != -1) {

                        min_time = best_times[i];

                    }

                }

                int spaces_to_print = spacing + 1;

                if (best_times[algorithm].count() == -1) {

                    std::cout << "N/A";
                    spaces_to_print -= 3;
                    if (algorithm != NUMBER_OF_ALGORITHMS - 1) {

                        std::cout << ", ";
                        spaces_to_print -= 2;

                    }

                } else {

                    // print best time in red
                    if (best_times[algorithm] == min_time) {

                        std::cout << "\033[1;31m";

                    }
                    std::cout << best_times[algorithm].count() << "ms";

                    spaces_to_print -= std::to_string(best_times[algorithm].count()).length() + 2;

                    if (algorithm != NUMBER_OF_ALGORITHMS - 1) {

                        std::cout << ", ";
                        
                        spaces_to_print -= 2;

                    }

                    // clear color
                    std::cout << "\033[0m";

                }

                // match the spacing
                for (int i = 0; i < spaces_to_print; i++) {
                    std::cout << " ";
                }

            }

            std::cout << std::endl;

        }

        std::cout << std::endl;

    }

}

/**
 * @brief Main function to test sorting algorithms on various array sizes and orderings.
 * 
 * CS2040
 * @author Morgan Nilsson
 * @date 2025-01-01
 *
 * @return int Returns 0 upon successful completion.
 */
int main(void) {

    sortingTimes_t elapsed_times;

    // constant arrays that hold the generated data
    std::array<std::vector<int64_t>, ARRAY_SAMPLE_SIZE> src_arrays;

    // reused arrays that are sorted
    std::array<std::vector<int64_t>, ARRAY_SAMPLE_SIZE> arrays;

    // for each size of array to test
    for (size_t arr_size = 0; arr_size < ARRAY_NUMBER_OF_SIZES; arr_size++) {

        size_t size = array_sizes.at(arr_size);

        // for every ordering type
        for (int ordering = 0; ordering < NUMBER_OF_ORDERINGS; ordering++) {

            // generate arrays
            for (int sample = 0; sample < ARRAY_SAMPLE_SIZE; sample++) {

                src_arrays.at(sample).clear();
                (generating_functions.at(ordering))(size, src_arrays.at(sample));
            }

            // for each sample
            for (int sample = 0; sample < ARRAY_SAMPLE_SIZE; sample++) {

                // for each algorithm
                for (int algorithm = 0; algorithm < NUMBER_OF_ALGORITHMS; algorithm++) {

                    #if DEBUG
                    std::cout << "Numbers size " << src_arrays.at(sample).size() << " Ordering type: " << generation_names[ordering] << " sample: " << sample << " algorithm: " << algorithm_names[algorithm];
                    std::flush(std::cout);
                    #endif

                    // if using selection insertion or bubble and array > 100 000 skip
                    if (algorithm < 3 && size > 100000) {

                        elapsed_times.at(algorithm).at(arr_size).at(ordering).at(sample) = std::chrono::milliseconds(-1);

                        #if DEBUG
                        std::cout << " skipped" << std::endl;
                        #endif

                        continue;
                    }

                    deep_copy_vector(src_arrays.at(sample), arrays.at(sample));

                    elapsed_times.at(algorithm).at(arr_size).at(ordering).at(sample) = run_sorting_algorithm(sorting_functions.at(algorithm), arrays.at(sample));

                    #if DEBUG
                    std::cout << " done" << std::endl;
                    #endif
                }
            }
        }
    }

    print_test_times(elapsed_times);

    return 0;
}
