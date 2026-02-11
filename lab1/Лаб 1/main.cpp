#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "list.h"
#include "dual_list.h"
#include "array.h"
#include "queue.h"
#include "stack.h"
#include "tree.h"
using namespace std;

struct Structure {
    string type;
    vector<string> values; 
};

using DataBase = map<string, Structure>;

DataBase loadData(string& file){
    DataBase db;
    ifstream input(file);
    if (!input.is_open()){
        cerr << "Файл не найден или пуст. Создание новой базы";
        return db;
    }

    string line;
    string currentName;
    string currentType;
    while (getline(input, line)){
        if (line.empty()) continue;
        if (line[0] == '#'){
            string header = line.substr(1);
            stringstream ss(header);
            string type, name;
            if (ss >> type >> name){
                currentName = name;
                currentType = type;
                db[name].type = type;
                db[name].values = {};
            }
        } else if (!currentName.empty()){
            db[currentName].values.push_back(line);
        }
    }
    input.close();
    return db;
}

void saveData(const string& file, const DataBase& db){
    ofstream output(file);
    if (!output.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл для записи: " << file << endl;
        return;
    }

    for (const auto& pair : db) {
        const string& name = pair.first;
        const Structure& s = pair.second;

        output << "# " << s.type << " " << name << "\n";
        
        for (const string& value : s.values) {
            output << value << "\n";
        }
    }
    
    output.close();
}

