//
// Created by Вадим on 01.04.2022.
//

#include "reading_with_string.h"
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <cstring>
#include <algorithm>
#include <vector>
#include <chrono>
#include <sstream>

using namespace std;

string format_string(string s){
    for(std::string::iterator it = s.begin(); it != s.end(); ++it){
        if(!isalpha(*it))
            *it = ' ';
        else
            *it = tolower(*it);
    }
    return s;
}

bool cmp_pairs_by_value(pair<string, int> const &a, pair<string, int> const &b) {
return a.second > b.second;
}

vector<pair<string, int>> sort_map_by_value(map<string, int> dict) {
    vector<pair<string, int>> vec;
    map<string, int>::iterator it1;
    for (it1 = dict.begin(); it1 != dict.end(); it1++) {
        vec.emplace_back(it1->first, it1->second);
    }

    sort(vec.begin(), vec.end(), cmp_pairs_by_value);
    return vec;
}

string read_with_string(ifstream &file) {
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    string tmp_str;
    map<string, int> dict;
    while(file.good()){
        auto tmp_ch = file.get();
        if(isalpha(tmp_ch))
            tmp_str+= tolower(tmp_ch);
        else{
            if(!tmp_str.empty()){
                ++dict[tmp_str];
                tmp_str.clear();
            }
        }
    }
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    auto vec = sort_map_by_value(dict);
    dict.clear();
//    for (auto &pair: vec)
//        cout << "{" << pair.first << ": " << pair.second << "}" << endl;
    auto size = vec.size();
    vector<pair<string,int>> empty;
    vec.swap(empty);
    stringstream result;
    result << "Map size = " << size << endl;
    result << "reading with string time = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "[ms]"
           << endl;
    return result.str();
}