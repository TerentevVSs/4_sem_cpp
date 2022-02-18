#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>
#include <map>
#include <string>
#include <numeric>
#include <random>
#include <chrono>
#include <deque>
using namespace std;


template<typename T>
ostream& operator<<(ostream& out, const vector<T>& data){
    out<<"[";
    copy(data.begin(), prev(data.end()), ostream_iterator<T>(out, ", "));
    out<<*prev(data.end())<<"]";
    return out;
}
//template<typename T>
//class U<T>{};
//template<typename T, class U<T>>
//ostream& operator<<(ostream& out, const U<T>& data){
//    out<<"[";
//    copy(data.begin(), prev(data.end()), ostream_iterator<T>(out, ", "));
//    out<<*prev(data.end())<<"]";
//    return out;
//}

template<typename T>
ostream& operator<<(ostream& out, const deque<T>& data){
    out<<"[";
    copy(data.begin(), prev(data.end()), ostream_iterator<T>(out, ", "));
    out<<*prev(data.end())<<"]";
    return out;
}

int main(){
    auto seed = chrono::steady_clock::now().time_since_epoch().count();
    auto gen = mt19937(seed);
    auto distributon = uniform_int_distribution(1, 10);
    deque<int> rnd;
    generate_n(front_inserter(rnd), 10,
               [&gen, &distributon](){return distributon(gen);});
    cout<<rnd<<endl;
    auto nth_iter = next(rnd.begin(), 3);
    nth_element(rnd.begin(), nth_iter, rnd.end(), [](auto l, auto r){return l>r;});
    cout<<rnd<<endl;
    return 0;
}