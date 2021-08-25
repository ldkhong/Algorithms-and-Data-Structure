#include "project1.h"
bool is_3smooth(int x);

// 2^i * 3^j
uint64_t shell_sort3(std::vector<int>& nums) {
    int length = nums.size();

    if(length > 1){
        std::vector<int> gap_list; // list of 3smooth numbers < length
        int gap_element = 1; 
        while(gap_element < length) { // check numbers from 1 to (length - 1)
            if (is_3smooth(gap_element)) { // if it is 3smooth numbers
                gap_list.push_back(gap_element); // add to the list
            }
            gap_element++;
        }
        //sorting elements that are "gap" indexes apart
        uint64_t  elapsed_time = 0;
        auto start_time = std::chrono::steady_clock::now();
        for (int gap = gap_list.size()-1; gap >= 0; gap--) {
            for (int i = gap_list[gap]; i < length; i++) {
                int temp = nums[i];
                int j = i;
                while ( j >= gap_list[gap] && temp < nums[j - gap_list[gap]]) {
                    nums[j] = nums[j-gap_list[gap]];
                    j -= gap_list[gap];
                }
                nums[j] = temp;
            }
        }
        auto end_time = std::chrono::steady_clock::now();
        elapsed_time = std::chrono::nanoseconds(end_time - start_time).count();
        return elapsed_time;
    }
    return 0;
}

bool is_3smooth(int x) // check if x is a factor of 2 and 3
{
    if (x == 1)
        return true;
    if (x % 2 == 0)
        return is_3smooth(x/2);
    if (x % 3 == 0)
        return is_3smooth(x/3);

    return false;
}
