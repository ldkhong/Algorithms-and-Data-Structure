#include "ZipTree.h"
#include "project2.h"

#include <iostream>
#include <utility>
#include <string>
#include <cmath>
#include <unordered_map>
#include <functional>
#include <iomanip>
#include <fstream>
#include <iterator>
#include <cstdio>

void save_data(const std::string& file_name, unsigned input_size, double wasted_sum);

static std::vector<int> items_size = {32,64,128,256,512,1024,2048,4096,8192,16384, 32768, 65536, 131072};

std::vector<double> generate_items(int size) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis (0.0,0.6);
	std::vector<double> items;

	for(int i = 0; i< size; i++)
		items.push_back(dis(gen));

	return items;
}
typedef std::function<void(const std::vector<double>&, std::vector<int>&, std::vector<double>&)> FIT_FUNCTION;

static const std::unordered_map<std::string, FIT_FUNCTION> FIT_MAP = {
	{"next_fit", next_fit},
	{"first_fit", first_fit},
	{"first_fit_decreasing", first_fit_decreasing},
	{"best_fit", best_fit},
	{"best_fit_decreasing", best_fit_decreasing},
};

void testAlgorithm(const std::vector<std::vector<double> >& items, int size)
{	
	for (const auto& func : FIT_MAP) {
		std::cout << func.first << " ";
		double  wasted_sum = 0.0;
		for(auto test : items) {
			std::vector<int> assignments(test.size(), 0);
			std::vector<double> free_space;
			func.second(test,assignments,free_space);
			double  wasted = 0.0;
			for (int i = 0; i < free_space.size(); i++)
				if(free_space[i] < 0)
					wasted += 0.0;
				else
					wasted += free_space[i];
			wasted_sum += wasted;
		}
		std::cout << wasted_sum << "\n";
		std::string file_name = func.first;
		save_data(file_name, size, wasted_sum);
	}
}

void save_data(const std::string& file_name, unsigned input_size, double wasted_sum)
{
	double avg = wasted_sum / 10.0;
	std::ofstream out;
	out.open("/Users/loclinh/desktop/CS165/project2/run_time/" + file_name + ".csv", std::ofstream::out | std::ofstream::app);
	out << input_size << ",";
	out << avg << "\n";
	out.close();
}


