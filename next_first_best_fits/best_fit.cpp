#include "project2.h"
#include "ZipTree.h"
#include "merge_sort.h"
#include <utility>
//return the best bin if exists, else nullptr
ZipTree <std::pair<double,int>, double>::Node* best_bin (ZipTree <std::pair<double,int>, double>::Node* &p, double size); 

void best_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
    int length = items.size();
    if (length > 0) {
        int bin = 1; // first bin 
        ZipTree <std::pair<double,int>, double> tree; // key(rc, id), val(rc)
        free_space.push_back(1.0);
        tree.insert(std::make_pair(1.0, bin), 1.0, ZipTree <std::pair<double,int>, double>::getRandomRank()); //log(n)

        for(int i = 0; i < length; i++) {
            ZipTree <std::pair<double,int>, double>::Node* best = best_bin(tree.root, items[i]);
            if(best != nullptr) {
                int bb = best->key.second;
                assignment[i] = bb;

                //remove and re-insert if rc > 0 to rebalance tree.
                //update free_space 
                tree.remove(best->key); 
                if (std::fabs(free_space[bb-1] - items[i]) < 1e-7) 
                    free_space[bb-1] = 0.0;
                else {
                    free_space[bb-1] -= items[i];
                    tree.insert(std::make_pair(free_space[bb-1], bb),free_space[bb-1],ZipTree <std::pair<double,int>, double>::getRandomRank());
                }
            }
            // assign item to new bin, update free_space, insert new bin to Tree
            else {  
                double free = 1.0 - items[i];
                free_space.push_back(free);
                bin++;
                assignment[i] = bin;
                tree.insert(std::make_pair(free, bin),free,ZipTree <std::pair<double,int>, double>::getRandomRank()); //log(n)
            }
        } 
    } 
}

void best_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
    std::vector <double> sort_items(items);
    merge_sort(sort_items);
    best_fit(sort_items,assignment,free_space); 
}

ZipTree <std::pair<double,int>, double>::Node* best_bin (ZipTree <std::pair<double,int>, double>::Node* &p, double size) {
    ZipTree <std::pair<double,int>, double>::Node* cur = p;
    ZipTree <std::pair<double,int>, double>::Node* best = nullptr;

    while(cur != nullptr) { 
        // go left if <= parent node else go right
        if(lessEqual(size, cur->key.first)) {
            best = cur;
            cur = cur->llink;
        }
        else 
            cur = cur->rlink;
    }
    return best;
} 