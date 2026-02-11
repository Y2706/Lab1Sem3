#include <iostream>
#include <vector>
#include <string>
#include "list.h"

using namespace std;

struct Node {
    string num;
    Node* next;
};

Node* vectorToList(const vector<string>& values){
    Node* head = nullptr;
    Node* tail = nullptr;
    for(const string& value : values){
        Node* newNode = new Node;
        newNode -> num = value;
        newNode -> next = nullptr;
        if (head == nullptr){
            head = newNode;
            tail = newNode;
        } else{
            tail -> next = newNode;
            tail = newNode;
        }
    }
    return head;
}

void listToVector(Node* head, vector<string>& values){
    values.clear();
    Node* current = head;
    while(current != nullptr){
        values.push_back(current -> num);
        current = current -> next;
    }
}

void freeList(Node* head){
    Node* current = head;
    while (current != nullptr){
        Node* next = current -> next;
        delete current;
        current = next;
    }
}

void AddNodeAfter(Node* ptr, string key){
    Node* newNode = new Node;
    newNode -> num = key;
    newNode -> next = ptr -> next;
    ptr -> next = newNode;
}

Node* AddNodeBeginning(Node* ptr, string key){
    Node* newNode = new Node;
    newNode -> num = key;
    newNode -> next = ptr;
    return newNode;
}

void AddNodeEnd(Node* ptr, string key){
    Node* newNode = new Node;
    Node* current = ptr;
    while(current -> next != nullptr){
        current = current -> next;
    }
    newNode -> num = key;
    newNode -> next = nullptr;
    current -> next = newNode;
}

Node* DeleteNode(Node* head, string key){
    if (head != nullptr && key == head -> num){
        Node* newHead = head -> next;
        delete head;
        return newHead;
    }
    Node* current = head;
    Node* prev = nullptr;
    while(current != nullptr && current -> num != key){
        prev = current;
        current = current -> next;
    }
    if (current == nullptr){
        cout << "Узел не найден" << endl;
        return head;
    }
    prev -> next = current -> next;
    delete current;
    
    return head;
}

Node* SearchNode(Node* head, string foundKey){
    Node* current = head;
    while(current != nullptr){
        if (current -> num == foundKey){
            cout << "Узел найден" << endl;
            return current;
        }
        current = current -> next;
    }
    cout << "Узел не найден" << endl;
    return nullptr;
}

void PrintList(Node* head){
    cout << "List:" << endl;
    while (head != nullptr){
        cout << head -> num << " ";
        head = head -> next;
    }
    cout << endl;
}

bool fpushAfter(vector<string>& values, const string& existingKey, const string& newValue){
    Node* head = vectorToList(values);
    Node* ptr = SearchNode(head, existingKey);
    bool success = false;
    if (ptr != nullptr) {
        AddNodeAfter(ptr, newValue);
        success = true;
    } 
    listToVector(head, values);
    freeList(head);
    return success;
}

bool fpushBeginning(vector<string>& values, const string& key){
    Node* head = vectorToList(values);
    head = AddNodeBeginning(head, key);
    listToVector(head, values);
    freeList(head);
    return true;
}

bool fpushEnd(vector<string>& values, const string& key){
    Node* head = vectorToList(values);
    if (head == nullptr) {
        head = AddNodeBeginning(head, key);
    } else {
        AddNodeEnd(head, key); 
    }
    listToVector(head, values);
    freeList(head);
    return true;
}

bool fdel(vector<string>& values, const string& key){
    Node* head = vectorToList(values);
    size_t initialSize = values.size();
    head = DeleteNode(head, key); 
    listToVector(head, values);
    freeList(head);
    bool success = (values.size() < initialSize);
    return success;
}

bool fget(const vector<string>& values, const string& key){
    Node* head = vectorToList(values);
    Node* result = SearchNode(head, key);
    freeList(head);
    return result != nullptr;
}

bool fdelHead(vector<string>& values) {
    Node* head = vectorToList(values);
    
    if (head == nullptr) {
        cerr << "Ошибка: список пуст" << endl;
        freeList(head);
        return false;
    }
    
    string removedValue = head->num;
    Node* newHead = head->next;
    
    delete head;
    
    listToVector(newHead, values);
    freeList(newHead);
    
    cout << "Удален первый элемент: '" << removedValue << "'" << endl;
    return true;
}

