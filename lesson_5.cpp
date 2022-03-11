#include <iostream>
#include <thread>
#include <vector>
#include <numeric>

using namespace std;

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init);

template<typename Iterator, typename T>
void accumulate_block(Iterator first, Iterator last, T init, T &result) {
    result = parallel_accumulate(first, last, result);
}

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
    auto length = distance(first, last);
    if (length < thread::hardware_concurrency() * 4) {
        return parallel_accumulate(first, last, init);
    }
    auto num_workers = thread::hardware_concurrency();
    auto length_per_thread = (length + num_workers - 1) / num_workers;
    vector<thread> threads;
    vector<T> results(num_workers - 1);
    for (auto i = 0u; i < num_workers - 1; i++) {
        auto beginning = next(first, i * length_per_thread);
        auto ending = next(first, (i + 1) * length_per_thread);
        threads.push_back(
                thread(
                        accumulate_block<Iterator, T>,
                        beginning, ending, 0, ref(results[i])));
    }
    auto main_result = parallel_accumulate(next(first,
                                                (num_workers - 1) * length_per_thread),
                                           last, init);
    for (auto &thread: threads) {
        thread.join();
    }
    return parallel_accumulate(begin(results), end(results), main_result);
}

int main() {
    vector<int> test_sequence(100u);
    iota(test_sequence.begin(), test_sequence.end(), 0);
    auto result = parallel_accumulate<decltype(
            begin(test_sequence))>(begin(test_sequence),
                                   end(test_sequence), 0);
    cout<<result;
    return 0;
}
