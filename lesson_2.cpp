#include <list>
#include <forward_list>
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
    list<int> numbers = {1,3,2,42 -325};
    list<int> other_numbers = {25, -1, 30};
    numbers.splice(next(numbers.begin()),
                   other_numbers,
                   other_numbers.begin(),
                   prev(other_numbers.end()));
    numbers.sort(less<>());
    for(auto item: numbers){
        cout << item << ' ';
    }
    cout<<endl;

    numbers.merge(other_numbers);
    copy(numbers.begin(), numbers.end(),
         ostream_iterator<int>(cout, " "));
    cout<<endl;
    return 0;
}