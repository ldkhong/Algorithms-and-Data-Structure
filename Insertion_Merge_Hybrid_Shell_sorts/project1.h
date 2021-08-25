#include <vector>
#include <chrono>
//REQUIREMENTS:
//each sort should be implemented in its own file of the same name e.g. insertion_sort.cpp
//each file should #include this header file
//no file should use anything outside of the C++ standard library
//functions should be tested using g++ in a linux environment
//each function should modify the input vector so that it is sorted upon completion
uint64_t insertion_sort(std::vector<int>& nums);
uint64_t merge_sort(std::vector<int>& nums);
uint64_t shell_sort1(std::vector<int>& nums);
uint64_t shell_sort2(std::vector<int>& nums);
uint64_t shell_sort3(std::vector<int>& nums);
uint64_t shell_sort4(std::vector<int>& nums);
uint64_t hybrid_sort1(std::vector<int>& nums);
uint64_t hybrid_sort2(std::vector<int>& nums);
uint64_t hybrid_sort3(std::vector<int>& nums);
