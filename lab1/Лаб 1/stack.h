#ifndef STACK_H
#define STACK_H

#include <vector>
#include <string>

using namespace std;

struct SNode {
    string data;
    SNode* next;
};

bool spush(vector<string>& values, const string& value);
bool spop(vector<string>& values);

#endif
