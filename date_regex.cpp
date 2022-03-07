#include <iostream>
#include <iterator>
#include <regex>
#include <vector>


using namespace std;


std::vector<std::string> search(const std::regex& pattern,
                                const std::string& text) {
    auto begin = std::sregex_iterator(std::begin(text),
                                      std::end(text), pattern);
    auto end = std::sregex_iterator();
    std::vector<std::string> results(std::distance(begin, end));
    std::transform(begin, end, std::back_inserter(results), [](auto x){
        return x.str();
    });
    return results;
}
int main(){
    // для удобства дальнейшего использования (которого не будет...) будем искать отдельно даты и отдельно время
    // date - YYYY.MM.DD, год всегда 4 цифры, месяц и день могут быть 1 или 2 цифры
    // time - HH.MM.SS, часы, минуты и скунды могут быть 1 или 2 цифры
    string test_data = " 34.0.12\n"
                       " 0034.03.12\n"
                       " 0034.03.32\n"
                       " 0034.03.22\n"
                       " 0034.03.12\n"
                       " 0034.03.2\n"
                       " 0034.03.02\n"
                       " 034.03.03\n"
                       " 000034.03.15\n"
                       " 0004.03.29\n"
                       " 2.02.26\n"
                       " 2.2.12\n"
                       " 434.11.27\n"
                       " 6233.12.17\n"
                       " .12.23\n"
                       " 65233.12.31\n"
                       " 63.13.12\n"
                       " 23.13.12\n"
                       " 3.1.0\n"
                       " 3.63.12\n"
                       " 25.13.12\n"
                       " 5.59.59\n"
                       " 5.13.12\n";
    regex date_pattern(R"(\D([1-9]{4}|0[1-9]\d{2}|00[1-9]\d{1}|000[0-9])\.(0\d{1}|1[0-2]{1}|[1-9]{1})\.([1-2]\d{1}|30|31|0\d{1}))");
    regex time_pattern(R"(\D([0,1]\d{1}|2[0-3]|\d{1})\.([0-5]\d{1}|\d{1})\.([0-5]\d{1}|\d{1}))");
    auto date_result = search(date_pattern, test_data);
    copy(begin(date_result), end(date_result), ostream_iterator<string>(cout, " "));
    cout<<endl<<endl;
    auto time_result = search(time_pattern,test_data);
    copy(begin(time_result), end(time_result), ostream_iterator<string>(cout, " "));
    return 0;
}