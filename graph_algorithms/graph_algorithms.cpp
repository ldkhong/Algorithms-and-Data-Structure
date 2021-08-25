#include "graph.h"
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <list>
#include <iostream>

int bFS (int id, Graph G, int& dmax);

int get_diameter(Graph graph)
{
	// TODO
	srand(time(NULL));
	int id = rand() % graph.numNodes + 1;
	int dMax = 0;
	int temp = 0;
	int farthest = bFS(id, graph, temp);
	while (temp > dMax){
		dMax = temp;
		farthest = bFS(farthest, graph, temp);
	}
	return dMax; // remove this line if you implement the function
}

float get_clustering_coefficient(Graph graph) 
{
	// TODO
	//number of 2-edge paths and compute array D list of degrees of vertices
	int two_edge_paths = 0;
	std::vector<int> degrees;
	int max = 0;
	for (int i = 0; i < graph.numNodes; i++) {
		int deg = graph.graphList[i].size();
		two_edge_paths += (deg * (deg - 1))/2;
		if(max < deg)
			max = deg;
		degrees.push_back(deg);
	}
	// get degenaracy of graph
	std::unordered_set<int> visited;
	std::list<int> l;
	std::vector<std::list<int> > d (max+1, std::list<int>{});
	std::vector<std::vector<int> > neighbor_v (graph.numNodes, std::vector<int>{});

	for (int i = 0; i < graph.numNodes; i++)
		d[degrees[i]].push_back(i+1);

	int j = 0;
	while( j < (max+1) && d[j].empty()) 
			j++;
	
	for(int i = 0; i< graph.numNodes; i++){	
		int v = d[j].back();
		d[j].pop_back();
		l.push_front(v);
		visited.insert(v);
		std::vector<Node> neighbor = graph.get_neighbors(graph.node_map[v]);
		
		for (int m = 0; m < neighbor.size(); m++){
			int w = neighbor[m].id;
			if(visited.find(w)==visited.end()) {
				d[degrees[w-1]].remove(w);
				degrees[w - 1] -= 1;
				d[degrees[w-1]].push_back(w);
				neighbor_v[v-1].push_back(w);
			}		
		} 
		if(!d[j-1].empty())
			j--;
		else if(d[j].empty())
			while( j < (max + 1) && d[j].empty())
				j++;
	}

	// count triangle
	int triangle = 0;
	std::list<int>::iterator iterEnd = l.end();
	for(std::list<int>::iterator iter = l.begin(); iter != iterEnd; iter++)
	{
		int v = *iter-1;
		int length = neighbor_v[v].size();
		for (int m = 0; m < length; m++){
			for(int n = m + 1; n < length; n++){
				if(graph.graphList[neighbor_v[v][m]-1].find(neighbor_v[v][n]) != graph.graphList[neighbor_v[v][m]-1].end())
					triangle++;
			}
		}
	} 
	float rs = 3.0 * triangle / two_edge_paths;
	return rs;  // remove this line if you implement the function 
}

// key-value pairs represent {degree, number of nodes with that degree}
std::map<int, int> get_degree_distribution(Graph graph) 
{
	// TODO
	std::map<int,int> rs;
	for(int i = 0; i < graph.numNodes; i++) {
		int deg = graph.graphList[i].size();
		if(rs.find(deg) != rs.end())
			rs[deg] += 1;
		else
			rs[deg] = 1;
	}
	return rs; 
}

int bFS (int id, Graph G, int& dmax){
    int max = 0;
    int farthest = id;
    std::vector<int> reached;
    for(int i = 0; i < G.numNodes; i++)
        reached.push_back(-1);
    reached[id-1] = 0;
    std::queue<int> q;
    q.push(id);
    while(!q.empty()) {
        int v = q.front();
        q.pop();
        std::vector<Node> neighbor = G.get_neighbors(G.node_map[v]);
        for(int i = 0; i < neighbor.size(); i++) {
            if(reached[neighbor[i].id - 1] == -1){
                q.push(neighbor[i].id);
                reached[neighbor[i].id - 1] = reached[v-1] + 1;
                if( max < reached[v-1] + 1) 
                    max = reached [v-1] + 1;
            }
        }
    }
    dmax = max;
    for(int i = 0; i < G.numNodes; i++)
        if(max == reached[i])
            return i+1;
    return farthest;
}
