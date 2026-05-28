#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


// #include "chisq.h"
// #include <random>
// #include "utils.h"
// #include "poisgen.h"
// #include "poisgen1.h"
// #include "DrawTimeParams.h"
// #include "poisgen2.h"
// #include "distribution.h"
// #include "mod.h"
// #include <algorithm>

// const double GOOD_STEP_SIZE = 0.05;
// const double EPS = 1e-6;
// auto stdgen = new std::mt19937_64(2007);

// template <typename T>
// void print_arr(T *arr, int N){
//    std::cout << "[";
//    for(int i=0; i<N; ++i){
//        std::cout << arr[i] << " ";
//    }
//    std::cout << "]\n";
// }

// int compareInts(const void* a, const void* b) {
//    int int_a = *((int*)a);
//    int int_b = *((int*)b);

//    if (int_a < int_b) return -1;
//    if (int_a > int_b) return 1;
//    return 0;
// }

// void test_chisq(){
//    int N=50;
//    double lambda=10.3;
//    Distribution *d0 = new Distribution(lambda);
//    PoisGen *curr_gen = new PoisGen1(d0, stdgen);

//    curr_gen->gen_sample(N);
//    qsort(curr_gen->_sample, N, sizeof(int), compareInts);
//    std::cout << "sample: ";
//    print_arr(curr_gen->_sample, N);
//    std::cout << "\n";

//    ChiSq test(curr_gen, d0);

//    std::cout << "df = " << test._df << "\n";
//    std::cout << "pval = " << test._pval << "\n";
//    std::cout << "statistic = " << test._stat << "\n";
//    std::cout << "i  | exp_freqs | obs_freqs\n";
//    for(int i=0; i<test._n_states; ++i){
//        printf("%2d    %6.3f  %10.3f\n", i, test._exp_freqs[i], test._obs_freqs[i]);
//    }

//    delete d0;
//    delete curr_gen;
// }


// void test_pecdf(){
//    int main_sample_size = 100;
//    int psample_size = 10000;
//    double lambda_h0 = 10;
//    double lambda_h1 = 10.9;
//    double alpha = 0.35;
//    Distribution *d0 = new Distribution(lambda_h0);
//    Distribution *d1 = new Distribution(lambda_h1);
//    PoisGen *h0_gen = new PoisGen1(d0, stdgen);
//    PoisGen *h1_gen = new PoisGen1(d1, stdgen);

//    double *F0;
//    double *F1;
//    double obs_sgnf_lvl;
//    double obs_pwr;
//    get_pdist(h0_gen, h1_gen, psample_size, main_sample_size, F0, F1, alpha, obs_sgnf_lvl, obs_pwr);

//    int N = 1 / GOOD_STEP_SIZE;
//    std::cout << "val     F0     F1\n";
//    for(int i=0; i<N; ++i){
//        printf("%3.2f  %5.3f  %5.3f\n", GOOD_STEP_SIZE*(i+1), F0[i], F1[i]);
//    }

//    std::cout << "\n";
//    printf("at alpha = %.3f\n", alpha);
//    printf("ERR_1 = %.3f   POW = %.3f\n", obs_sgnf_lvl, obs_pwr);

//    delete d0;
//    delete d1;

// }



// int main(int argc, char *argv[])
// {

//    test_chisq();

//    std::cout << "\n";
//    for(int i=0; i<40; ++i){
//        std::cout << "#";
//    }
//    std::cout << "\n\n";

//    test_pecdf();

// }




