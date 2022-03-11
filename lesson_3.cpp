#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>
#include <string>
#include <deque>
using namespace std;


template<typename T>
ostream& operator<<(ostream& out, const vector<T>& data){
    out<<"[";
    copy(data.begin(), prev(data.end()), ostream_iterator<T>(out, ", "));
    out<<*prev(data.end())<<"]";
    return out;
}

template<typename T>
ostream& operator<<(ostream& out, const deque<T>& data){
    out<<"[";
    copy(data.begin(), prev(data.end()), ostream_iterator<T>(out, ", "));
    out<<*prev(data.end())<<"]";
    return out;
}

#define range(cont) begin(cont), end(cont)
int main(){
    vector<int> numbers = {1,1,4,2,4,6,3,1,5,3};
    cout<<numbers<<endl;
    auto to_delete = unique(numbers.begin(), numbers.end());
    numbers.erase(to_delete, numbers.end());
    cout<<numbers<<endl;
    vector<int> copied;
    copy_if(range(numbers), back_inserter(copied), [](auto elem){return elem>4;});
    cout<<copied;
    return 0;
}