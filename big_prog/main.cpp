

/**
 * @mainpage Большая программа
 *
 * # Общее описание проекта
 * Данный программный комплекс предназначен для численного моделирования случайных величин,
 * распределенных по закону Пуассона, и последующего статистического анализа качества генерации,
 * мощности статистических критериев, а также вычислительной эффективности алгоритмов.
 *
* # Примеры использования компонентов (Быстрый старт)
 *
 * Здесь представлены готовые примеры использования ключевых классов вашей системы.
 * Код автоматически подтягивается из тестовых сценариев проекта.
 *
 * ## 1. Проверка выборки критерием Хи-квадрат Пирсона
 * В данном примере создается теоретическое распределение Пуассона, генерируется выборка
 * с помощью инверсного метода (`PoisGenInvFunc`) и вычисляются частоты вместе со значением p-value.
 *
 * @snippet main.cpp Chisq_Example
 *
 * ## 2. Моделирование распределений p-value (Критерий H0 vs H1)
 * Пример демонстрирует применение функции `get_pdist` для генерации векторов эмпирических функций
 * распределения статистик под воздействием верной нулевой и альтернативной гипотез.
 *
 * @snippet main.cpp Pecdf_Example
 *
 * ## 3. Управление кэшем распределения и генератор Кнута (PoisGenKnuth)
 * Показывает, как работает динамический дорасчет табличных вероятностей в классе `Distribution`,
 * а также прямое извлечение случайных чисел через переопределенный метод Кнута.
 *
 * @snippet main.cpp Knuth_Cache_Example
 *
 * ## 4. Проведение нагрузочных тестов времени выполнения
 * Использование класса `DrawTimeParams` для автоматического замера скорости генерации больших объемов
 * данных при изменении параметра интенсивности \f$\lambda\f$.
 *
 * @snippet main.cpp Performance_Example
 *
 *
 * Графический интерфейс разработан на базе фреймворка Qt и предоставляет пользователю
 * мощные инструменты для визуализации результатов.
 *
 * ---
 *
 * # Функциональные возможности программы
 *
 * @section gen_sec 1. Моделирование пуассоновских выборок двумя методами
 * Программа позволяет генерировать псевдослучайные последовательности с заданным параметром
 * интенсивности \f$\lambda\f$ двумя принципиально разными путями:
 * - **Метод обратной функции** (реализован в классе PoisGenInvFunc) —
 * моделирование через последовательное суммирование вероятностей и сравнение с CDF.
 * - **Алгоритм Кнута** (реализован в классе PoisGenKnuth) — моделирование на основе
 * подсчета числа событий в простейшем потоке через произведение равномерных случайных величин.
 *
 * @section stat_sec 2. Статистический анализ критерием Хи-квадрат Пирсона
 * Для проверки гипотезы о соответствии сгенерированной выборки теоретическому закону Пуассона
 * в программе реализован класс ChiSq, выполняющий:
 * - Автоматическое вычисление и кэширование теоретических вероятностей (класс Distribution).
 * - Группировку малочисленных смежных интервалов по правилу \f$n \cdot p_i \ge 5.0\f$
 * для обеспечения корректности аппроксимации.
 * - Расчет эмпирического значения статистики \f$\chi^2\f$, числа степеней свободы \f$df\f$ и значения @f$p\text{-value}@f$.
 * - Построение интерактивных **гистограмм частот**, наглядно сопоставляющих наблюдаемые
 * (эмпирические) и ожидаемые (теоретические) частоты попадания в интервалы.
 *
 * @section pval_sec 3. Исследование распределения p-value и мощности критерия
 * Программа предоставляет мощный функционал для визуализации и анализа поведения статистического критерия:
 * - Построение графиков **эмпирической функции распределения p-value** при справедливости
 * нулевой гипотезы \f$H_0\f$ (параметры генератора и гипотезы совпадают). При этом график
 * автоматически сопоставляется с эталонной функцией \f$F(x) = x\f$, так как при \f$H_0\f$
 * величина @f$p\text{-value}@f$ должна быть распределена равномерно на отрезке \f$[0, 1]\f$.
 * - Построение графиков распределения @f$p\text{-value}@f$ при альтернативной гипотезе \f$H_1\f$
 * (когда реальная интенсивность генератора отличается от гипотетической). Это позволяет
 * визуально оценить и рассчитать **мощность критерия** при заданном уровне значимости \f$\alpha\f$.
 *
 * @section perf_sec 4. Анализ вычислительной эффективности (Зависимость времени от лямбда)
 * Программа осуществляет автоматическое нагрузочное тестирование и сравнение быстродействия алгоритмов
 * (класс DrawTimeParams):
 * - Измеряется чистое время генерации массивов больших объемов в миллисекундах.
 * - Строятся **графики зависимости времени моделирования от параметра \f$\lambda\f$** одновременно
 * для обоих методов.
 *
 * ---
 *
 * @section arch_sec Архитектура данных
 * Программа построена по принципу Document-Interface:
 * - **Модель данных** сосредоточена в классе Document, который централизованно владеет
 * всеми наборами параметров вычислений (`HistGenParams`, `PDistGenParams`, `DrawTimeParams`).
 * - **Визуализация** осуществляется через специализированный виджет интерфейса `BasicView`,
 * отвечающий за отрисовку координатных сеток, осей, гистограмм и графиков на основе накопленных в модели данных.
 *
 * @note some note here
 */


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
//     //! [Chisq_Example]
//     int N=50;
//     double lambda=10.3;

//     // 1. Создаем теоретическое распределение Пуассона
//     Distribution *d0 = new Distribution(lambda);

//     // 2. Инициализируем генератор с методом обратной ф-ии
//     PoisGen *curr_gen = new PoisGenInvFunc(d0, stdgen);

