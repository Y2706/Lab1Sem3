#ifndef TREE_H
#define TREE_H

#include <vector>
#include <string>

using namespace std;

struct TreeNode {
    string data;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
};

bool tadd(vector<string>& values, const string& value);
bool tsearch(const vector<string>& values, const string& value);
bool tisFull(const vector<string>& values);
void tprint(const vector<string>& values);

#endif
