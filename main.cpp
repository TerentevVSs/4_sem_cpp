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


int main(){
    double result;
    {
        auto timer = Timer();
        for (auto i = 0u; i < pow(10, 7); i++) {
            result = sin(i) + cos(i);
        }
    }
    cout<<result;
    return 0;
}
