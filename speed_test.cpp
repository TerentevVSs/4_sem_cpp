#include <iostream>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <cmath>
#include <chrono>
#include "Timer.h"


using namespace std;

int main(){

    srand(unsigned(time(nullptr)));
    const int N=2000000;
    array<int, N> ar;
    vector<int> vec(N);
    deque<int> deq(N);
    list<int> li(N);
    forward_list<int> f_li(N);
    generate(ar.begin(), ar.end(), rand);
    generate(vec.begin(), vec.end(), rand);
    generate(deq.begin(), deq.end(), rand);
    generate(li.begin(), li.end(), rand);
    generate(f_li.begin(), f_li.end(), rand);
    {
        auto timer = Timer<chrono::milliseconds>();
        timer.start();
        sort(ar.begin(), ar.end());
        timer.stop();
        cout<<"Array: ";
    }
    {
        auto timer = Timer<chrono::milliseconds>();
        timer.start();
        sort(vec.begin(), vec.end());
        timer.stop();
        cout<<"Vector: ";
    }
    {
        auto timer = Timer<chrono::milliseconds>();
        timer.start();
        sort(deq.begin(), deq.end());
        timer.stop();
        cout<<"Deque: ";
    }
    {
        auto timer = Timer<chrono::milliseconds>();
        timer.start();
        li.sort();
        timer.stop();
        cout<<"List: ";
    }
    {
        auto timer = Timer<chrono::milliseconds>();
        timer.start();
        f_li.sort();
        timer.stop();
        cout<<"Forward list: ";
    }
    return 0;
}