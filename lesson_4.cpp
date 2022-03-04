#include <iostream>
#include <fstream>
#include <iterator>
#include <filesystem>
using namespace std;


int main(){
    filesystem::path parent_directory("..");
    auto path_to_main = parent_directory / "lesson_4.cpp";
    auto copy_path = parent_directory / "copy_lesson_4.cpp";
    // absolute and relative paths
    cout<<filesystem::absolute(copy_path)<<endl;
    cout<<filesystem::relative(copy_path)<<endl;
    cout<<endl;
    // copy file
    filesystem::remove(copy_path);
    filesystem::copy(path_to_main, copy_path);
    fstream reader(copy_path, ios::in);
    copy(istream_iterator<string>(reader),
            istream_iterator<string>(),
            ostream_iterator<string>(cout, " "));
    reader.close();
    filesystem::remove(copy_path);
    // loop in directory
    auto directory_for_lookup = parent_directory / "cmake-build-debug";
    filesystem::directory_iterator begin{directory_for_lookup};
    filesystem::directory_iterator end;
    for(auto it = begin; it!=end; it++){
        // get info about files
        auto& current_file_path = it->path();
        cout<<"Full path: "<<filesystem::absolute(current_file_path)<<endl;
        auto is_directory = filesystem::is_directory(current_file_path);
        cout<<"Is a directory: "<<boolalpha<<is_directory<<endl;
        if(!is_directory) {
            cout << "Stem: " << current_file_path.stem() << endl;
            cout << "Extension: " << current_file_path.extension() << endl;
        }
    }

    return 0;
}