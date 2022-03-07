#include <iostream>
#include <iterator>
#include <regex>
#include <vector>

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

int main() {
    std::regex pattern(R"((\+7|8)\s?(\([498][0-9]{2}\)|[498][0-9]{2})\s?[0-9]{3}(-?[0-9]{2}){2})");
    std::string test_sequence = " +79528888888 \n"
                                " +75528888888 \n"
                                " 88888888888 \n"
                                " 8(888)888-88-88 \n"
                                " +7(888)888-88-88 \n"
                                " 8 (888) 888-88-88 \n"
                                " +7 (888) 888-88-88 \n"
                                " +74528888888 \n"
                                " +7452888-88-88 \n"
                                " +7452888-8888 \n"
                                " 79528888888 \n"
                                " +99528888888 \n";
    auto result = search(pattern, test_sequence);
    std::copy(std::begin(result), std::end(result), std::ostream_iterator<std::string>(std::cout, " "));
    return 0;
}