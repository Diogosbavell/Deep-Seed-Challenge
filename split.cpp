
#include <iostream>
#include <vector>
#include "headers/split.h"

using namespace std;

vector<string> Split::start(string s, string delimiter)
{
    size_t position_start = 0, position_end, delim_length = delimiter.length();
    string result;
    vector<string> separated;

    while ((position_end = s.find(delimiter, position_start)) != string::npos)
    {
        result = s.substr(position_start, position_end - position_start);
        position_start = position_end + delim_length;
        separated.push_back(result);
    }

    separated.push_back(s.substr(position_start));
    return separated;
};