#include <thread>
#include <iostream>
#include <queue>
#include <mutex>

using namespace std;

template<typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue() : q() {};

    void push(T elem) {
        lock_guard guard(m);
        q.push(elem);
    }

    T &front() {
        lock_guard guard(m);
        return q.front();
    }

    T &back() {
        lock_guard guard(m);
        return q.back();
    }

    void pop() {
        lock_guard guard(m);
        q.pop();
    }

    bool empty() {
        lock_guard guard(m);
        return q.empty();
    }

    size_t size() {
        lock_guard guard(m);
        return q.size();
    }

private:
    queue<T> q;
    mutex m;
};

void push_n_times(ThreadSafeQueue<int> &q, int n) {
    for (auto i = 0; i < n; i++) {
        q.push(1);
    }
}

int main() {
    ThreadSafeQueue<int> q;
    for (auto i = 0; i < 30000; i++) {
        q.push(i);
    }
    thread t(push_n_times, ref(q), 30000);
    for (auto i = 0; i < 30000; i++) {
        q.pop();
    }
    t.join();
    cout << q.size() << endl;
    cout << boolalpha << q.empty() << endl;
    cout << q.front() << endl;
    cout << q.back() << endl;
    return 0;
}