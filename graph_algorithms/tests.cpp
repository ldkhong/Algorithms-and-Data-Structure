// Instructions:
//
// Move all source code/header files you will be submitting to a new directory, along with the two files Makefile and project3_tests.cpp
// Edit the main function to create and try different test cases on your algorithms
// Enter the command "make" to compile and run the program
// If you make any changes to any of the files, enter the command "make clean" to remove the generated executable before entering "make" again.
//
// note that passing the test cases here does not necessarily mean your algorithms will pass other test cases
// so it's a good idea to create and try different test cases

#include "project3.h"
#include <assert.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <random>
#include <fstream>

using namespace std;
Graph graph_BA (int n, int d) {
    int length = 2*n*d;
    Graph graph;
    graph.numNodes = n;

    for(int i = 0; i < n; i++) {
        Node newNode(i+1);
        graph.node_map[i+1] = newNode;
        graph.graphList.push_back(std::unordered_set<int>{});
    }
   
    std::vector<int> m (length,-1);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    for(int v = 0; v < n; v++)
        for(int i = 0; i < d; i++){
            int pos = 2*(v*d+i);
            m[pos] = v;
            std::uniform_int_distribution<int> dist(0, pos);
            int r = dist(generator);
            m[pos+1] = m[r];
        }
    
    for (int i = 0; i < n*d; i++) {
            graph.graphList[m[2*i]].insert(m[2*i + 1] + 1);
            graph.graphList[m[2*i+1]].insert(m[2*i] + 1);
    }
    return graph;
}

void save_data(const std::string& file_name, int numNodes, std::map<int,int> deg)
{
	std::ofstream out;
	out.open("/Users/loclinh/desktop/CS165/project3/data/" + file_name + "_" + to_string(numNodes) + ".csv", std::ofstream::out | std::ofstream::app);
    for(std::map<int,int>::iterator iter = deg.begin(); iter != deg.end(); iter++) {
        out << iter->first << "," << iter->second << "\n";
    }
	out.close();
}

void save_data_2(const std::string& file_name, unsigned numNodes, double avg)
{
	std::ofstream out;
	out.open("/Users/loclinh/desktop/CS165/project3/data/" + file_name + ".csv", std::ofstream::out | std::ofstream::app);
    out << numNodes << "," << avg << "\n";
	out.close();
}

void save_data_3(const std::string& file_name, unsigned numNodes, float avg)
{
	std::ofstream out;
	out.open("/Users/loclinh/desktop/CS165/project3/data/" + file_name + ".csv", std::ofstream::out | std::ofstream::app);
    out << numNodes << "," << avg << "\n";
	out.close();
}

void message(string s)
{
    cout << s << "\n";
}

void newline()
{
    cout << "\n";
}

bool floating_compare(float a, float b)
{
    return std::fabs(a-b) < 1e-3;
}

bool vectors_have_same_nodes(vector<Node> nodes1, vector<Node> nodes2)
{
    sort(nodes1.begin(), nodes1.end(), [](const Node& u, const Node& v){return u.id < v.id;});
    sort(nodes2.begin(), nodes2.end(), [](const Node& u, const Node& v){return u.id < v.id;});
    return nodes1 == nodes2;
}

int main()
{
    //test diameter, test clustering_coefficient
    //get degree_distribution
   for(int i = 1000; i < 100001; i*=10){
        Graph g= graph_BA(i,5);
        std::map<int,int> deg = get_degree_distribution (g);
        save_data("degree_distribution", i, deg);
    }  
  /*  
    for(int i = 8; i < 100000; i*=2){
        int diameter = 0;
        float coeff = 0.0;
        for(int j = 0; j<10; j++) {
            Graph g= graph_BA(i,5);
            diameter += get_diameter(g);
            coeff += get_clustering_coefficient(g);
        }
        double diameter_avg = diameter*1.0000/10.0;
        float avg = coeff / 10.0;
        std::cout<< diameter_avg << " " << avg << "\n";
        save_data_2("diameter",i,diameter_avg);
        save_data_3("clustering",i,avg);
    }
*/


    std::cout << "\n";
    return 0;
}

