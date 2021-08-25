For this project, I was using C++11 for my code. I also had an extra file "helper_functions.cpp" in which I implemented a merger function (merge 2 sub vectors) and a printVector function.

Steps to run my program:
1) compile: 
    g++ -std=c++11 -c helper_functions.cpp insertion_sort.cpp merge_sort.cpp hybrid_sort1.cpp hybrid_sort2.cpp hybrid_sort3.cpp shell_sort1.cpp shell_sort2.cpp 
    shell_sort3.cpp shell_sort4.cpp main.cpp
2) link:
    g++ -std=c++11 helper_functions.o insertion_sort.o merge_sort.o hybrid_sort1.o hybrid_sort2.o hybrid_sort3.o shell_sort1.o shell_sort2.o shell_sort3.o
    shell_sort4.o main.o -o run
3) run:
    ./run



