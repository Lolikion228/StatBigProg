//#include "mainwindow.h"

//#include <QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
//}


#include "chisq.h"
#include <random>
#include "utils.h"
#include "poisgen.h"
#include "poisgen1.h"
#include "poisgen2.h"
#include "mysample.h"
#include "distribution.h"
#include <algorithm>

auto stdgen = new std::mt19937_64(2007);

template <typename T>
void print_arr(T *arr, int N){
    std::cout << "[";
    for(int i=0; i<N; ++i){
        std::cout << arr[i] << " ";
    }
    std::cout << "]\n";
}

int compareInts(const void* a, const void* b) {
    int int_a = *((int*)a);
    int int_b = *((int*)b);

    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

void test_chisq(int N=50, double lambda=10.3){
    PoisGen *curr_gen = new PoisGen1(lambda, stdgen);

    int *X = new int[N];
    get_sample(N, X, curr_gen);
    qsort(X, N, sizeof(int), compareInts);
    MySample *sample = new MySample();
    sample -> set_sample(X, N);
    std::cout << "sample: ";
    print_arr(sample->get_sample(), N);
    std::cout << "\n";

    Distribution d0(lambda);
    ChiSq test(sample, d0);
    std::cout << "df = " << test._df << "\n";
    std::cout << "pval = " << test._pval << "\n";
    std::cout << "statistic = " << test._stat << "\n";
    std::cout << "i  | exp_freqs | obs_freqs\n";
    for(int i=0; i<test._n_states; ++i){
        printf("%2d    %6.3f  %10.3f\n", i, test._exp_freqs[i], test._obs_freqs[i]);
    }

    delete curr_gen;
    delete sample;
}




int main(int argc, char *argv[])
{
    test_chisq();
}




