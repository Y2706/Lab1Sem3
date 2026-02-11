#include "stack.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

SNode* vectorToStack(const vector<string>& values) {
    SNode* head = nullptr;
    
    for (const string& value : values) {
        SNode* newNode = new SNode;
        newNode->data = value;
        newNode->next = head;
        head = newNode;
    }
    
    return head;
}

void stackToVector(SNode* head, vector<string>& values) {
    values.clear();
    
    SNode* current = head;
    while (current != nullptr) {
        values.push_back(current->data);
        current = current->next;
    }
}

void freeStack(SNode* head) {
    SNode* current = head;
    while (current != nullptr) {
        SNode* next = current->next;
        delete current;
        current = next;
    }
}

bool spush(vector<string>& values, const string& value) {
    SNode* head = vectorToStack(values);
    
    SNode* newNode = new SNode;
    newNode->data = value;
    newNode->next = head;
    head = newNode;
    
    stackToVector(head, values);
    freeStack(head);
    
    cout << "Элемент '" << value << "' добавлен в стек" << endl;
    return true;
}

bool spop(vector<string>& values) {
    SNode* head = vectorToStack(values);
    
    if (head == nullptr) {
        cerr << "Ошибка: стек пуст" << endl;
        freeStack(head);
        return false;
    }
    
    string poppedValue = head->data;
    SNode* nodeToDelete = head;
    head = head->next;
    
    delete nodeToDelete;
    
    stackToVector(head, values);
    freeStack(head);
    
    cout << "Элемент '" << poppedValue << "' удален из стека" << endl;
    return true;
}