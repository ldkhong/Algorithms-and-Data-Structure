#include "project1.h"
#include <chrono>
#include <functional>
#include <cmath>
#include <fstream>
#include <iostream>
#include <locale.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <cstdio>


typedef std::function<uint64_t(std::vector<int>&, unsigned, unsigned)> SORT_FUNCTION;
typedef std::function<std::vector<int>(unsigned, PRNG&)> GET_VECTOR_FUNCTION;

static const std::unordered_map<std::string, SORT_FUNCTION> SORT_MAP = {

	{"merge_sort", merge_sort_c},

};

static const std::unordered_map<std::string, GET_VECTOR_FUNCTION> GET_VECTOR_MAP = { 

	/* These functions below need to be implemented. You can use uniform_int_distribution<int> in the process of 
	generating a random or almost sorted vector
	*/
	{"reverse", get_reverse_vector},
	{"random", get_random_vector},
	{"almost_sorted", get_almost_sorted_vector},
};

void save_data(const std::string& dir_name, const std::string& file_name,
	unsigned input_size, uint64_t elapsed_time_sum, uint64_t num_comparisons_sum, unsigned num_runs)
{

	std::ofstream out;
	out.open("/Users/haleh/Dropbox/165/pr1/CS165-of_pr1/sorting/data/" +dir_name + "/"+ file_name + ".csv", std::ofstream::out | std::ofstream::app);
	out << input_size << ",";
	out <<  static_cast<uint64_t>(round(elapsed_time_sum / num_runs))<<",";
	out << (int) round(num_comparisons_sum /  num_runs)<< "\n";
	out.close();
}

void run_experiment(unsigned min_input_size, unsigned input_size, unsigned num_runs)
{

	for (const auto& file_name_func : GET_VECTOR_MAP)
	{
		std::string file_name = file_name_func.first;

		std::vector<int> nums = file_name_func.second(input_size);
		 
		for (const auto& dir_name_func : SORT_MAP)
		{

			std::string dir_name = dir_name_func.first;
			if(min_input_size == input_size){ // this is expected to delete the file if we are at the beginning of the experiment. Late in save_data() it would be
			// created and getting appended 
				 std::string file_temp = "/Users/haleh/Dropbox/165/pr1/CS165-of_pr1/sorting/data/" +dir_name + "/"+ file_name + ".csv";
				 std::remove(file_temp.c_str());
				 std::cout << file_temp << std::endl; 
			}
			auto temp = nums;
			uint64_t  elapsed_time_sum = 0;
			uint64_t num_comparisons_sum = 0;
			for (unsigned i = 0; i < num_runs; ++i)
			{
				auto start_time = std::chrono::steady_clock::now();

			    num_comparisons_sum += dir_name_func.second(temp, 0u, -1u); // calling your sort function on the input temp; alter the arguments as needed

				auto end_time = std::chrono::steady_clock::now();
				elapsed_time_sum += std::chrono::nanoseconds(end_time - start_time).count();
			}
			save_data(dir_name, file_name, input_size, elapsed_time_sum, num_comparisons_sum, num_runs);
		}

	}
}

void run_experiments(unsigned min_input_size, unsigned max_input_size, double factor, unsigned num_runs)
{

	for (unsigned input_size = min_input_size; input_size <= max_input_size; input_size *= factor)
	{
		
		run_experiment(min_input_size, input_size, num_runs);
		std::cout << "Experiments with input size "<< input_size <<" for "<< num_runs <<" runs"<<" are done" << std::endl;
	}
}

int main()
{ 
	run_experiments(2, 10000, 2, 10);
	
	return 0;

}