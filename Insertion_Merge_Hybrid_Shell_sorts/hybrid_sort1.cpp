#include "project1.h"
#include "helper_functions.h"
#include <math.h>

void hybridSort1(std::vector<int>& nums, int H);

uint64_t hybrid_sort1(std::vector<int>& nums)
{
    int H = static_cast<int> (sqrt(nums.size()));
    uint64_t  elapsed_time = 0;
    auto start_time = std::chrono::steady_clock::now()
    ;
    hybridSort1(nums, H);
    
    auto end_time = std::chrono::steady_clock::now();
    elapsed_time = std::chrono::nanoseconds(end_time - start_time).count();
    return elapsed_time;
}

//Using the pseudo code in lecture slides
void hybridSort1(std::vector<int>& nums, int H) {
    int length = nums.size();
    if (length > H) {
            std::vector<int> v1(nums.begin(), nums.begin() + length/2); // first half elements of nums.
            std::vector<int> v2 (nums.begin() + length/2, nums.end()); //second half elements of nums
            hybridSort1(v1, H);
            hybridSort1(v2, H);
            merge(nums,v1,v2); // implemented in helper_functions.cpp
    }
    else {
        for (int i = 1; i < length; i++) { 
            int temp = nums[i]; 
            int j = i;

            while(j > 0 && nums[j-1] > temp){ 
                nums[j] = nums[j-1];
                j--;
            }
            nums[j] = temp;
        }
    }
}
