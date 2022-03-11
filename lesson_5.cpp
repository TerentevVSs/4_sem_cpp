#include <iostream>
#include <thread>
#include <future>
#include <sstream>
using namespace std;

void print_word(const string& word) {
    cout << "The word is " << word << endl;
}

string return_word(const string& word) {
    cout<< "Returning word "+word<<endl;
    stringstream ss;
    ss << "The word is " << word << endl;
    return ss.str();
}


int main(){
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
    cout<<return_word("MAIN");
    cout<<first_future.get(); // требуем результат немедленно
    cout<<second_future.get();
    return 0;
}
