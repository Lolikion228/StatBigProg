#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <cmath>

class Distribution
{
private:
    double _lambda;
public:
    Distribution(double lambda);
    int get_lim(int sample_size, double cum_exp_freq_thresh);
    double get_lambda() const;
    void get_probs(int right_lim, double *p);
    void whoami();
    ~Distribution();
};

#endif // DISTRIBUTION_H
