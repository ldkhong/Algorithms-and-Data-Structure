#include "project1.h"
//Using pseudo code in lecture slide
//{32,64,128,256,512,1024,2048,4096,8192,16384};
static const std::vector<int> shell_1 = {32768,16384,8192,4096,2048,1024,512,256,128,64,32,16,8,4,2,1,0};

uint64_t shell_sort1(std::vector<int>& nums) {
    int length = nums.size();
    int gap = shell_1[0], k = 0;
    while (gap >= length && k < 15){
        k++;
        gap = shell_1[k];
    }
      
    uint64_t  elapsed_time = 0;
    auto start_time = std::chrono::steady_clock::now();

    while (gap > 0) {
        //sorting elements that are "gap" indexes apart
        for (int i = gap; i < length; i++) {
            int temp = nums[i];
            int j = i;
            while ( j >= gap && temp < nums[j - gap]) {
                nums[j] = nums[j-gap];
                j -= gap;
            }
            nums[j] = temp;
        }
        k++;
        gap = shell_1[k]; // divide gap by 2 until it > 0
    }
    
    auto end_time = std::chrono::steady_clock::now();
    elapsed_time = std::chrono::nanoseconds(end_time - start_time).count();
    return elapsed_time;
}


