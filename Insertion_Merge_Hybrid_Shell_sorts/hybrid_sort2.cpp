#include "project1.h"
#include <math.h>
#include "helper_functions.h"

void hybridSort2(std::vector<int>& nums, int H);

// H = n^1/4
uint64_t hybrid_sort2(std::vector<int>& nums)
{
    double power = 1.0/4.0;
    int H = static_cast<int> (pow(nums.size(),power));
    uint64_t  elapsed_time = 0;
    auto start_time = std::chrono::steady_clock::now();
    hybridSort2(nums, H);
    auto end_time = std::chrono::steady_clock::now();
    elapsed_time = std::chrono::nanoseconds(end_time - start_time).count();
    return elapsed_time;
}

void hybridSort2(std::vector<int>& nums, int H) {
    int length = nums.size();
    
    if (length > H) {
            std::vector<int> v1(nums.begin(), nums.begin() + length/2); //first half elements of nums.
            std::vector<int> v2 (nums.begin() + length/2, nums.end()); //second half elements of nums
            hybridSort2(v1, H);
            hybridSort2(v2, H);
            merge(nums,v1,v2); // implemented in helper_functions.cpp
    }
    else {
        for (int i = 1; i < length; i++) { //start at the second element of the list
            int temp = nums[i]; 
            int j = i;

            while(j > 0 && nums[j-1] > temp){ //keep comparing and shifting until the correct location found
                nums[j] = nums[j-1];
                j--;
        }
            nums[j] = temp;
        }
    }
}