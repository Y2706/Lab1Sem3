#include "queue.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

Queue* vectorToQueue(const vector<string>& values) {
    Queue* q = new Queue;
    q->front = nullptr;
    q->rear = nullptr;
    
    for (const string& value : values) {
        QNode* newNode = new QNode;
        newNode->data = value;
        newNode->next = nullptr;
        
        if (q->rear == nullptr) {
            q->front = newNode;
            q->rear = newNode;
        } else {
            q->rear->next = newNode;
            q->rear = newNode;
        }
    }
    
    return q;
}

void queueToVector(Queue* q, vector<string>& values) {
    values.clear();
    
    QNode* current = q->front;
    while (current != nullptr) {
        values.push_back(current->data);
        current = current->next;
    }
}

void freeQueue(Queue* q) {
    QNode* current = q->front;
    while (current != nullptr) {
        QNode* next = current->next;
        delete current;
        current = next;
    }
    delete q;
}

bool qpush(vector<string>& values, const string& value) {
    Queue* q = vectorToQueue(values);
    
    QNode* newNode = new QNode;
    newNode->data = value;
    newNode->next = nullptr;
    
    if (q->rear == nullptr) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    
    queueToVector(q, values);
    freeQueue(q);
    
    cout << "Элемент '" << value << "' добавлен в очередь" << endl;
    return true;
}

bool qpop(vector<string>& values) {
    Queue* q = vectorToQueue(values);
    
    if (q->front == nullptr) {
        cerr << "Ошибка: очередь пуста" << endl;
        freeQueue(q);
        return false;
    }
    
    string poppedValue = q->front->data;
    QNode* nodeToDelete = q->front;
    q->front = q->front->next;
    
    if (q->front == nullptr) {
        q->rear = nullptr;
    }
    
    delete nodeToDelete;
    
    queueToVector(q, values);
    freeQueue(q);
    
    cout << "Элемент '" << poppedValue << "' удален из очереди" << endl;
    return true;
}