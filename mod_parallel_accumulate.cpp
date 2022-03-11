#include <thread>
#include <numeric>
#include <iostream>
#include <vector>
#include <chrono>
#include "Timer.h"
#include <fstream>

using namespace std;

template<typename Iterator, typename T>
void accumulate_block(Iterator first, Iterator last, T init, T &result) {
    result = accumulate(first, last, init);
}

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init, unsigned int num_workers=thread::hardware_concurrency()){ //
    // 1. Проверили длину
    auto length = distance(first, last);
    if (length < 4 * thread::hardware_concurrency()) {
        return accumulate(first, last, init);
    }
    // 2. Длина достаточна, распараллеливаем
    //auto num_workers = thread::hardware_concurrency();
    // Вычислили длину для одного потока
    auto length_per_thread = (length + num_workers - 1) / num_workers;
    // Векторы с потоками и результатами
    vector<thread> threads;
    vector<T> results(num_workers - 1);
    // 3. Распределяем данные (концепция полуинтервалов!)
    for (auto i = 0u; i < num_workers - 1; i++) {
        auto beginning = next(first, i * length_per_thread);
        auto ending = next(first, (i + 1) * length_per_thread);
        // 4. Запускаем исполнителей
        threads.push_back(thread(
                accumulate_block<Iterator, T>,
                beginning, ending, 0, ref(results[i])));
    }
    // Остаток данных -- в родительском потоке
    auto main_result = accumulate(next(first, (num_workers - 1) * length_per_thread),
                                  last, init);
    // std::mem_fun_ref -- для оборачивания join().
    for_each(begin(threads), end(threads), mem_fun_ref(&thread::join));
    // 5. Собираем результаты
    return accumulate(begin(results), end(results), main_result);
}

int main() {
    vector<long long> test_sequence(100000u);
    iota(test_sequence.begin(), test_sequence.end(), 0);
    auto timer = Timer<chrono::microseconds>();
    int n=100;
    vector<int> answers(100);
    for(int j=0; j<n; j++){
        for(int i=1; i<=100; i++)
        {
            timer.reset();
            timer.start();
            auto result =
                    parallel_accumulate(begin(test_sequence),
                                        end(test_sequence), 0, i);
            timer.stop();
            answers[i-1]+=timer.get_time();
        }
        cout<<j<<endl;
    }
    ofstream out;
    out.open("../data.txt");
    for_each(answers.begin(), answers.end(), [&out, &n](auto data){out<<data/n<<endl;});
    out.close();

    return 0;
}