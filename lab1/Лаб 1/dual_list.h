#ifndef DUAL_LIST_H
#define DUAL_LIST_H

#include <vector>
#include <string>

using namespace std;

bool lpushLeft(vector<string>& values, const string& key);
bool lpushRight(vector<string>& values, const string& key);
bool laddBefore(vector<string>& values, const string& existingKey, const string& newValue);
bool laddAfter(vector<string>& values, const string& existingKey, const string& newValue);
bool ldelHead(vector<string>& values);
bool ldelTail(vector<string>& values);
bool ldelBefore(vector<string>& values, const string& existingKey);
bool ldelAfter(vector<string>& values, const string& existingKey);
bool ldel(vector<string>& values, const string& key);
bool lget(const vector<string>& values, const string& key);

#endif
