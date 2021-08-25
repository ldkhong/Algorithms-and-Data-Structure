#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <vector>
#include <unordered_set>
#include "node.h"

class Graph 
{
	public:
		// DO NOT MODIFY MEMBERS BELOW THIS LINE
        int get_num_nodes(); 						// get number of nodes
        int get_num_edges(); 						// get number of edges
        std::vector<Node> get_neighbors(Node u); 	// return neighbors of u 
        std::map<int, Node> get_id_to_node_map(); 	// allows lookup of nodes from ids
		// DO NOT MODIFY MEMBERS ABOVE THIS LINE
		
		// declare any constructors, members, and member functions you may want to use
        Graph(){};
        std::vector<std::unordered_set<int> > graphList;
        std::map<int, Node> node_map;
        int numNodes = 0;
        int numEdges = 0;
		
		// implement any newly declared member functions in graph.cpp
};

#endif
