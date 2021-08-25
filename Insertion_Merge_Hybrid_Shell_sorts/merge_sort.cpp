#include "project1.h"
#include "helper_functions.h"

//Using pseudo code in lecture slide
void mergeSort (std::vector<int>& nums, int length);

uint64_t merge_sort(std::vector<int>& nums) {
    uint64_t  elapsed_time = 0;
    auto start_time = std::chrono::steady_clock::now();

    int length = nums.size();
    mergeSort(nums, length);

    auto end_time = std::chrono::steady_clock::now();
    elapsed_time = std::chrono::nanoseconds(end_time - start_time).count();
    return elapsed_time;
}

void mergeSort (std::vector<int>& nums, int length) {
    if (length > 1) {
        std::vector<int> v1(nums.begin(), nums.begin() + length/2);//firs hafl
        std::vector<int> v2 (nums.begin() + length/2, nums.end());//second half 
        mergeSort(v1,v1.size());
        mergeSort(v2,v2.size());
        merge(nums,v1,v2);// implemented in helper_functions.cpp
    }
}