#include "project1.h"
#include "helper_functions.h"
#include <iostream>

// C++11
void test_insertion(std::vector<std::vector<int> > v);
void test_merge(std::vector<std::vector<int> > v);
void test_hybrid_1(std::vector<std::vector<int> > v);
void test_hybrid_2(std::vector<std::vector<int> > v);
void test_hybrid_3(std::vector<std::vector<int> > v);
void test_shell_1(std::vector<std::vector<int> > v);
void test_shell_2(std::vector<std::vector<int> > v);
void test_shell_3(std::vector<std::vector<int> > v);
void test_shell_4(std::vector<std::vector<int> > v);
int main() {
    std::vector<std::vector<int> > v = {
        {20,7,9,10,15,14,12,13,11,2,3,8,1,5,17,4,6,18,19,16},
        {10,9,8,7,6,5,4,3,2,1}, {9,1,2,3,4,5,8,7,6},
        {2,3,4,1,5,6,7,8}, {3,4,5,2,1,6,7}, {5,4,3,6,1,2},
        {5,3,4,2,1}, {1,2,3,4}, {1,3,2}, {2,1}, {1}, {}, };

    std::cout<< "--------------------------------" << std::endl;
    std::cout<<"Insertion sort: " << std::endl;
    //test_insertion(v);

    std::cout<< "--------------------------------" << std::endl;
    std::cout<<"Merge sort: " << std::endl;
    //test_merge(v);

    std::cout<< "--------------------------------" << std::endl;
    std::cout<<"Hybrid sort 1: " << std::endl;   
   //test_hybrid_1(v);

    std::cout<< "--------------------------------" << std::endl;
    std::cout<<"Hybrid sort 2: " << std::endl;
    //test_hybrid_2(v);

    std::cout<< "--------------------------------" << std::endl;
    std::cout<<"Hybrid sort 3: " << std::endl;
    //test_hybrid_3(v);

    std::cout<< "--------------------------------" << std::endl;
    std::cout<<"Shell sort 1: " << std::endl;
    //test_shell_1(v);

    std::cout<< "--------------------------------" << std::endl;
    std::cout<<"Shell sort 2: " << std::endl;
    //test_shell_2(v);

    std::cout<< "--------------------------------" << std::endl;
    std::cout<<"Shell sort 3: " << std::endl;
    test_shell_3(v);

    std::cout<< "--------------------------------" << std::endl;
    std::cout<<"Shell sort 4: " << std::endl;
    //test_shell_4(v);
  
    std::cout << std::endl;
    return 0;
}

void test_insertion(std::vector<std::vector<int> > v)
{   
    int length = v.size();
    
    for(int i = 0; i < length; i++){
        std::cout<<"Case " << i << ": "<< std::endl;
        printVector(v[i]);
       // insertion_sort(v[i]);
        printVector(v[i]);
    }
}
void test_merge(std::vector<std::vector<int> > v)
{
    int length = v.size();
    
    for(int i = 0; i < length; i++){
        std::cout<<"Case " << i << ": " << std::endl;
        printVector(v[i]);
      //  merge_sort(v[i]);
        printVector(v[i]);
    }
}

void test_hybrid_1(std::vector<std::vector<int> > v)
{
    int length = v.size();
    
    for(int i = 0; i < length; i++){
        std::cout<<"Case " << i << ": "<< std::endl;
        printVector(v[i]);
       // hybrid_sort1(v[i]);
        printVector(v[i]);
    }
}
void test_hybrid_2(std::vector<std::vector<int> > v)
{
    int length = v.size();
    
    for(int i = 0; i < length; i++){
        std::cout<<"Case " << i << ": "<< std::endl;
        printVector(v[i]);
       // hybrid_sort2(v[i]);
        printVector(v[i]);
    }
}
void test_hybrid_3(std::vector<std::vector<int> > v)
{
    int length = v.size();
    
    for(int i = 0; i < length; i++){
        std::cout<<"Case " << i << ": "<< std::endl;
        printVector(v[i]);
        std::cout << hybrid_sort3(v[i]) << " ";
        printVector(v[i]);
    }
}

void test_shell_1(std::vector<std::vector<int> > v)
{
    int length = v.size();
    
    for(int i = 0; i < length; i++){
        std::cout<<"Case " << i << ": "<< std::endl;
        printVector(v[i]);
       // shell_sort1(v[i]);
        printVector(v[i]);
    }   
}

void test_shell_2(std::vector<std::vector<int> > v)
{
    int length = v.size();
    
    for(int i = 0; i < length; i++){
        std::cout<<"Case " << i << ": "<< std::endl;
        printVector(v[i]);
     //   shell_sort2(v[i]);
        printVector(v[i]);
    }      
}
void test_shell_3(std::vector<std::vector<int> > v){
    int length = v.size();
    
    for(int i = 0; i < length; i++){
        std::cout<<"Case " << i << ": "<< std::endl;
        printVector(v[i]);
     //   shell_sort3(v[i]);
        printVector(v[i]);
    }      
}
void test_shell_4(std::vector<std::vector<int> > v) {
    int length = v.size();
    
    for(int i = 0; i < length; i++){
        std::cout<<"Case " << i << ": "<< std::endl;
        printVector(v[i]);
     //   shell_sort4(v[i]);
        printVector(v[i]);
    }      
}