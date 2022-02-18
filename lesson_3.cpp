#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>
#include <map>
#include <string>
#include <numeric>
using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& data){
    out<<"[";
    copy(data.begin(), prev(data.end()), ostream_iterator<T>(out, ", "));
    out<<*prev(data.end())<<"]";
    return out;
}

int main(){
//    vector<int> source = {32,623,236,76};
//    vector<int> dest = {27,832,278,375};
//    copy(source.begin(), source.end(), back_inserter(dest));
//    copy(dest.begin(), dest.end(), ostream_iterator<int>(cout, " "));
    vector<int> seq(10);
    iota(seq.begin(), seq.end(), 66);
    cout<<seq<<endl;
    auto sum = accumulate(seq.begin(), seq.end(), 66);
    auto product = accumulate(seq.begin(), seq.end(),
                              1ll, [](auto lhs, auto rhs){return lhs*rhs;});
    cout<<sum<<endl;
    cout<<product<<endl;
    vector<int> reversed_seq;
    reverse_copy(seq.begin(), seq.end(), back_inserter(reversed_seq));
    cout<<reversed_seq<<endl;
    return 0;
}