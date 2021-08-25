#include "project2.h"
#include "ZipTree.h"
#include "merge_sort.h"

//return the bin index of first fit bin and update BRC after assign item to bin 
int find_bin (ZipTree<int, double>::Node* &p, std::vector<double>& brc, double size);
//update brc after insert new bin
void heapify(ZipTree<int, double>::Node* &p, std::vector<double>& brc, int key);

void first_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
   int length = items.size();
    if (length > 0) {
        //initialize first bin, emptry Ziptree and best remaining capacity
        int bin = 1; 
        ZipTree <int,double> tree; 
        std::vector<double> brc; 

        //update BRC and free_space, insert bin to Zip tree
        brc.push_back(1.0); 
        free_space.push_back(1.0);  
        tree.insert(bin,1.0,ZipTree<int, double>::getRandomRank());
         
        for(int i = 0; i < length; i++) {
            // Compare Item size with BRC in Ziptree, if it <= root.BRC then 
            if(lessEqual(items[i], brc[tree.root->key-1])) {
                //get the first-fit bin, 
                int fit_bin = find_bin(tree.root,brc,items[i]); 

                //then assign to assignment and update bin free space.
                assignment[i] = fit_bin; 
                if (std::fabs(free_space[fit_bin-1] - items[i]) < 1e-7) 
                    free_space[fit_bin-1] = 0.0; 
                else
                    free_space[fit_bin-1] -= items[i];
            }
            // No current bin can store the items, assign to new bin,
            // add new bin to free_space and Ziptree then update BRC.
            else { 
                bin++;
                assignment[i] = bin;
                free_space.push_back(1.0 - items[i]);
                brc.push_back(1.0 - items[i]);
                tree.insert(bin,1.0 - items[i],ZipTree<int, double>::getRandomRank()); //log(n)
                heapify(tree.root, brc, bin); //log(n)
            }
        } 
    } 
}

void first_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
    std::vector <double> sort_items(items);
    merge_sort(sort_items);
    first_fit(sort_items,assignment,free_space);
}

void heapify(ZipTree<int, double>::Node* &p, std::vector<double>& brc, int key){
    ZipTree<int, double>::Node* cur = p;
    // find the new insert bin
    while (cur->key != key)  //O(logn)
        cur = (key < cur->key)? cur->llink : cur->rlink;

    while (cur != nullptr)
    {
        double cur_brc = brc[cur->key-1];
        // get left child BRC if it exists, else assume it = cur.brc
        double left_brc = (cur->llink == nullptr)? cur->val : brc[cur->llink->key-1];
        // do the same with right child
        double right_brc = (cur->rlink == nullptr)? cur->val : brc[cur->rlink->key-1];
        // compare left and right and get the max
        double max_brc = (left_brc > right_brc)? left_brc : right_brc;
        //update current brc with max
        brc[cur->key-1] = (max_brc > cur_brc)? max_brc : cur_brc;
        // go to the parent of current Node.
        cur = cur->plink;
    }
}

int find_bin (ZipTree<int, double>::Node* &p, std::vector<double>& brc, double s) {
    ZipTree<int, double>::Node* cur = p;

    bool found = false;
    while (cur != nullptr && !found) {
        //check from left-parent-right
        // if left.brc >= item size then go left
        if(cur->llink != nullptr && lessEqual(s, brc[cur->llink->key-1]))
            cur = cur->llink;
        // else if current.brc <= size, we find the bin
        else if(lessEqual(s, cur->val))
            found = true;
        else  // go to the right
            cur = cur->rlink;
    }
    //bin is guanrantee to be found since I check the BRC before calling the function, so cur cannot be nullptr.
    // get the bin and update bin remaing capacity
    int bin = cur->key;
    if (std::fabs(cur->val - s) < 1e-7) 
        cur->val = 0.0; 
    else
        cur->val -= s;

    //update brc
    while ( cur != nullptr) {
        //same as above algorithm
        double cur_brc = cur->val;
        double left_brc = (cur->llink == nullptr)? cur->val : brc[cur->llink->key-1];
        double right_brc = (cur->rlink == nullptr)? cur->val : brc[cur->rlink->key-1];
        double max_brc = (left_brc > right_brc)? left_brc : right_brc;
        brc[cur->key-1] = (max_brc > cur_brc)? max_brc : cur_brc;
        cur = cur->plink;
    }
    return bin;
}