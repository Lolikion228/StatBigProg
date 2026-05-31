#include "poisgen1.h"


int PoisGenInvFunc::gen(){
    int k = 0;

    double alpha = _stdgen->operator()() / (double)std::numeric_limits<uint64_t>::max();

    while(alpha > _dist->_computed_cumsums[k]){
        ++k;
        if(k>=_dist->_n_computed){
            _dist->update_probs(2*k+2);
        }
    }

    return k;
}
