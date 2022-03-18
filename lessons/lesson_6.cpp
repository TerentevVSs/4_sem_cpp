#include <thread>
#include <numeric>
#include <iostream>
#include <vector>
#include <mutex>
#include <atomic>

using namespace std;


mutex lock_cout;
mutex other_lock;
template<typename Mutex>
class RAIILockWrapper{
public:
    RAIILockWrapper(Mutex& given): m(given){
        m.lock();
    }
    ~RAIILockWrapper(){
        m.unlock();
    }
private:
    Mutex& m;
};
mutex m;
void print_word(const string& word) {
    lock_guard wrapper(m);
    cout<< "ABC "<<"DEF "<<word<<" s else ";
};


int main() {
    string word = "DGAP";
    thread other(print_word, "DGAP");
    print_word("LPR");
    other.join();
    return 0;
}