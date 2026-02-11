#ifndef QUEUE_H
#define QUEUE_H

#include <vector>
#include <string>

using namespace std;

struct QNode {
    string data;
    QNode* next;
};

struct Queue {
    QNode* front;
    QNode* rear;
};

bool qpush(vector<string>& values, const string& value);
bool qpop(vector<string>& values);

#endif
