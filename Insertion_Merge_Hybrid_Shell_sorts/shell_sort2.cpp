#include "project1.h"
#include <math.h>

// 2^k + 1
//{32,64,128,256,512,1024,2048,4096,8192,16384};
static const std::vector<int> shell_2 = {32769,16385,8193,4097,2049,1025,513,257,129,65,33,17,9,5,3,1,0};

uint64_t shell_sort2(std::vector<int>& nums) {
    int length = nums.size();
    int gap = shell_2[0], k = 0;
    while (gap >= length){
        k++;
        gap = shell_2[k];
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
        gap = shell_2[k];
    }
    auto end_time = std::chrono::steady_clock::now();
    elapsed_time = std::chrono::nanoseconds(end_time - start_time).count();
    return elapsed_time;
}