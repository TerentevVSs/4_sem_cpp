#include <fstream>
#include <random>
#include <algorithm>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <unordered_set>
#include <iterator>
#include <optional>
#include <thread>
#include <mutex>
#include <set>
#include <vector>
#include <cmath>
#include <chrono>
#include <iostream>
using namespace std;


int main(){
    vector<int> numbers;
    for (auto i=0; i<300; i++){
        numbers.push_back(i);
        cout<<numbers.size()<<" "<<numbers.capacity()<<endl;
    }
    return 0;
}