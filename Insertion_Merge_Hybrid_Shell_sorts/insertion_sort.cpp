#include "project1.h"

uint64_t insertion_sort(std::vector<int>& nums){
    uint64_t  elapsed_time = 0;
    auto start_time = std::chrono::steady_clock::now();
    int length = nums.size();
    for (int i = 1; i < length; i++) { //start at the second element of the list
        int temp = nums[i]; 
        int j = i;

        while(j > 0 && nums[j-1] > temp){ //keep comparing and shifting until the correct location found
            nums[j] = nums[j-1];
            j--;
        }
        nums[j] = temp;
    }
    
    auto end_time = std::chrono::steady_clock::now();
    elapsed_time = std::chrono::nanoseconds(end_time - start_time).count();
    return elapsed_time;
}