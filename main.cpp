#include <fstream>
#include <iostream>
#include "reading_with_char_star.h"
#include "reading_with_string.h"

using namespace std;

int main() {
    ifstream file;

    file.open(R"(C:\coding\cplusplus\untitled\pg67730.txt)");
    if (!file.is_open()) {
        exit(1);
    }
    string res1 = read_with_char_star(file);
    file.close();

    file.open(R"(C:\coding\cplusplus\untitled\pg67730.txt)");
    if (!file.is_open()) {
        exit(1);
    }
    string res2 = read_with_string(file);
    file.close();


    cout << endl;
    cout << res1 << endl;
    cout << res2 << endl;
    return 0;
}