int main()
{
	for (int i = 0; i < items_size.size(); i++){
	std::vector<std::vector<double> > items; 
		for(int j = 0 ;j < 10; j++)
		{
			items.push_back(generate_items(items_size[i]));
		}
		testAlgorithm(items,items_size[i]);
	}

	/*
	// ------------------
	// bin packing tests
	// ------------------
	std::cout << std::endl;
	std::cout << "testing bin packing" << std::endl;
	std::cout << "test 1" << std::endl;

	// define list of items
	std::vector<double> items {0.1, 0.8, 0.3, 0.5, 0.7, 0.2, 0.6, 0.4};
	std::vector<int> assignments(items.size(), 0);
	std::vector<double> free_space;
	ProblemInstance test1 = {items, assignments, free_space}, expected_result;

	// next_fit
	expected_result = {items, {1, 1, 2, 2, 3, 3, 4, 4}, {0.1, 0.2, 0.1, 0.0}};
	testAlgorithm(test1, expected_result, next_fit, "next_fit");

	// first_fit
	expected_result = {items, {1, 1, 2, 2, 3, 2, 4, 4}, {0.1, 0.0, 0.3, 0.0}};
	testAlgorithm(test1, expected_result, first_fit, "first_fit");

	// first_fit_decreasing
	expected_result = {items, {1, 2, 3, 4, 3, 2, 1, 4}, {0.0, 0.0, 0.0, 0.4}};
	testAlgorithm(test1, expected_result, first_fit_decreasing, "first_fit_decreasing"); 

	// best_fit
	expected_result = {items, {1, 1, 2, 2, 3, 2, 4, 4}, {0.1, 0.0, 0.3, 0.0}};
	testAlgorithm(test1, expected_result, best_fit, "best_fit");

	// best_fit_decreasing
	expected_result = {items, {1, 2, 3, 4, 3, 2, 1, 4}, {0.0, 0.0, 0.0, 0.4}};
	testAlgorithm(test1, expected_result, best_fit_decreasing, "best_fit_decreasing"); 

	// ----------------------------------test 2 ----------------------------------
	std::cout << std::endl;
	std::cout << "test 2" << std::endl;
	items = {0.79, 0.88, 0.95, 0.12, 0.05, 0.46, 0.53, 0.64, 0.04, 0.38, 0.03, 0.26};
	assignments = std::vector<int> (items.size(), 0);
	ProblemInstance test2 = {items, assignments, free_space};

	// next_fit
	expected_result = {items, {1, 2, 3, 4, 4, 4, 5, 6, 6, 7, 7, 7}, {0.21, 0.12, 0.05, 0.37, 0.47, 0.32, 0.33}};
	testAlgorithm(test2, expected_result, next_fit, "next_fit");

	// first_fit
	expected_result = {items, {1, 2, 3, 1, 1, 4, 4, 5, 1, 6, 2, 5}, {0, 0.09, 0.05, 0.01, 0.1, 0.62}};
	testAlgorithm(test2, expected_result, first_fit, "first_fit");

	// first_fit_decreasing
	expected_result = {items, {1, 2, 3, 4, 5, 5, 6, 4, 2, 1, 3, 3}, {0, 0, 0.14, 0.1, 0.01, 0.62}};
	testAlgorithm(test2, expected_result, first_fit_decreasing, "first_fit_decreasing"); 

	// best_fit
	expected_result = {items, {1, 2, 3, 2, 3, 4, 4, 5, 1, 6, 1, 5}, {0.14, 0, 0, 0.01, 0.1, 0.62}};
	testAlgorithm(test2, expected_result, best_fit, "best_fit");

	// best_fit_decreasing
	expected_result = {items, {1, 2, 3, 4, 5, 5, 6, 4, 2, 1, 4, 4}, {0, 0, 0.21, 0.03, 0.01, 0.62}};
	testAlgorithm(test2, expected_result, best_fit_decreasing, "best_fit_decreasing"); 

	// ----------------------------------test 3 ----------------------------------
	std::cout << std::endl;
	std::cout << "test 3" << std::endl;
	items = {0.43, 0.75, 0.25, 0.42, 0.54, 0.03, 0.64};
	assignments = std::vector<int> (items.size(), 0);
	ProblemInstance test3 = {items, assignments, free_space};

	// next_fit
	expected_result = {items, {1, 2, 2, 3, 3, 3, 4}, {0.57, 0, 0.01, 0.36}};
	testAlgorithm(test3, expected_result, next_fit, "next_fit");

	// first_fit
	expected_result = {items, {1, 2, 1, 3, 3, 1, 4}, {0.29, 0.25, 0.04, 0.36}};
	testAlgorithm(test3, expected_result, first_fit, "first_fit");

	// first_fit_decreasing
	expected_result = {items, {1, 2, 3, 3, 4, 1, 2}, {0, 0.33, 0.03, 0.58}};
	testAlgorithm(test3, expected_result, first_fit_decreasing, "first_fit_decreasing");
	// best_fit
	expected_result = {items, {1, 2, 2, 1, 3, 1, 4}, {0.12, 0, 0.46, 0.36}};
	testAlgorithm(test3, expected_result, best_fit, "best_fit");

	// best_fit_decreasing
	expected_result = {items, {1, 2, 3, 3, 4, 1, 3}, {0, 0.36, 0, 0.58}};
	testAlgorithm(test3, expected_result, best_fit_decreasing, "best_fit_decreasing"); 

	// ----------------------------------test 4----------------------------------
	std::cout << std::endl;
	std::cout << "test 4" << std::endl;
	items = {0.54, 0.67, 0.46, 0.57, 0.06, 0.23, 0.83, 0.64, 0.47, 0.03, 0.53, 0.74, 0.36, 0.24, 0.07, 0.25, 0.05, 0.63, 0.43, 0.04};
	assignments = std::vector<int> (items.size(), 0);
	ProblemInstance test4 = {items, assignments, free_space};

	// next_fit
	expected_result = {items, {1, 2, 3, 4, 4, 4, 5, 6, 7, 7, 8, 9, 10, 10, 10, 10, 10, 11, 12, 12}, {0.46, 0.33, 0.54, 0.14, 0.17, 0.36, 0.5, 0.47, 0.26, 0.03, 0.37, 0.53}};
	testAlgorithm(test4, expected_result, next_fit, "next_fit");

	// first_fit
	expected_result = {items, {1, 2, 1, 3, 2, 2, 4, 5, 6, 2, 6, 7, 3, 5, 3, 7, 4, 8, 9, 4}, {0, 0.01, 0, 0.08, 0.12, 0, 0.01, 0.37, 0.57}};
	testAlgorithm(test4, expected_result, first_fit, "first_fit");

	// first_fit_decreasing
	expected_result = {items, {1, 2, 3, 4, 5, 6, 7, 8, 8, 7, 6, 4, 2, 3, 5, 1, 1, 3, 1, 3}, {0, 0.01, 0.01, 0, 0.14, 0, 0, 0}};
	testAlgorithm(test4, expected_result, first_fit_decreasing, "first_fit_decreasing"); 

	// best_fit
	expected_result = {items, {1, 2, 1, 3, 2, 2, 4, 5, 6, 2, 6, 7, 5, 7, 4, 3, 4, 8, 9, 4}, {0, 0.01, 0.18, 0.01, 0, 0, 0.02, 0.37, 0.57}};
	testAlgorithm(test4, expected_result, best_fit, "best_fit");

	// best_fit_decreasing
	expected_result = {items, {1, 2, 3, 4, 5, 6, 7, 8, 8, 7, 6, 4, 2, 3, 5, 3, 5, 5, 1, 5}, {0.13, 0.01, 0.02, 0, 0, 0, 0, 0}};
	testAlgorithm(test4, expected_result, best_fit_decreasing, "best_fit_decreasing"); 
	std::cout << std::endl;

	std::cout << "test 5" << std::endl;
	items = {0.54, 0.67, 0.46, 0.57, 0.06, 0.23, 0.83, 0.64, 0.47, 0.03, 0.53, 0.74, 0.36, 0.24, 0.07, 0.25, 0.05, 0.63, 0.43, 0.04, 0.53};
	assignments = std::vector<int> (items.size(), 0);
	ProblemInstance test5 = {items, assignments, free_space};

	expected_result = {items, {1, 2, 3, 4, 4, 4, 5, 6, 7, 7, 8, 9, 10, 10, 10, 10, 10, 11, 12, 12, 12}, {0.46, 0.33, 0.54, 0.14, 0.17, 0.36, 0.5, 0.47, 0.26, 0.03, 0.37, 0.00}};
	testAlgorithm(test5, expected_result, next_fit, "next_fit"); */
	return 0;
}

