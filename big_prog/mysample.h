#ifndef MYSAMPLE_H
#define MYSAMPLE_H


class MySample
{
protected:
    int _min_val;
    int _max_val;
    int _range;
    int _sample_size;
    int* _sample;

public:
    void set_sample(int* sample, int sample_size);
    int* get_sample() const;
    int get_min_val() const;
    int get_max_val() const;
    int get_range() const;
    int get_sample_size() const;
    MySample();
    ~MySample();
};

#endif // MYSAMPLE_H
