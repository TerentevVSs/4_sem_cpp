#include <thread>
#include <numeric>
#include <iostream>
#include <vector>
#include <mutex>
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


int main() {
    string word = "DGAP";
    lock(lock_cout, other_lock);
    thread other(function_for_thread, "DGAP");
    function_for_main("LPR");
    other.join();
    return 0;
}