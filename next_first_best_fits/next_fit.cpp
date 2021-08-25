#include "project2.h"
#include <cmath>

void next_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
    int length = items.size();
    if (length > 0) {
        int bin = 1;
        double free = 1.00;
        free_space.push_back(free);

        for (int i = 0; i < length; i++) {
            if( (std::fabs(free - items[i]) < 1e-4) || (items[i] < free)) {
               //if(free >= items[i]) {
                assignment[i]=bin;
                free -= items[i];
                free_space[bin-1] = free;
            }
            else {
                free = 1 - items[i];
                free_space.push_back(free);
                bin++;
                assignment[i] = bin;
            }
        }
    } 
}
