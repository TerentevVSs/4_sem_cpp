#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <map>
#include <string>


using namespace std;


ostream& operator << (ostream& out, map<string, string>& data){
    for(auto const&[name, phone]: data){
        out<<name<<" "<<phone<<endl;
    }
    return out;
}

class User{
private:
    string name;
    string number;
public:
    User()=default;
    explicit User(string name): name(std::move(std::move(name))){};
    User(string name, string number): name(std::move(std::move(name))), number(std::move(std::move(number))){};
    string get_name(){
        return name;
    }
    string get_number(){
        return number;
    }
};

ostream& operator << (ostream& out, User user){
    out<<user.get_name()<<" "<<user.get_number();
    return out;
}


class PhoneDirectory{
private:
    vector<string> names;
    map<string, string> data;
    [[nodiscard]] string generate_name() const{
        unsigned id = rand();
        id = id%names.size();
        return names[id];
    }
public:
    PhoneDirectory(){
        srand(unsigned(time(nullptr)));
    };
    void add_pearson(const string& name, const string& number){
        data.insert({name, number});
        names.push_back(name);
    }
    [[nodiscard]] string get_random_number() const{
        string name = generate_name();
        auto number_pair= data.find(name);
        if (number_pair==data.end()){
            cerr << "You tried to get number of random user. Something went wrong!" << endl;
            return "0";
        } else{
            return number_pair->second;
        }
    }
    [[nodiscard]] User get_random_user() const{
        string name = generate_name();
        auto number_pair= data.find(name);
        if (number_pair==data.end()){
            cerr << "You tried to get number of random user. Something went wrong!" << endl;
            return User();
        } else{
            return User(name, number_pair->second);
        }
    }
    [[nodiscard]] string get_current_number(const string& name) const{
        auto number_pair = data.find(name);
        if (number_pair==data.end()){
            cerr << "You tried to get number of " << name << ". No such user!"<< endl;
            return "0";
        } else{
            return number_pair->second;
        }
    }
    [[nodiscard]] const map<string, string>& get_all_data() const{
        return data;
    }
};


int main(){
    PhoneDirectory dataset = PhoneDirectory();
    dataset.add_pearson("Vasya", "2326");
    dataset.add_pearson("Vova", "666404");
    dataset.add_pearson("Ivan", "94363");
    dataset.add_pearson("Ilya", "9373");
    dataset.add_pearson("Peter", "37343");
    cout<<"Vova number: "<<dataset.get_current_number("Vova")<<endl;
    cout<<"Anon number: "<<dataset.get_current_number("Anon")<<endl;
    cout<<"Random number: "<<dataset.get_random_number()<<endl;
    cout<<"Random user: "<<dataset.get_random_user()<<endl;
    auto all_data = dataset.get_all_data();
    cout<<endl<<"All data:"<<endl<<all_data;
    return 0;
}