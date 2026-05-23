#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <cmath>

class Distribution
{
private:
    double _lambda;
public:
    Distribution(double lambda);
    double get_lambda() const;
    void get_probs(int right_lim, double *p) const;
    const char* whoami() const;
    ~Distribution();
};

#endif // DISTRIBUTION_H
