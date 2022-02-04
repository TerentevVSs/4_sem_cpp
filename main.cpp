#include <fstream>
#include <random>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <unordered_set>
#include <iterator>
#include <optional>
#include <thread>
#include <mutex>
#include <cmath>
#include <set>
#include <vector>
#include <iostream>
using namespace std;


class Timer{
public:
    Timer(): start(chrono::steady_clock::now()){
    }
    ~Timer(){
        cout<<"Time in microseconds: "<<chrono::duration_cast<chrono::microseconds>(
                chrono::steady_clock::now() - start).count()<<endl;
    }
private:
    chrono::steady_clock::time_point start;
    chrono::steady_clock::time_point end;
};


template<typename Type>
void print(Type arg){
    cout<<arg<<endl;
}
template<typename Firstype, typename... Types>
void print(Firstype firstype, Types... args){
    cout << firstype<< endl;
    print(args...);
}

int main(){
    double result;
    {
        auto timer = Timer();
        for (auto i = 0u; i < pow(10, 7); i++) {
            result = sin(i) + cos(i);
        }
    }

    auto a = new int(4);
    a[0]=4;
    cout<<0[a]<<endl;
    //cout<<result;
    print(11,3,"FPMI");
    return 0;
}
