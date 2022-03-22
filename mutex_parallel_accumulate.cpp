#include <thread>
#include <numeric>
#include <iostream>
#include <vector>
#include <mutex>

using namespace std;


template<typename Iterator, typename T>
void accumulate_block(Iterator first, Iterator last, T& init, mutex& m) {
    auto result = accumulate(first, last, 0);
    m.lock();
    init += result;
    m.unlock();
}

template<typename Iterator, typename T>
void parallel_accumulate(Iterator first, Iterator last, T& init,
                      unsigned int num_workers = thread::hardware_concurrency()) {
    // 1. Проверили длину
    mutex m;
    auto length = distance(first, last);
    if (length < 4 * num_workers) {
        init = accumulate(first, last, init);
    }
    // 2. Длина достаточна, распараллеливаем
    // Вычислили длину для одного потока
    auto length_per_thread = (length + num_workers - 1) / num_workers;
    // Векторы с потоками и результатами
    vector<thread> threads;

    // 3. Распределяем данные (концепция полуинтервалов!)
    auto beginning = first;
    auto ending = next(first, length_per_thread);
    for (auto i = 0; i < num_workers - 1; i++) {
        beginning = min(next(first, i * length_per_thread), last);
        ending = min(next(first, (i + 1) * length_per_thread), last);
        // 4. Запускаем исполнителей
        threads.push_back(thread(
                accumulate_block<Iterator, T>,
                beginning, ending, ref(init), ref(m)));
    }
    // Остаток данных - в родительском потоке
    auto result = accumulate(min(next(first,
                               (num_workers - 1) * length_per_thread),
                          last), last, 0);
    m.lock();
    init += result;
    m.unlock();
    // std::mem_fun_ref - для оборачивания join().
    for_each(begin(threads), end(threads), mem_fun_ref(&thread::join));
}

int main() {
    vector<long long> test_sequence(666);
    iota(test_sequence.begin(), test_sequence.end(), 0);
    int sum=0;
    parallel_accumulate(begin(test_sequence),
                        end(test_sequence), sum, 42);
    cout<<sum<<endl;
    return 0;
}