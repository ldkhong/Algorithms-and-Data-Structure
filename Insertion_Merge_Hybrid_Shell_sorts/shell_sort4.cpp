#include "project1.h"

void generate_gap(std::vector<int>& gap_list, int length);

// A033622 Good sequence of increments for Shell sort
uint64_t shell_sort4(std::vector<int>& nums) {
    int length = nums.size();

    if (length > 1) {
        std::vector<int> gap_list;
        generate_gap(gap_list, length);
        
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

//formula: a(0)=1, a(1)=5, a(2)=19, a(3)=41, a(4)=109, a(n)=a(n-1)+6*a(n-2)- 6*a(n-3)- 8*a(n-4)+8*a(n-5) - Harvey P. Dale, Mar 02 2015.
void generate_gap(std::vector<int>& gap_list, int length)
{
    gap_list.push_back(1);
    int n = 1;

    while (gap_list.back() < length)
    {
            if ( n == 1)
                gap_list.push_back(5);
            else if (n == 2)
                gap_list.push_back(19);
            else if (n == 3)
                gap_list.push_back(41);
            else if (n == 4)
                gap_list.push_back(109);
            else
                gap_list.push_back(gap_list[n-1] + 6*gap_list[n-2] - 6*gap_list[n-3] - 8*gap_list[n-4] + 8*gap_list[n-5]);
            n++;
    }
    gap_list.pop_back();
}