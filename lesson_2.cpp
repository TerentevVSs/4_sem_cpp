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
#include <tuple>
using namespace std;
template<typename T, typename... Types>
auto dynamically_construct(Types... args) {
    return new T(args...);
}
struct Date {
    Date(int year, int month, int day): year(year), month(month), day(day) {}
    int year, month, day;
};

bool compare_dates(Date d1, Date d2)
{
    return make_tuple(d1.year, d1.month, d1.day) < make_tuple(d2.year, d2.month, d2.day);
}
int main(){
    Date d1{2020, 12, 3};
    Date d2{2020, 12, 5};
    cout<<boolalpha<<compare_dates(d1, d2);
    Date* date_ptr = dynamically_construct<Date>(2022, 2, 4);
    delete date_ptr;
    return 0;
}
