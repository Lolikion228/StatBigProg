#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


//#include "chisq.h"
//#include <random>
//#include "utils.h"
//#include "poisgen.h"
//#include "poisgen1.h"
//#include "DrawTimeParams.h"
//#include "poisgen2.h"
//#include "mysample.h"
//#include "distribution.h"
//#include "mod.h"
//#include <algorithm>

//const double GOOD_STEP_SIZE = 0.05;
//const double EPS = 1e-6;
//auto stdgen = new std::mt19937_64(2007);

//template <typename T>
//void print_arr(T *arr, int N){
//    std::cout << "[";
//    for(int i=0; i<N; ++i){
//        std::cout << arr[i] << " ";
//    }
//    std::cout << "]\n";
//}

//int compareInts(const void* a, const void* b) {
//    int int_a = *((int*)a);
//    int int_b = *((int*)b);

//    if (int_a < int_b) return -1;
//    if (int_a > int_b) return 1;
//    return 0;
//}

//void test_chisq(){
//    int N=50;
//    double lambda=10.3;
//    PoisGen *curr_gen = new PoisGen1(lambda, stdgen);

//    int *X = new int[N];
//    get_sample(N, X, curr_gen);
//    qsort(X, N, sizeof(int), compareInts);
//    MySample *sample = new MySample();
//    sample -> set_sample(X, N);
//    std::cout << "sample: ";
//    print_arr(sample->get_sample(), N);
//    std::cout << "\n";

//    Distribution d0(lambda);
//    ChiSq test(sample, d0);
//    std::cout << "df = " << test._df << "\n";
//    std::cout << "pval = " << test._pval << "\n";
//    std::cout << "statistic = " << test._stat << "\n";
//    std::cout << "i  | exp_freqs | obs_freqs\n";
//    for(int i=0; i<test._n_states; ++i){
//        printf("%2d    %6.3f  %10.3f\n", i, test._exp_freqs[i], test._obs_freqs[i]);
//    }

//    delete curr_gen;
//    delete sample;
//}


//void test_pecdf(){
//    int main_sample_size = 100;
//    int psample_size = 10000;
//    double lambda_h0 = 10;
//    double lambda_h1 = 10.5;
//    double alpha = 0.15;

//    PoisGen *h0_gen = new PoisGen1(lambda_h0, stdgen);
//    PoisGen *h1_gen = new PoisGen1(lambda_h1, stdgen);

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
//    int ix = 0;
//    if(alpha >= GOOD_STEP_SIZE){
//        ix = alpha / GOOD_STEP_SIZE - 1 + EPS;
//    }
//    printf("ERR_1 = %.3f   POW = %.3f\n", F0[ix], F1[ix]);

//}



//int main(int argc, char *argv[])
//{

//    test_chisq();

//    std::cout << "\n";
//    for(int i=0; i<40; ++i){
//        std::cout << "#";
//    }
//    std::cout << "\n\n";

//    test_pecdf();
//}




