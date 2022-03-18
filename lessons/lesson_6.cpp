#include <thread>
#include <numeric>
#include <iostream>
#include <vector>
#include <mutex>
#include <atomic>
using namespace std;


mutex lock_cout;
mutex other_lock;

void function_for_thread(const string& word){
    lock_cout.lock();
    this_thread::sleep_for(chrono::milliseconds(1));
    other_lock.lock();
    cout<<"The "<<"word "<<"is "<<word<<"!"<<endl;
    lock_cout.unlock();
    other_lock.unlock();
}

void function_for_main(const string& word){
    other_lock.lock();
    this_thread::sleep_for(chrono::milliseconds(1));
    lock_cout.lock();
    cout<<"The "<<"word "<<"is "<<word<<"!"<<endl;
    other_lock.unlock();
    lock_cout.unlock();
}
int some_variable=0;
atomic<int> atomic_variable=0;
void function(){
    for(auto i=0; i<300000; i++){
        atomic_variable+=1;
    }
}

int main() {
//    string word = "DGAP";
//    lock(lock_cout, other_lock);
//    thread other(function_for_thread, "DGAP");
//    function_for_main("LPR");
//    other.join();
    thread other(function);
    function();
    other.join();
    cout<<atomic_variable;
    return 0;
}