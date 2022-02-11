#include <fstream>
#include <random>
#include <algorithm>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <iterator>
#include <optional>
#include <thread>
#include <mutex>
#include <set>
#include <vector>
#include <cmath>
#include <chrono>
#include <iostream>
#include <iomanip>
using namespace std;


int main(){
    multimap<int, string> groups;
    groups.emplace(831, "Nikita");
    groups.insert({831, "Victor"});
    groups.insert({831, "Alex"});
    groups.insert({002, "Johnny"});
    groups.insert({002, "Valery"});
    groups.insert({001, "Pyotr"});

    for(const auto& [group, student]: groups)
        cout << setw(3) << setfill('0') <<
        group << ": " << setw(10) << setfill(' ') << student << endl;
    auto [left, right]= groups.equal_range(831);
    while(left!=right){
        cout<<left->second<<endl;
        left++;
    }
    return 0;
}
