#include <thread>
#include <iostream>
#include <stack>
#include <mutex>

using namespace std;

template<typename T>
class ThreadSafeStack{
public:
    ThreadSafeStack(): st(){};
    void push(T elem){
        lock_guard guard(m);
        st.push(elem);
    }
    T top(){
        lock_guard guard(m);
        return st.top();
    }
    void pop(){
        lock_guard guard(m);
        st.pop();
    }
    size_t size(){
        lock_guard guard(m);
        return st.size();
    }
private:
    stack<T> st;
    mutex m;
};

void push_n_times(ThreadSafeStack<int>& st, int n){
    for(auto i=0; i<n; i++){
        st.push(1);
    }
}

int main() {
    ThreadSafeStack<int> st;
    for(auto i=0; i<30000; i++){
        st.push(i);
    }
    thread t(push_n_times, ref(st), 30000);
    for(auto i=0; i<30000; i++){
        st.pop();
    }
    t.join();
    cout<<st.size();
    return 0;
}