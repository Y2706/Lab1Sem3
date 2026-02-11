#ifndef ARRAY_H
#define ARRAY_H

#include <vector>
#include <string>

using namespace std;

struct Array {
    string* data;
    int size;
    int capacity;
};

bool marrayCreate(vector<string>& values, const string& sizeStr);
bool madd(vector<string>& values, const string& value);
bool mindexAdd(vector<string>& values, const string& indexStr, const string& value);
bool mget(const vector<string>& values, const string& indexStr);
bool mdeleteIndex(vector<string>& values, const string& indexStr);
bool mreplace(vector<string>& values, const string& indexStr, const string& value);
bool mlength(const vector<string>& values);

#endif
