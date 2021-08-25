#include "graph.h"

Graph make_graph(int num_nodes, std::vector<int> u, std::vector<int> v){
	// TODO
    Graph newGraph;
    newGraph.numNodes = num_nodes;
    newGraph.numEdges = u.size();
    for(int i = 0; i < num_nodes; i++) {
        Node newNode(i+1);
        newGraph.node_map[i+1] = newNode;
        newGraph.graphList.push_back(std::unordered_set<int>{});
    }
    for(int i = 0; i < u.size(); i++) {
        newGraph.graphList[u[i]-1].insert(v[i]);
        newGraph.graphList[v[i]-1].insert(u[i]);
    }
    
	return newGraph; // remove this line if you implement the function
}

int Graph::get_num_nodes() {
	// TODO
	return numNodes; // remove this line if you implement the function
}

int Graph::get_num_edges() {
	// TODO
	return numEdges; // remove this line if you implement the function
}

std::vector<Node> Graph::get_neighbors(Node u) {
	// TODO
    std::vector<Node> v;
    for(std::unordered_set<int>::iterator iter = graphList[u.id - 1].begin();
        iter != graphList[u.id - 1].end(); iter++)
        v.push_back(node_map[*iter]);
	return v; //remove this line if you implement the function
}

std::map<int, Node>Graph::get_id_to_node_map(){
	// TODO
	return node_map; // remove this line if you implement the function
}

