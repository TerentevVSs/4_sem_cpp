#include <iostream>
#include <fstream>
#include "json.hpp"
#include <filesystem>
#include <vector>
#include <string>


using namespace std;
using nlohmann::json;

struct Date{
    Date(): month("Not Found"), day(0), year(0){};
    Date(string month, int day, int year): month(month), day(day), year(year) {};
    string month;
    int day;
    int year;
    json to_json(){
        json data_json;
        data_json["Month"] = this->month;
        data_json["Day"] = this->day;
        data_json["Year"] = this->year;
        return data_json;
    }
};


istream& operator >> (istream& in, Date& date){
    in>>date.month>>date.day>>date.year;
    return in;
}

ostream& operator << (ostream& out, Date& date){
    out<<date.to_json().dump(4)<<endl;
    return out;
}


struct Pearson{
    string name;
    string surname;
    string phone;
    string address;
    Date birthday;
    Pearson():
        name("Anonymous"), surname("Anonymous"),
        phone("404"), address("Not Found"),
        birthday() {};
    Pearson(string name, string surname, string phone, string address, Date birthday):
        name(std::move(name)), surname(std::move(surname)),
        phone(std::move(phone)), address(std::move(address)),
        birthday(std::move(birthday)) {};
    json to_json(){
        json data;
        data["Name"] = this->name;
        data["Surname"] = this->surname;
        data["Phone"] = this->phone;
        data["Address"] = this->address;
        data["Birthday"] = this->birthday.to_json();
        return data;
    }
};

istream& operator >> (istream& in, Pearson& pearson){
    in>>pearson.name>>pearson.surname>>pearson.phone>>pearson.address>>pearson.birthday;
    return in;
}

ostream& operator << (ostream& out, Pearson& pearson){
    out<<pearson.to_json().dump(4)<<endl;
    return out;
}


int main(){
    Date data("october", 30, 2002);
    Pearson pearson;
    json pearson_0 = pearson.to_json();
    cin>>pearson;
    json pearson_1 = pearson.to_json();
    cin>>pearson;
    json pearson_2 = pearson.to_json();
    filesystem::path parent_directory("..");
    filesystem::create_directory(parent_directory/"pearson_jsons");

    ofstream out;
    out.open("../pearson_jsons/0.txt");
    out<<pearson_0.dump(4);
    out.close();
    out.open("../pearson_jsons/1.txt");
    out<<pearson_1.dump(4);
    out.close();
    out.open("../pearson_jsons/2.txt");
    out<<pearson_2.dump(4);
    out.close();
    return 0;
}