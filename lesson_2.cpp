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

class Fraction {
public:
    Fraction(int numerator, unsigned denuminator): numerator(numerator), denuminator(denuminator){}
private:
    int numerator;
    unsigned denuminator;
};

int main(){
    deque<Fraction> deq;
    deq.emplace_back(3,5);
    cout<<deq.size();
    return 0;
}