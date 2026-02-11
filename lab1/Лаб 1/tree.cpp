#include "tree.h"
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>

using namespace std;

TreeNode* vectorToTree(const vector<string>& values) {
    if (values.empty()) return nullptr;
    
    TreeNode* root = new TreeNode;
    root->data = values[0];
    root->left = nullptr;
    root->right = nullptr;
    root->parent = nullptr;
    
    queue<TreeNode*> nodeQueue;
    nodeQueue.push(root);
    
    int i = 1;
    while (i < values.size()) {
        TreeNode* current = nodeQueue.front();
        nodeQueue.pop();
        
        if (i < values.size()) {
            TreeNode* leftNode = new TreeNode;
            leftNode->data = values[i];
            leftNode->left = nullptr;
            leftNode->right = nullptr;
            leftNode->parent = current;
            current->left = leftNode;
            nodeQueue.push(leftNode);
            i++;
        }
        
        if (i < values.size()) {
            TreeNode* rightNode = new TreeNode;
            rightNode->data = values[i];
            rightNode->left = nullptr;
            rightNode->right = nullptr;
            rightNode->parent = current;
            current->right = rightNode;
            nodeQueue.push(rightNode);
            i++;
        }
    }
    
    return root;
}

void treeToVector(TreeNode* root, vector<string>& values) {
    values.clear();
    if (!root) return;
    
    queue<TreeNode*> nodeQueue;
    nodeQueue.push(root);
    
    while (!nodeQueue.empty()) {
        TreeNode* current = nodeQueue.front();
        nodeQueue.pop();
        
        if (current) {
            values.push_back(current->data);
            nodeQueue.push(current->left);
            nodeQueue.push(current->right);
        } else {
            values.push_back("NULL");
        }
    }
    
    while (!values.empty() && values.back() == "NULL") {
        values.pop_back();
    }
}

void freeTree(TreeNode* root) {
    if (!root) return;
    
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

bool tadd(vector<string>& values, const string& value) {
    TreeNode* root = vectorToTree(values);
    
    stringstream ss(value);
    string numStr;
    if (!(ss >> numStr) || !ss.eof()) {
        cerr << "Ошибка: неверный формат значения" << endl;
        freeTree(root);
        return false;
    }
    
    TreeNode* newNode = new TreeNode;
    newNode->data = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->parent = nullptr;
    
    if (!root) {
        root = newNode;
    } else {
        queue<TreeNode*> nodeQueue;
        nodeQueue.push(root);
        
        while (!nodeQueue.empty()) {
            TreeNode* current = nodeQueue.front();
            nodeQueue.pop();
            
            if (!current->left) {
                current->left = newNode;
                newNode->parent = current;
                break;
            } else if (!current->right) {
                current->right = newNode;
                newNode->parent = current;
                break;
            } else {
                nodeQueue.push(current->left);
                nodeQueue.push(current->right);
            }
        }
    }
    
    treeToVector(root, values);
    freeTree(root);
    
    cout << "Элемент '" << value << "' добавлен в дерево" << endl;
    return true;
}

bool tsearch(const vector<string>& values, const string& value) {
    TreeNode* root = vectorToTree(values);
    
    if (!root) {
        freeTree(root);
        return false;
    }
    
    queue<TreeNode*> nodeQueue;
    nodeQueue.push(root);
    
    while (!nodeQueue.empty()) {
        TreeNode* current = nodeQueue.front();
        nodeQueue.pop();
        
        if (current->data == value) {
            cout << "Элемент '" << value << "' найден в дереве" << endl;
            freeTree(root);
            return true;
        }
        
        if (current->left) nodeQueue.push(current->left);
        if (current->right) nodeQueue.push(current->right);
    }
    
    cout << "Элемент '" << value << "' не найден в дереве" << endl;
    freeTree(root);
    return false;
}

bool isCompleteBinaryTree(TreeNode* root) {
    if (!root) return true;
    
    queue<TreeNode*> q;
    q.push(root);
    bool end = false;
    
    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        
        if (!current) {
            end = true;
        } else {
            if (end) return false;
            
            q.push(current->left);
            q.push(current->right);
        }
    }
    return true;
}

bool tisFull(const vector<string>& values) {
    TreeNode* root = vectorToTree(values);
    bool result = isCompleteBinaryTree(root);
    freeTree(root);
    
    if (result) {
        cout << "Дерево является полным бинарным деревом" << endl;
    } else {
        cout << "Дерево не является полным бинарным деревом" << endl;
    }
    
    return result;
}

void printTree(TreeNode* root, int level) {
    if (!root) return;
    
    printTree(root->right, level + 1);
    
    for (int i = 0; i < level; i++) {
        cout << "    ";
    }
    
    cout << root->data << endl;
    
    printTree(root->left, level + 1);
}

void tprint(const vector<string>& values) {
    TreeNode* root = vectorToTree(values);
    
    if (!root) {
        cout << "Дерево пусто" << endl;
        return;
    }
    
    cout << "Дерево:" << endl;
    printTree(root, 0);
    freeTree(root);
} 