int main(int argc, char* argv[]){
    string key1 = argv[1];
    string key2 = argv[3];
    if (argc != 5 || key1 != "--file" || key2 != "--query"){
        cerr << "Ошибка: Неверный формат аргументов";
        return 1;
    }
    string file = argv[2];
    string query = argv[4];

    DataBase db = loadData(file);

    stringstream ss(query);
    string command, structName, param1, param2;

    ss >> command >> structName >> param1 >> param2;

    if (command.empty() || structName.empty()){
        cerr << "Ошибка: Неверный формат ввода";
        return 1;
    }

    char typePrefix = command[0];
    Structure& s = db[structName];
    if (s.type.empty()){
        if (typePrefix == 'M'){
            s.type = "ARRAY";
        } else if (typePrefix == 'F'){
            s.type = "LIST";
        } else if (typePrefix == 'L'){
            s.type = "DUAL_LIST";
        } else if (typePrefix == 'Q'){
            s.type = "QUEUE";
        } else if (typePrefix == 'S'){
            s.type = "STACK";
        } else if (typePrefix == 'T'){
            s.type = "TREE";
        }
    }

    vector<string>& values = s.values;
    if (command == "PRINT"){
        cout << "Содержимое " << structName << " (" << s.type << "): ";
        if (values.empty()){
            cout << "Пусто" << endl;
        } else{
            for (const string& val : values){
                cout << val << " ";
            }
            cout << endl;
        }
    } else{
        if (s.type.empty()){
            cerr << "Ошибка: Структура " << structName << " не имеет определённого типа" << endl;
            return 1;
        }
        
        if (typePrefix == 'F'){
            if (s.type != "LIST") {
                cerr << "Ошибка: Структура " << structName << " имеет тип " << s.type << ", ожидался LIST." << endl;
                return 1;
            }
            if (command == "FPUSH"){
                if (fpushBeginning(values, param1)){
                    cout << "Успешно: FPUSH (в начало) " << param1 << " в " << structName << endl;
                }
            } else if (command == "FADD_END"){
                if (fpushEnd(values, param1)){
                    cout << "Успешно: FADD_END (в конец) " << param1 << " в " << structName << endl;
                }
            } else if (command == "FADD_AFTER") {
                if (fpushAfter(values, param1, param2)) {
                    cout << "Успешно: FADD_AFTER (после " << param1 << ") " << param2 << " в " << structName << endl;
                } else {
                    return 1; 
                }
            } else if (command == "FDEL") {
                if (fdel(values, param1)) {
                    cout << "Успешно: FDEL (удален " << param1 << ") из " << structName << endl;
                } else {
                    return 1; 
                }
            } else if (command == "FGET") {
                if (fget(values, param1)) {
                } else {
                    return 1; 
                }
            } else if (command == "FDEL_HEAD") {
                if (!fdelHead(values)) {
                    return 1;
                }
            } else if (command == "FDEL_TAIL") {
                if (!fdelTail(values)) {
                    return 1;
                }
            } else if (command == "FDEL_AFTER") {
                if (!fdelAfter(values, param1)) {
                    return 1;
                }
            } else if (command == "FADD_BEFORE") {
                if (faddBefore(values, param1, param2)) {
                    cout << "Успешно: FADD_BEFORE (перед " << param1 << ") " << param2 << " в " << structName << endl;
                } else {
                    return 1;
                }
            } else if (command == "FDEL_BEFORE") {
                if (!fdelBefore(values, param1)) {
                    return 1;
                }
            } else {
                cerr << "Ошибка: Неизвестная команда LIST: " << command << endl;
                return 1;
            }
        
        } else if(typePrefix == 'L'){
            if (s.type != "DUAL_LIST") {
                cerr << "Ошибка: Структура " << structName << " имеет тип " << s.type << ", ожидался DUAL_LIST." << endl;
                return 1;
            }
            if (command == "LPUSH_LEFT"){
                if (lpushLeft(values, param1)){
                    cout << "Успешно: LPUSH_LEFT (в начало) " << param1 << " в " << structName << endl;
                }
            } else if (command == "LPUSH_RIGHT"){
                if (lpushRight(values, param1)){
                    cout << "Успешно: LPUSH_RIGHT (в конец) " << param1 << " в " << structName << endl;
                }
            } else if (command == "LADD_BEFORE") {
                if (laddBefore(values, param1, param2)) { 
                    cout << "Успешно: LADD_BEFORE (добавлен " << param2 << " перед " << param1 << ") в " << structName << endl;
                } else {
                    return 1;
                }
            } else if (command == "LADD_AFTER") {
                if (laddAfter(values, param1, param2)) { 
                    cout << "Успешно: LADD_AFTER (добавлен " << param2 << " после " << param1 << ") в " << structName << endl;
                } else {
                    return 1;
                }
            } else if (command == "LDEL") {
                if (ldel(values, param1)) {
                    cout << "Успешно: LDEL (удален " << param1 << ") из " << structName << endl;
                } else {
                    return 1; 
                }
            } else if (command == "LGET") {
                if (lget(values, param1)) {
                } else {
                    return 1; 
                }
            } else if (command == "LDEL_HEAD") {
                if (!ldelHead(values)) {
                    return 1;
                }
            } else if (command == "LDEL_TAIL") {
                if (!ldelTail(values)) {
                    return 1;
                }
            } else if (command == "LDEL_BEFORE") {
                if (!ldelBefore(values, param1)) {
                    return 1;
                }
            } else if (command == "LDEL_AFTER") {
                if (!ldelAfter(values, param1)) {
                    return 1;
                }
            } else {
                cerr << "Ошибка: Неизвестная команда DUAL_LIST: " << command << endl;
                return 1;
            }
        } else if (typePrefix == 'M') {
            if (s.type != "ARRAY") {
                cerr << "Ошибка: Структура " << structName << " имеет тип " << s.type 
                     << ", ожидался ARRAY." << endl;
                return 1;
            }
    
            if (command == "MARRAY") {
                if (!marrayCreate(values, param1)) {
                    return 1;
                }
            } else if (command == "MADD") {
                if (!madd(values, param1)) {
                    return 1;
                }
            } else if (command == "MINDEXADD") {
                if (!mindexAdd(values, param1, param2)) {
                    return 1;
                }
            } else if (command == "MGET") {
                if (!mget(values, param1)) {
                    return 1;
                }
            } else if (command == "MDELETE") {
                if (!mdeleteIndex(values, param1)) {
                    return 1;
                }
            } else if (command == "MREPLACE") {
                if (!mreplace(values, param1, param2)) {
                    return 1;
                }
            } else if (command == "MLENGTH") {
                if (!mlength(values)) {
                    return 1;
                }
            } else {
                cerr << "Ошибка: Неизвестная команда ARRAY: " << command << endl;
                return 1;
            }
        } else if (typePrefix == 'Q') {
            if (s.type != "QUEUE") {
                cerr << "Ошибка: Структура " << structName << " имеет тип " << s.type 
                     << ", ожидался QUEUE." << endl;
                return 1;
            }
    
            if (command == "QPUSH") {
                if (!qpush(values, param1)) {
                    return 1;
                }
            } else if (command == "QPOP") {
                if (!qpop(values)) {
                    return 1;
                }
            } else {
                cerr << "Ошибка: Неизвестная команда QUEUE: " << command << endl;
                return 1;
            }
        } else if (typePrefix == 'S') {
            if (s.type != "STACK") {
                cerr << "Ошибка: Структура " << structName << " имеет тип " << s.type 
                     << ", ожидался STACK." << endl;
                return 1;
            }
    
            if (command == "SPUSH") {
                if (!spush(values, param1)) {
                    return 1;
                }
            } else if (command == "SPOP") {
                if (!spop(values)) {
                    return 1;
                }
            } else {
                cerr << "Ошибка: Неизвестная команда STACK: " << command << endl;
                return 1;
            }
        } else if (typePrefix == 'T') {
            if (s.type != "TREE") {
                cerr << "Ошибка: Структура " << structName << " имеет тип " << s.type 
                     << ", ожидался TREE." << endl;
                return 1;
            }
    
            if (command == "TADD") {
                if (!tadd(values, param1)) {
                    return 1;
                }
            } else if (command == "TSEARCH") {
                if (!tsearch(values, param1)) {
                    return 1;
                }
            } else if (command == "TISFULL") {
                if (!tisFull(values)) {
                    return 1;
                }
            } else if (command == "TPRINT") {
                tprint(values);
            } else {
                cerr << "Ошибка: Неизвестная команда TREE: " << command << endl;
                return 1;
            }
        } else {
            cerr << "Ошибка: Неизвестный префикс команды: " << typePrefix << endl;
            return 1;
        }
    }
    saveData(file, db);
    return 0;
}
