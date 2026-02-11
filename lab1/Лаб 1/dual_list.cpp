#include "dual_list.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct DualNode {
    string name;
    DualNode* prev;
    DualNode* next;
};

DualNode* vectorToDualList(const vector<string>& values){
    DualNode* head = nullptr;
    DualNode* tail = nullptr;
    for(const string& value : values){
        DualNode* newNode = new DualNode;
        newNode -> name = value;
        newNode -> next = nullptr;
        
        if (head == nullptr){
            newNode -> prev = nullptr;
            head = newNode;
            tail = newNode;
        } else{
            newNode -> prev = tail;
            tail -> next = newNode;
            tail = newNode;
        }
    }
    return head;
}

void dualListToVector(DualNode* head, vector<string>& values){
    values.clear();
    DualNode* current = head;
    while(current != nullptr){
        values.push_back(current -> name);
        current = current -> next;
    }
}

void freeDualList(DualNode* head){
    DualNode* current = head;
    while (current != nullptr){
        DualNode* next = current -> next;
        delete current;
        current = next;
    }
}

DualNode* AddNodeBeginning(DualNode* head, string name){
    DualNode* newNode = new DualNode;
    newNode -> name = name;
    newNode -> next = head;
    newNode -> prev = nullptr;
    if (head != nullptr){
        head -> prev = newNode;
    }
    return newNode;
}

void AddNodeEnd(DualNode* head, string name){
    DualNode* current = head;
    while(current -> next != nullptr){
        current = current -> next;
    }
    DualNode* newNode = new DualNode;
    newNode -> name = name;
    newNode -> prev = current;
    newNode -> next = nullptr;
    current -> next = newNode;
}

void AddNodeAfter(DualNode* ptr, string name){
    DualNode* newNode = new DualNode;
    newNode -> name = name;
    
    newNode -> next = ptr -> next;
    newNode -> prev = ptr;
    ptr -> next = newNode;
    
    if (newNode -> next != nullptr){
        newNode -> next -> prev = newNode;
    }
}

DualNode* AddNodeBefore(DualNode* head, DualNode* ptr, string name){
    DualNode* newNode = new DualNode;
    newNode -> name = name;
    
    if (ptr == head){
        newNode -> next = ptr;
        newNode -> prev = nullptr;
        ptr -> prev = newNode;
        return newNode;
    }
    
    newNode -> next = ptr;
    newNode -> prev = ptr -> prev;
    ptr -> prev -> next = newNode;
    ptr -> prev = newNode;
    return head;
}

DualNode* NodeFound(DualNode* head, string name){
    DualNode* current = head;
    while(current != nullptr){
        if (current -> name == name){
            cout << "Узел найден" << endl;
            return current;
        }
        current = current -> next;
    }
    cout << "Узел не найден" << endl;
    return nullptr;
}

DualNode* DeleteNode(DualNode* head, string name){
    DualNode* ptr = head;
    while(ptr != nullptr && ptr -> name != name){
        ptr = ptr -> next;
    }
    
    if(ptr == nullptr){
        cout << "Ошибка: узел не найден" << endl;
        return head;
    }
    
    if(ptr -> prev != nullptr){
        ptr -> prev -> next = ptr -> next;
    } else {
        head = ptr -> next;
    }
    
    if(ptr -> next != nullptr){
        ptr -> next -> prev = ptr -> prev;
    }
    
    delete ptr;
    return head;
}

bool lpushLeft(vector<string>& values, const string& key) {
    DualNode* head = vectorToDualList(values);
    head = AddNodeBeginning(head, key);
    dualListToVector(head, values);
    freeDualList(head);
    return true;
}

bool lpushRight(vector<string>& values, const string& key) {
    DualNode* head = vectorToDualList(values);
    if (head == nullptr) {
        head = AddNodeBeginning(head, key);
    } else {
        AddNodeEnd(head, key);
    }
    dualListToVector(head, values);
    freeDualList(head);
    return true;
}

