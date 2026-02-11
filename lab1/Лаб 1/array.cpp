#include "array.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

Array* vectorToArray(const vector<string>& values) {
    Array* arr = new Array;
    arr->size = values.size();
    arr->capacity = arr->size;
    arr->data = new string[arr->capacity];
    
    for (int i = 0; i < arr->size; i++) {
        arr->data[i] = values[i];
    }
    return arr;
}

void arrayToVector(Array* arr, vector<string>& values) {
    values.clear();
    values.reserve(arr->size);
    
    for (int i = 0; i < arr->size; i++) {
        values.push_back(arr->data[i]);
    }
}

void freeArray(Array* arr) {
    if (arr != nullptr) {
        if (arr->data != nullptr) {
            delete[] arr->data;
        }
        delete arr;
    }
}

bool marrayCreate(vector<string>& values, const string& sizeStr) {
    stringstream ss(sizeStr);
    int size;
    
    if (!(ss >> size) || !ss.eof()) {
        cerr << "Ошибка: неверный формат размера массива" << endl;
        return false;
    }
    
    if (size < 0) {
        cerr << "Ошибка: размер массива не может быть отрицательным" << endl;
        return false;
    }
    
    Array* arr = new Array;
    arr->size = size;
    arr->capacity = size;
    arr->data = new string[arr->capacity];
    
    for (int i = 0; i < arr->size; i++) {
        arr->data[i] = "";
    }
    
    arrayToVector(arr, values);
    freeArray(arr);
    
    cout << "Массив создан, размер: " << size << endl;
    return true;
}

bool madd(vector<string>& values, const string& value) {
    Array* arr = vectorToArray(values);
    
    if (arr->size >= arr->capacity) {
        arr->capacity = (arr->capacity == 0) ? 1 : arr->capacity * 2;
        string* newData = new string[arr->capacity];
        
        for (int i = 0; i < arr->size; i++) {
            newData[i] = arr->data[i];
        }
        
        delete[] arr->data;
        arr->data = newData;
    }
    
    arr->data[arr->size] = value;
    arr->size++;
    
    arrayToVector(arr, values);
    freeArray(arr);
    
    cout << "Элемент '" << value << "' добавлен в конец массива" << endl;
    return true;
}

bool mindexAdd(vector<string>& values, const string& indexStr, const string& value) {
    stringstream ss(indexStr);
    int index;
    
    if (!(ss >> index) || !ss.eof()) {
        cerr << "Ошибка: неверный формат индекса" << endl;
        return false;
    }
    
    Array* arr = vectorToArray(values);
    
    if (index < 0 || index > arr->size) {
        cerr << "Ошибка: некорректный индекс (" << index 
             << "). Допустимый диапазон: 0-" << arr->size << endl;
        freeArray(arr);
        return false;
    }
    
    if (arr->size >= arr->capacity) {
        arr->capacity = (arr->capacity == 0) ? 1 : arr->capacity * 2;
        string* newData = new string[arr->capacity];
        
        for (int i = 0; i < arr->size; i++) {
            newData[i] = arr->data[i];
        }
        
        delete[] arr->data;
        arr->data = newData;
    }
    
    for (int i = arr->size; i > index; i--) {
        arr->data[i] = arr->data[i - 1];
    }
    
    arr->data[index] = value;
    arr->size++;
    
    arrayToVector(arr, values);
    freeArray(arr);
    
    cout << "Элемент '" << value << "' добавлен по индексу " << index << endl;
    return true;
}

bool mget(const vector<string>& values, const string& indexStr) {
    stringstream ss(indexStr);
    int index;
    
    if (!(ss >> index) || !ss.eof()) {
        cerr << "Ошибка: неверный формат индекса" << endl;
        return false;
    }
    
    Array* arr = vectorToArray(values);
    
    if (index < 0 || index >= arr->size) {
        cerr << "Ошибка: некорректный индекс (" << index 
             << "). Допустимый диапазон: 0-" << (arr->size - 1) << endl;
        freeArray(arr);
        return false;
    }
    
    cout << "Элемент по индексу " << index << ": " << arr->data[index] << endl;
    freeArray(arr);
    return true;
}

bool mdeleteIndex(vector<string>& values, const string& indexStr) {
    stringstream ss(indexStr);
    int index;
    
    if (!(ss >> index) || !ss.eof()) {
        cerr << "Ошибка: неверный формат индекса" << endl;
        return false;
    }
    
    Array* arr = vectorToArray(values);
    
    if (index < 0 || index >= arr->size) {
        cerr << "Ошибка: некорректный индекс (" << index 
             << "). Допустимый диапазон: 0-" << (arr->size - 1) << endl;
        freeArray(arr);
        return false;
    }
    
    string removedValue = arr->data[index];
    
    for (int i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    
    arr->size--;
    
    arrayToVector(arr, values);
    freeArray(arr);
    
    cout << "Элемент '" << removedValue << "' удален по индексу " << index << endl;
    return true;
}

bool mreplace(vector<string>& values, const string& indexStr, const string& value) {
    stringstream ss(indexStr);
    int index;
    
    if (!(ss >> index) || !ss.eof()) {
        cerr << "Ошибка: неверный формат индекса" << endl;
        return false;
    }
    
    Array* arr = vectorToArray(values);
    
    if (index < 0 || index >= arr->size) {
        cerr << "Ошибка: некорректный индекс (" << index 
             << "). Допустимый диапазон: 0-" << (arr->size - 1) << endl;
        freeArray(arr);
        return false;
    }
    
    string oldValue = arr->data[index];
    arr->data[index] = value;
    
    arrayToVector(arr, values);
    freeArray(arr);
    
    cout << "Элемент по индексу " << index << " заменен: '" 
         << oldValue << "' -> '" << value << "'" << endl;
    return true;
}

bool mlength(const vector<string>& values) {
    Array* arr = vectorToArray(values);
    cout << "Длина массива: " << arr->size << endl;
    freeArray(arr);
    return true;
}
