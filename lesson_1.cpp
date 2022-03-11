#include <deque>
#include <cmath>
#include <chrono>
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
template<typename First_type, typename... Types>
void print(First_type first_type, Types... args){
    cout << first_type << endl;
    print(args...);
}

int main(){
    [[maybe_unused]] double result;
    {
        auto timer = Timer();
        for (auto i = 0u; i < pow(10, 7); i++) {
            sin(i) + cos(i);
        }
    }

    auto a = new int(4);
    a[0]=4;
    cout<<a[0]<<endl;
    //cout<<result;
    print(11,3,"FPMI");
    return 0;
}