bool fdelTail(vector<string>& values) {
    Node* head = vectorToList(values);
    
    if (head == nullptr) {
        cerr << "Ошибка: список пуст" << endl;
        freeList(head);
        return false;
    }
    
    if (head->next == nullptr) {
        string removedValue = head->num;
        delete head;
        head = nullptr;
        
        listToVector(head, values);
        freeList(head);
        
        cout << "Удален последний элемент: '" << removedValue << "'" << endl;
        return true;
    }
    
    Node* current = head;
    Node* prev = nullptr;
    
    while (current->next != nullptr) {
        prev = current;
        current = current->next;
    }
    
    string removedValue = current->num;
    prev->next = nullptr;
    
    delete current;
    
    listToVector(head, values);
    freeList(head);
    
    cout << "Удален последний элемент: '" << removedValue << "'" << endl;
    return true;
}

bool fdelAfter(vector<string>& values, const string& existingKey) {
    Node* head = vectorToList(values);
    Node* ptr = SearchNode(head, existingKey);
    
    if (ptr == nullptr) {
        freeList(head);
        return false;
    }
    
    if (ptr->next == nullptr) {
        cout << "Ошибка: нет элемента после '" << existingKey << "'" << endl;
        freeList(head);
        return false;
    }
    
    Node* toDelete = ptr->next;
    string removedValue = toDelete->num;
    
    ptr->next = toDelete->next;
    
    delete toDelete;
    
    listToVector(head, values);
    freeList(head);
    
    cout << "Удален элемент '" << removedValue << "' после '" << existingKey << "'" << endl;
    return true;
}

bool faddBefore(vector<string>& values, const string& existingKey, const string& newValue) {
    Node* head = vectorToList(values);
    
    if (head == nullptr) {
        cerr << "Ошибка: список пуст, невозможно добавить элемент перед '" << existingKey << "'" << endl;
        freeList(head);
        return false;
    }
    
    if (head->num == existingKey) {
        head = AddNodeBeginning(head, newValue);
        listToVector(head, values);
        freeList(head);
        cout << "Элемент '" << newValue << "' добавлен перед '" << existingKey << "'" << endl;
        return true;
    }
    
    Node* current = head;
    Node* prev = nullptr;
    
    while (current != nullptr && current->num != existingKey) {
        prev = current;
        current = current->next;
    }
    
    if (current == nullptr) {
        cerr << "Ошибка: элемент '" << existingKey << "' не найден в списке" << endl;
        freeList(head);
        return false;
    }
    
    Node* newNode = new Node;
    newNode->num = newValue;
    newNode->next = current;
    
    prev->next = newNode;
    
    listToVector(head, values);
    freeList(head);
    
    cout << "Элемент '" << newValue << "' добавлен перед '" << existingKey << "'" << endl;
    return true;
}

bool fdelBefore(vector<string>& values, const string& existingKey) {
    Node* head = vectorToList(values);
    
    if (head == nullptr) {
        cerr << "Ошибка: список пуст" << endl;
        freeList(head);
        return false;
    }
    
    if (head->num == existingKey) {
        cerr << "Ошибка: нет элемента перед '" << existingKey << "' (это первый элемент)" << endl;
        freeList(head);
        return false;
    }
    
    Node* current = head;
    Node* prev = nullptr;
    Node* prevPrev = nullptr;
    
    while (current != nullptr && current->num != existingKey) {
        prevPrev = prev;
        prev = current;
        current = current->next;
    }
    
    if (current == nullptr) {
        cerr << "Ошибка: элемент '" << existingKey << "' не найден в списке" << endl;
        freeList(head);
        return false;
    }
    
    if (prev == head) {
        string removedValue = head->num;
        Node* newHead = head->next;
        delete head;
        head = newHead;
        
        listToVector(head, values);
        freeList(head);
        
        cout << "Удален элемент '" << removedValue << "' перед '" << existingKey << "'" << endl;
        return true;
    }
    
    if (prev != nullptr && prevPrev != nullptr) {
        string removedValue = prev->num;
        prevPrev->next = current;
        delete prev;
        
        listToVector(head, values);
        freeList(head);
        
        cout << "Удален элемент '" << removedValue << "' перед '" << existingKey << "'" << endl;
        return true;
    }
    
    cerr << "Ошибка: невозможно удалить элемент перед '" << existingKey << "'" << endl;
    freeList(head);
    return false;
}
