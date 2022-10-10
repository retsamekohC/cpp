#include <iostream>
#include <list>
#include <map>
#include <set>
#include <cstring>
#include <algorithm>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>
#include "reading_with_char_star.h"

using namespace std;

class Node {
    int endOfBuffer;
    static const int size = 32;

public:
    Node() {
        endOfBuffer = 0;
    }

    ~Node() {
        delete next;
    }

    Node *addToBuffer(char symbol) {
        if (endOfBuffer != size) {
            buffer[endOfBuffer] = symbol;
            endOfBuffer++;
            return this;
        } else {
            Node *nextElement = new Node();
            nextElement->addToBuffer(symbol);
            next = nextElement;
            return nextElement;
        }
    }

    bool isBufferFull() {
        return (bool) buffer[size - 1];
    }

    bool isLast() {
        return !isBufferFull();
    }

    int length() {
        return endOfBuffer;
    }

    Node *next;
    char buffer[size]{};
};

struct cmp_str {
    bool operator()(char const *a, char const *b) const {
        return strcmp(a, b) < 0;
    }
};

bool cmp_pairs_by_value(pair<char *, int> const &a, pair<char *, int> const &b) {
return a.second > b.second;
}

vector<pair<char *, int>> sort_map_by_value(map<char *, int, cmp_str> dict) {
    vector<pair<char *, int>> vec;
    map<char *, int>::iterator it1;
    for (it1 = dict.begin(); it1 != dict.end(); it1++) {
        vec.emplace_back(it1->first, it1->second);
    }

    sort(vec.begin(), vec.end(), cmp_pairs_by_value);
    vec.erase(vec.begin());
    return vec;
}

set<char> punctuation{' '};

Node *get_linked_list_with_file_content(ifstream &file) {
    Node *element = new Node();
    Node *first = element;
    while (file.good()) {
        char symbol = file.get();
        if (!isalpha(symbol))
            symbol = ' ';
        else
            symbol = tolower(symbol);
        element = element->addToBuffer(tolower(symbol));
    }
    return first;
}

map<char *, int, struct cmp_str> fill_dict(Node *current) {
    map<char *, int, cmp_str> dict;
    char word_arr[20]{0};
    int k = 0;
    bool isItFirstLoop = true;
    while (!(current->isLast())) {
        if (!isItFirstLoop) {
            current = current->next;
        }
        isItFirstLoop = false;
        for (int i = 0; i < current->length(); i++) {
            if (!punctuation.count(current->buffer[i])) {
                word_arr[k] = current->buffer[i];
                k++;
            } else {
                char *word_key = new char[sizeof(word_arr)];
                strcpy(word_key, word_arr);
                ++dict[word_key];
                memset(word_arr, 0, sizeof(word_arr));
                k = 0;
            }
        }
    }
    return dict;
}

string read_with_char_star(ifstream &file) {
    Node *current = get_linked_list_with_file_content(file);
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    map<char *, int, cmp_str> dict = fill_dict(current);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    auto vec = sort_map_by_value(dict);
    dict.clear();
//    for (auto &pair: vec)
//        cout << "{" << pair.first << ": " << pair.second << "}" << endl;
    auto size = vec.size();
    vec.clear();
    stringstream result;
    result << "Map size - " << size << endl;
    result << "reading with char* time = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "[ms]"
         << endl;
    punctuation.clear();
    return result.str();
}