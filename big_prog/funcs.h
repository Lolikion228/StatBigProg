#ifndef FUNCS_H
#define FUNCS_H

#include <cmath>
#include <iostream>
#include "distribution.h"



/*
X: sample
p: vector of probs
N: size of p
*/


template <typename T>
void print_arr(T x, int n){
    std::cout << "[" ;
    for(int i=0; i<n; ++i){
        std::cout << x[i] << " ";
    }
    std::cout << "]\n";
}

#endif // FUNCS_H