bool laddBefore(vector<string>& values, const string& existingKey, const string& newValue) {
    DualNode* head = vectorToDualList(values);
    DualNode* ptr = NodeFound(head, existingKey);
    bool success = false;

    if (ptr != nullptr) {
        head = AddNodeBefore(head, ptr, newValue);
        success = true;
    }
    
    dualListToVector(head, values);
    freeDualList(head);
    return success;
}

bool laddAfter(vector<string>& values, const string& existingKey, const string& newValue) {
    DualNode* head = vectorToDualList(values);
    DualNode* ptr = NodeFound(head, existingKey);
    bool success = false;

    if (ptr != nullptr) {
        AddNodeAfter(ptr, newValue);
        success = true;
    }
    
    dualListToVector(head, values);
    freeDualList(head);
    return success;
}

bool ldel(vector<string>& values, const string& key) {
    DualNode* head = vectorToDualList(values);
    size_t initialSize = values.size();
    head = DeleteNode(head, key);
    
    dualListToVector(head, values);
    freeDualList(head);
    
    bool success = (values.size() < initialSize);
    return success;
}

bool lget(const vector<string>& values, const string& key) {
    DualNode* head = vectorToDualList(values);
    NodeFound(head, key);
    freeDualList(head);
    return true;
}

bool ldelHead(vector<string>& values) {
    DualNode* head = vectorToDualList(values);
    
    if (head == nullptr) {
        cerr << "Ошибка: список пуст" << endl;
        freeDualList(head);
        return false;
    }
    
    string removedValue = head->name;
    DualNode* newHead = head->next;
    
    if (newHead != nullptr) {
        newHead->prev = nullptr;
    }
    
    delete head;
    
    dualListToVector(newHead, values);
    freeDualList(newHead);
    
    cout << "Удален первый элемент: '" << removedValue << "'" << endl;
    return true;
}

bool ldelTail(vector<string>& values) {
    DualNode* head = vectorToDualList(values);
    
    if (head == nullptr) {
        cerr << "Ошибка: список пуст" << endl;
        freeDualList(head);
        return false;
    }
    
    DualNode* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    
    string removedValue = current->name;
    
    if (current->prev != nullptr) {
        current->prev->next = nullptr;
    } else {
        head = nullptr;
    }
    
    delete current;
    
    dualListToVector(head, values);
    freeDualList(head);
    
    cout << "Удален последний элемент: '" << removedValue << "'" << endl;
    return true;
}

bool ldelBefore(vector<string>& values, const string& existingKey) {
    DualNode* head = vectorToDualList(values);
    DualNode* ptr = NodeFound(head, existingKey);
    
    if (ptr == nullptr) {
        freeDualList(head);
        return false;
    }
    
    if (ptr->prev == nullptr) {
        cout << "Ошибка: нет элемента перед '" << existingKey << "'" << endl;
        freeDualList(head);
        return false;
    }
    
    DualNode* toDelete = ptr->prev;
    string removedValue = toDelete->name;
    
    if (toDelete->prev != nullptr) {
        toDelete->prev->next = ptr;
    } else {
        head = ptr;
    }
    
    ptr->prev = toDelete->prev;
    
    delete toDelete;
    
    dualListToVector(head, values);
    freeDualList(head);
    
    cout << "Удален элемент '" << removedValue << "' перед '" << existingKey << "'" << endl;
    return true;
}

bool ldelAfter(vector<string>& values, const string& existingKey) {
    DualNode* head = vectorToDualList(values);
    DualNode* ptr = NodeFound(head, existingKey);
    
    if (ptr == nullptr) {
        freeDualList(head);
        return false;
    }
    
    if (ptr->next == nullptr) {
        cout << "Ошибка: нет элемента после '" << existingKey << "'" << endl;
        freeDualList(head);
        return false;
    }
    
    DualNode* toDelete = ptr->next;
    string removedValue = toDelete->name;
    
    if (toDelete->next != nullptr) {
        toDelete->next->prev = ptr;
    }
    
    ptr->next = toDelete->next;
    
    delete toDelete;
    
    dualListToVector(head, values);
    freeDualList(head);
    
    cout << "Удален элемент '" << removedValue << "' после '" << existingKey << "'" << endl;
    return true;
}
