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
using namespace std;

#define RANGE(container) container.begin(), container.end()

int main(){
    vector<int> nums{3,-4,5, 94,-23};
    sort(RANGE(nums), [](auto l, auto r){return l<r;});
    copy(RANGE(nums),ostream_iterator<int>(cout, " "));
    return 0;
}