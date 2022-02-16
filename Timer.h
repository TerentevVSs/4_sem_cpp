#include <cmath>
#include <chrono>
#include <iostream>
#include <map>
#include <string>
using namespace std;

template<typename T>
class Timer{
private:
    float duration;
    bool active;
    chrono::steady_clock::time_point start_time;
    chrono::steady_clock::time_point end_time;
    map<string, string> typenames;
public:
    Timer(): duration(0), active(false){
        typenames[typeid(chrono::nanoseconds).name()]="nanoseconds";
        typenames[typeid(chrono::microseconds).name()]="microseconds";
        typenames[typeid(chrono::milliseconds).name()]="milliseconds";
        typenames[typeid(chrono::seconds).name()]="seconds";
        typenames[typeid(chrono::minutes).name()]="minutes";
        typenames[typeid(chrono::hours).name()]="hours";
    }
    ~Timer(){
        cout<<"Timer died! Time in "<<typenames[typeid(T).name()]<< ": " <<duration<<endl;
    }
    void start(){
        if (active==false) {
            start_time = chrono::steady_clock::now();
            active=true;
        }
        else{
            cerr<<"Timer was already started!"<<endl;
        }
    }
    void stop(){
        if (active==true) {
            end_time = chrono::steady_clock::now();
            active=false;
            duration += chrono::duration_cast<T>(end_time - start_time).count();
        }
        else{
            cerr<<"Timer was already stopped!"<<endl;
        }
    }
    float get_time() const{
        return duration;
    }
    void print_time() const{
        cout<<"Time in "<<typenames.at(typeid(T).name())<< ": " <<duration<<endl;
    }
    void reset(){
        duration=0;
    }
};
