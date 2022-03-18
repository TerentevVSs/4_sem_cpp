#include <thread>
#include <numeric>
#include <iostream>
#include <vector>

using namespace std;

template<typename Iterator, typename T>
void accumulate_block(Iterator first, Iterator last, T init, T &result) {
    result = accumulate(first, last, init);
}

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init, unsigned num_workers=55) {
    // 1. Проверили длину
    auto length = distance(first, last);
    if (length < 4 * num_workers) {
        return accumulate(first, last, init);
    }
    // 2. Длина достаточна, распараллеливаем
    // Вычислили длину для одного потока
    auto length_per_thread = (length + num_workers - 1) / num_workers;
    // Векторы с потоками и результатами
    vector<thread> threads;
    vector<T> results(num_workers - 1);
    // 3. Распределяем данные (концепция полуинтервалов!)
    auto beginning = first;
    auto ending = next(first, length_per_thread);
    for (int i = 0; i < num_workers - 1; i++) {
        beginning = min(next(first, i * length_per_thread), last);
        ending = min(next(first, (i + 1) * length_per_thread), last);
        // 4. Запускаем исполнителей
        threads.push_back(thread(
                accumulate_block<Iterator, T>,
                beginning, ending, 0, ref(results[i])));
    }
    // Остаток данных -- в родительском потоке
    auto main_result = accumulate(min(next(first,
                                           (num_workers - 1) * length_per_thread),
                                      last),
                                  last, init);
    // std::mem_fun_ref -- для оборачивания join().
    for_each(begin(threads),
             end(threads),
             mem_fun_ref(&thread::join));
    // 5. Собираем результаты
    return accumulate(begin(results),
                      end(results),
                      main_result);
}

int main() {
    vector<int> test_sequence(1000);
    iota(test_sequence.begin(), test_sequence.end(), 0);
    auto result =
            parallel_accumulate(begin(test_sequence),
                                end(test_sequence),
                                0);
    cout << "Result is " << result << endl;
}