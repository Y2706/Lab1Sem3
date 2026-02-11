#ifndef LIST_H
#define LIST_H

#include <vector>
#include <string>

using namespace std;

bool fpushBeginning(vector<string>& values, const string& value);
bool fpushEnd(vector<string>& values, const string& value);
bool fpushAfter(vector<string>& values, const string& existingKey, const string& newValue);
bool faddBefore(vector<string>& values, const string& existingKey, const string& newValue);
bool fdelHead(vector<string>& values);
bool fdelTail(vector<string>& values);
bool fdelAfter(vector<string>& values, const string& existingKey);
bool fdelBefore(vector<string>& values, const string& existingKey);
bool fdel(vector<string>& values, const string& key);
bool fget(const vector<string>& values, const string& key);

#endif
