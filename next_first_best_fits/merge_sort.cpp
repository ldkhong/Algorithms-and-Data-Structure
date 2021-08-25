#include "merge_sort.h"

void merge(std::vector<double>& nums,std::vector<double>& v1,std::vector<double>& v2)
{
    int i = 0, j = 0; // start at 2 first elements of vectors v1 and v2
    int size_1 = v1.size(), size_2 = v2.size();

    while (i < size_1 && j < size_2) {
    // compare the 2 elements of the 2 vectors, then insert the smaller to nums
        if (v1[i] > v2[j]) { 
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
        nums[i+j]= v1[i];
        
        i++;
    }

    while (j < size_2) {
        nums[i+j] = v2[j];
        j++;
    }

}

void merge_sort(std::vector<double>& nums) {

    int length = nums.size();
    mergeSort(nums, length);
}

void mergeSort (std::vector<double>& nums, int length) {
    if (length > 1) {
        std::vector<double>v1 (nums.begin(), nums.begin() + length/2);//firs hafl
        std::vector<double> v2 (nums.begin() + length/2, nums.end());//second half 
        mergeSort(v1,v1.size());
        mergeSort(v2,v2.size());
        merge(nums,v1,v2);// implemented in helper_functions.cpp
    }
}

bool lessEqual(double x, double y)
{
    return (std::fabs(y - x) < 1e-4) || (x < y); 
}