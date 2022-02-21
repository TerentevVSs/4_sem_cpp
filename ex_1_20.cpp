#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>
#include <map>
#include <string>
#include <numeric>
#include <random>
#include <chrono>
#include <deque>
using namespace std;

template<typename T>
ostream& operator << (ostream& out, vector<T> data){
    for(int i=0; i<data.size(); i++){
        out<<data[i]<<" ";
    }
    out<<endl;
    return out;
}

int main(){
    vector<int> p1(10);
    // 1. sequence
    iota(p1.begin(), p1.end(), 1);
    cout<<"1. "<<p1;
    // 2. cin add
    for(int i=0; i<3; i++)
    {
        int ad;
        //cin>>ad;
        p1.push_back(i+1);
    }
    cout<<"2. "<<p1;
    // 3. random shuffle
    auto seed = chrono::steady_clock::now().time_since_epoch().count();
    shuffle(p1.begin(), p1.end(), mt19937(seed));
    cout<<"3. "<<p1;
    // 4. delete duplicates
    sort(p1.begin(), p1.end());
    p1.erase(unique(p1.begin(), p1.end()), p1.end());
    cout<<"4. "<<p1;
    // 5. count odd numbers
    cout<<"5. Count odd = "<<count_if(p1.begin(), p1.end(), [](auto a){return a%2==1;})<<endl;
    // 6. min, max
    cout<<"6. Min = "<<*min_element(p1.begin(), p1.end())<<" "
    <<"Max = "<<*max_element(p1.begin(), p1.end())<<endl;
    // 7. odd in p1 (the most dummy search)
    vector<int> odd_p1;
    copy_if(p1.begin(), p1.end(), back_inserter(odd_p1), [](auto a){
                                    bool flag = true;
                                    for(int i=2; i<a; i++){
                                        if (a%i==0) flag = false;
                                    }
                                    return flag;});
    cout<<"7. Odd in p1: "<<odd_p1;
    // 8. p1 to p1^2
    transform(p1.begin(), p1.end(), p1.begin(), [](auto a){return a*a;});
    cout<<"8. "<<p1;
    // 9. random p2 with size of p1
    vector<int> p2;
    generate_n(back_inserter(p2), p1.size(), mt19937(seed));
    cout<<"9. "<<p2;
    // 10. sum of p2
    cout<<"10. Sum of p2 = "<< accumulate(p2.begin(), p2.end(), 0) <<endl;
    // 11. some numbers in p2 to 1
    transform(p2.begin(), next(p2.begin(),3), p2.begin(), [](auto a){return 1;});
    cout<<"11. "<<p2;
    // 12. p3 = p1-p2
    vector<int> p3;
    transform(p1.begin(), p1.end(), p2.begin(),
              back_inserter(p3), [](auto lhs, auto rhs){return lhs-rhs;});
    cout<<"12. "<<p3;
    // 13. p3: max(0, elem)
    transform(p3.begin(), p3.end(),p3.begin(), [](auto a){return max(0, a);});
    cout<<"13. "<<p3;
    // 14. remove 0 from p3
    p3.erase(remove_if(p3.begin(), p3.end(),  [](auto a){return a==0;}), p3.end());
    cout<<"14. "<<p3;
    // 15. reverse p3
    reverse(p3.begin(), p3.end());
    cout<<"15. "<<p3;
    // 16. top 3 of p3
    partial_sort(p3.begin(), p3.begin()+3, p3.end(), greater<>());
    cout<<"16. ";
    copy(p3.begin(), p3.begin()+3, ostream_iterator<int>(cout, " "));
    cout<<endl;
    // 17. sort p1, p2
    sort(p1.begin(), p1.end());
    sort(p2.begin(), p2.end());
    cout<<"17. p1 = "<<p1;
    cout<<"17. p2 = "<<p2;
    // 18. merge p1 and p2 to p4
    vector<int> p4;
    merge(p1.begin(), p1.end(), p2.begin(), p2.end(), back_inserter(p4));
    cout<<"18. "<<p4;
    // 19. range of equal 1 in p4
    auto start = lower_bound(p4.begin(), p4.end(), 1);
    auto end = upper_bound(p4.begin(), p4.end(), 1);
    cout<<"19. Lower bound = "<<start-p4.begin()<<"; Upper bound = "<<end-p4.begin()<<endl;
    // 20. print all
    cout<<"20. p1 = "<<p1;
    cout<<"20. p2 = "<<p2;
    cout<<"20. p3 = "<<p3;
    cout<<"20. p4 = "<<p4;
    return 0;
}