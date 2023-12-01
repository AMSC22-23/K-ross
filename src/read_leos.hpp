#ifndef READ_LEOS_HPP
#define READ_LEOS_HPP


#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Entry {
    int id;
    double f1;
    double f2;
    string name;
};

int read_leos(vector<Entry>& data);


#endif