#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <cmath>

class Distribution
{
private:
    double _lambda;
public:
    double *_computed_probs;
    double *_computed_cumsums;
    int _n_computed;
    int _capacity;

    Distribution(double lambda);
    Distribution(const Distribution& other);
    Distribution(Distribution&& other);
    Distribution& operator=(const Distribution& other);
    ~Distribution();

    double get_lambda() const;
    void update_probs(int compute_up_to);
    void get_probs(int right_lim, double *p);
    const char* whoami() const;
};

#endif // DISTRIBUTION_H
