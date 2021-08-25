#include "helper_functions.h"
#include <iostream>

// merging of 2 sorted vectors v1 and v2 to nums, 
// I implemented this function by following the algorithm in lecture slide.
void merge(std::vector<int>& nums,std::vector<int>& v1,std::vector<int>& v2)
{
    int i = 0, j = 0; // start at 2 first elements of vectors v1 and v2
    int size_1 = v1.size(), size_2 = v2.size();

    while (i < size_1 && j < size_2) {
    // compare the 2 elements of the 2 vectors, then insert the smaller to nums
        if (v1[i] <= v2[j]) { 
            nums[i+j] = v1[i];
            i++;
        }
        else {
            nums[i+j] = v2[j];
            j++;
        }
    }
    //insert the remaining elements of vector 1 or 2 if have
    while (i < size_1) {
        nums[i+j] = v1[i];
        i++;
    }

    while (j < size_2) {
        nums[i+j] = v2[j];
        j++;
    }

}

void printVector(std::vector<int>& nums)
{  
    int length = nums.size();

    if(length == 0) {
        std::cout << "emtpy";
    }
    else {
        for (int i = 0; i < length; i++) {
            std::cout<< nums[i] << " ";
        }
    }
    std::cout << std::endl;
}
