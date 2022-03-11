#include <iostream>
#include <thread>
#include <future>
#include <sstream>
#include <utility>

using namespace std;

void print_word(const string &word) {
    cout << "The word is " << word << endl;
}

string return_word(const string &word) {
    cout << "Returning word " + word << endl;
    stringstream ss;
    ss << "The word is " << word << endl;
    return ss.str();
}

class WordHolder {
public:
    explicit WordHolder(string word) : word(std::move(word)) {}

    void print_word() const {
        cout << word << endl;
    }

private:
    string word;
};

void write_word(const string &word, string &out) {
    cout << "word";
    out = word;
}

int main() {
    thread first_thread(print_word, "FIRST");
    thread second_thread(print_word, "SECOND");
    print_word("MAIN");
    first_thread.join();
    second_thread.join();

    future<string> first_future(
            async(launch::async,
                  return_word,
                  "FIRST")); // начать выполнять сразу
    future<string> second_future(
            async(launch::deferred,
                  return_word,
                  "SECOND"));// только в последний момент
    cout << return_word("MAIN");
    cout << first_future.get(); // требуем результат немедленно
    cout << second_future.get();
    string to_write = "WORD";
    string result;
    // ref, cref - передача ссылок
    thread write_thread(write_word, cref(to_write), ref(result));
    write_thread.join();
    cout << result << endl;
    WordHolder holder("HELD");
    thread class_thread(&WordHolder::print_word, ref(holder));
    class_thread.join();
    return 0;
}
