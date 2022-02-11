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


int main(){
    map<string, unsigned> grades;
    grades["Denis"] = 3;
    grades.insert({"Ilya", 5});
    cout<<count_if(grades.begin(), grades.end(), [](auto data){return data.second==5;})<<endl;
    for(const auto& student_grade: grades){
        cout<<student_grade.first<<": "<<student_grade.second<<endl;
    }
    for(const auto& [student, grade]: grades)
        cout << student << ": " << grade << endl;
    return 0;
}