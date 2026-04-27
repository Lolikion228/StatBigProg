#include "utils.h"

void get_sample(int N, int *X, PoisGen* absgen){
    for(int i=0; i<N; ++i){
        X[i] = absgen->gen();
    }
}
