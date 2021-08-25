#include "project1.h"
#include "helper_functions.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <stdlib.h>
#include <locale.h>
#include <stdio.h>
#include <cmath>
#include <fstream>
#include <string>
#include <functional>
#include <cstdio>
#include <iterator>
#include <unordered_map>

static std::vector<int> sqs = {32,64,128,256,512,1024,2048,4096,8192,16384, 32768, 65536, 131072};

void save_data(const std::string& file_name, unsigned input_size, uint64_t elapsed_time_sum, unsigned num_runs, std::string& type);

typedef std::function<uint64_t(std::vector<int>&)> SORT_FUNCTION;

static const std::unordered_map<std::string, SORT_FUNCTION> SORT_MAP = {
	{"insertion_sort", insertion_sort},
	{"merge_sort", merge_sort},
	{"hybrid_sort1", hybrid_sort1},
	{"hybrid_sort2", hybrid_sort2},
	{"hybrid_sort3", hybrid_sort3},
	{"shell_sort1", shell_sort1},
	{"shell_sort2", shell_sort2},
	{"shell_sort3", shell_sort3},
	{"shell_sort4", shell_sort4},
};

std::vector<int> generateTest(int sz, int maxVal, int type)
{
	// sz: size of generated sequence,  maxVal: maximum value that the sequence can have
	// type = 1: random sequence
	// type = 2: almost sorted
	// type = 3: sorted in reverse
	std::vector<int> result;
	for (int i = 0; i < sz; i++) {
		result.push_back(i + 1);
	}
	
	if (type ==	1) {
		std::random_device rd;
    	std::mt19937 g(rd());
		std::shuffle(result.begin(),result.end(),g);
	}
	else if (type == 2) {
		int pairs = 2 * log2(sz);
		for (int i = 0; i < pairs; i++) {
			std::swap(result[rand() % sz], result[rand() % sz]);
		}
	}
	else if	(type == 3) {
			std::sort(result.rbegin(), result.rend());
	}
	printVector(result);
	return result;
}

void testAlgorithm(std::vector<std::vector<int> > tests, int nums, std::string& type)
{	
	for (const auto& func : SORT_MAP) {
		std::cout << func.first << " ";
		uint64_t  elapsed_time_sum = 0;
		for(auto test : tests) {
			for (int i = 0; i < nums; i++) {
				std::vector<int> v1 = test;
				std::sort(v1.begin(), v1.end());
				std::vector<int> v2 = test;
				elapsed_time_sum += func.second(v2);
				if (v1 == v2) {
					std::cout << "CORRECT" << std::endl;
				} else {
					std::cout << "INCORRECT" << std::endl;
				}
			}
			std::string file_name = func.first;
			save_data(file_name, test.size(), elapsed_time_sum, nums, type);
		}
	}
	//std::cout << elapsed_time_sum / nums << "\n";
	//std::string file_name = "insertion_3";
	//save_data(file_name, test.size(), elapsed_time_sum, nums);
}

void save_data(const std::string& file_name, unsigned input_size, uint64_t elapsed_time_sum, unsigned num_runs, std::string& type)
{

	std::ofstream out;
	out.open("/Users/loclinh/desktop/CS165/run_time/" + file_name + "_" + type + ".csv", std::ofstream::out | std::ofstream::app);
	out << input_size << ",";
	out <<  static_cast<uint64_t>(round(elapsed_time_sum / num_runs))<<"\n";
	out.close();
}

int main()
{
	// generate new tests
	//std::vector<std::vector<int> > tests;
	std::vector<std::vector<int> > tests_1;
	std::vector<std::vector<int> > tests_2;
	std::vector<std::vector<int> > tests_3;
	for (int i = 0; i < sqs.size(); i++)
	{
		//tests_1.push_back(generateTest(sqs[i], sqs[i], 1));
		//tests_2.push_back(generateTest(sqs[i], sqs[i], 2));
		tests_3.push_back(generateTest(sqs[i], sqs[i], 3));
	} 
	//tests_2.push_back(generateTest(128, 128, 2));
	std::string type = "3";
	testAlgorithm(tests_3, 5, type);
	//testAlgorithm(tests_2, 5);
	//testAlgorithm(tests_3, 5);

	return 0;
}
