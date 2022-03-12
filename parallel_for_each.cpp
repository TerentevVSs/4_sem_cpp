#include <future>
#include <numeric>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;


template<typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func func,
                       unsigned int num_workers = 12) {
    // 1. Проверили длину
    auto length = distance(first, last);
    if (length < 4 * num_workers) {
        for_each(first, last, func);
        return;
    }
    // 2. Длина достаточна, распараллеливаем
    // Вычислили длину для одного future
    auto length_per_thread = (length + num_workers - 1) / num_workers;
    // Вектор с future
    vector<future<void>> futures;
    // 3. Распределяем данные
    auto beginning = first;
    auto ending = next(first, length_per_thread);
    for (auto i = 0; i < num_workers - 1; i++) {
        beginning = min(next(first, i * length_per_thread), last);
        ending = min(next(first, (i + 1) * length_per_thread), last);
        futures.push_back(async(launch::async,
                                [beginning, ending, func]() {
                                    for_each(beginning, ending, func);
                                }));
    }
    // Остаток данных - в родительском потоке
    for_each(min(next(first,
                      (num_workers - 1) * length_per_thread),
                 last),
             last, func);
    // mem_fun_ref -- для оборачивания get().
    for_each(begin(futures),
             end(futures),
             mem_fun_ref(&future<void>::get));
}


int main() {
    vector<int> test_sequence(666666);
    iota(test_sequence.begin(), test_sequence.end(), 0);
    parallel_for_each(begin(test_sequence),
                      end(test_sequence),
                      [](auto &data) { data *= data; },
                      42);
    copy(test_sequence.begin(),
         test_sequence.end(),
         ostream_iterator<int>(cout, "\n"));
    return 0;
}