//     // 3. Моделируем случайную выборку объема N
//    curr_gen->gen_sample(N);

//     // Сортируем для наглядности
//    qsort(curr_gen->_sample, N, sizeof(int), compareInts);
//    std::cout << "sample: ";
//    print_arr(curr_gen->_sample, N);
//    std::cout << "\n";

//    // 4. Проводим анализ критерием Хи-квадрат Пирсона
//    ChiSq test(curr_gen, d0);

//    // 5. Выводим результаты
//    std::cout << "df = " << test._df << "\n";
//    std::cout << "pval = " << test._pval << "\n";
//    std::cout << "statistic = " << test._stat << "\n";
//    std::cout << "i  | exp_freqs | obs_freqs\n";
//    for(int i=0; i<test._n_states; ++i){
//        printf("%2d    %6.3f  %10.3f\n", i, test._exp_freqs[i], test._obs_freqs[i]);
//    }

//    delete d0;
//    delete curr_gen;
//    //! [Chisq_Example]
// }


// void test_pecdf(){
//     //! [Pecdf_Example]
//    int main_sample_size = 100;
//    int psample_size = 10000;
//    double lambda_h0 = 10;
//    double lambda_h1 = 10.9;
//    double alpha = 0.35;

//    Distribution *d0 = new Distribution(lambda_h0);
//    Distribution *d1 = new Distribution(lambda_h1);
//    PoisGen *h0_gen = new PoisGenInvFunc(d0, stdgen);
//    PoisGen *h1_gen = new PoisGenInvFunc(d1, stdgen);

//    double *F0 = nullptr;
//    double *F1 = nullptr;
//    double obs_sgnf_lvl;
//    double obs_pwr;

//    // Функция расчета эмпирической функции распределения p-value при H0 и H1
//  // TODO   // поменять местами арги
//      // вынести выделение памяти из ф-ии
//    get_pdist(F0, F1, h0_gen, h1_gen, psample_size, main_sample_size, alpha, obs_sgnf_lvl, obs_pwr);

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
//    delete h0_gen;
//    delete h1_gen;
//    delete F0;
//    delete F1;
//    //! [Pecdf_Example]
// }

// void test_distribution_and_knuth(){
//     //! [Knuth_Cache_Example]
//     double lambda = 4.0;
//     Distribution dist(lambda);

//     // Демонстрация работы с кэшем вероятностей класса Distribution
//     std::cout << "Initial capacity: " << dist._capacity << "\n";
//     std::cout << "Initial computed elements: " << dist._n_computed << "\n";

//     // Запрашиваем расчет вероятностей до 20-го состояния
//     dist.update_probs(20);
//     std::cout << "Capacity after update: " << dist._capacity << "\n";
//     std::cout << "Computed elements after update: " << dist._n_computed << "\n";

//     // Выведем первые несколько теоретических вероятностей P(X = k)
//     std::cout << "Theoretical PMF: ";
//     print_arr(dist._computed_probs, 5);

//     // Инициализируем второй генератор (Алгоритм Кнута)
//     PoisGenKnuth knuth_gen(&dist, stdgen);

//     // Генерируем 10 единичных значений методом gen() напрямую
//     std::cout << "Direct gen() calls (Knuth): ";
//     for(int i = 0; i < 10; ++i) {
//         std::cout << knuth_gen.gen() << " ";
//     }
//     std::cout << "\n";

//     // Генерируем выборку и смотрим зафиксированные экстремумы
//     std::cout << "generating the whole sample: ";
//     knuth_gen.gen_sample(10);
//     print_arr(knuth_gen._sample,10);
//     std::cout << "Sample statistics -> Min: " << knuth_gen._min_val
//               << ", Max: " << knuth_gen._max_val << "\n";
//     //! [Knuth_Cache_Example]
// }


// void test_performance_params(){
//     //! [Performance_Example]
//     // Создаем объект параметров замера времени от лямбда
//     DrawTimeParams time_params(stdgen);

//     time_params.lambda_min = 1.0;
//     time_params.lambda_max = 20.0;
//     time_params.cnt_steps = 5; // Сделаем 5 шагов по лямбде
//     time_params.sample_size = 50000; // Объем выборки на каждом шаге

//     std::cout << "Running performance test for PoisGenInvFunc and PoisGenKnuth...\n";
//     // Функция выполняет внутренний цикл замеров времени
//     time_params.update_dur();

//     int steps = static_cast<int>(time_params.cnt_steps) + 1;
//     std::cout << "Steps | Lambda | PoisGenInvFunc (ms) | PoisGenKnuth (ms)\n";
//     for(int i = 0; i < steps; ++i) {
//         double current_lambda = time_params.lambda_min +
//                                 (double(i) / time_params.cnt_steps) * (time_params.lambda_max - time_params.lambda_min);

//         printf("%5d | %6.2f | %13lld | %13lld\n",
//                i, current_lambda,
//                time_params.dur1[i].count(),
//                time_params.dur2[i].count());
//     }
//     //! [Performance_Example]
// }

// int main(int argc, char *argv[])
// {
//     std::cout << "--- TEST CHISQ ---\n";
//     test_chisq();

//     std::cout << "\n" << std::string(40, '#') << "\n\n";

//     std::cout << "--- TEST PECDF ---\n";
//     test_pecdf();

//     std::cout << "\n" << std::string(40, '#') << "\n\n";

//     std::cout << "--- TEST KNUTH & CACHE ---\n";
//     test_distribution_and_knuth();

//     std::cout << "\n" << std::string(40, '#') << "\n\n";

//     std::cout << "--- TEST PERFORMANCE PARAMS ---\n";
//     test_performance_params();

//     delete stdgen;
//     return 0;
// }




