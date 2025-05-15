#include "pack.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
using namespace std;
using namespace PACK;

string pack::getname() {
    return _getname;
}
string pack::sendname() {
    return _sendname;
}
int pack::from() {
    return _from;
}
int pack::to() {
    return _to;
}
int pack::id() {
    return _id;
}
int pack::weight() {
    return _weight;
}
pack* PACK::load(int &count) {
    ifstream in("packages.txt");
    if (!in.is_open()) {
        cerr << "error: cant open packages.txt" << endl;
        count = 0;
        return nullptr;
    }
    // Чтение количества посылок
    if (!(in >> count)) {
        cerr << "error: incorrect type of file" << endl;
        count = 0;
        return nullptr;
    }
    if (count <= 0) {
        cerr << "incorrect amount of packages: " << count << endl;
        return nullptr;
    }

    // Выделение памяти
    pack* arr = new (nothrow) pack[count];
    if (!arr) {
        cerr << "error: cant fill memory for " << count << "packages" << endl;
        count = 0;
        return nullptr;
    }

    // Чтение посылок
    for (int i = 0; i < count; ++i) {
        if (!(in >> arr[i])) {
            cerr << "error: cant read #" << i+1 << endl;
            delete[] arr;  // Освобождаем память при ошибке
            count = 0;
            return nullptr;
        }
 else{
     in >> arr[i];
 }
    }
    in.close();
    return arr;
}

pack::pack(string sendname, string getname, int from, int to, int id, int weight) 
    : _sendname(sendname), _getname(getname), _from(from), _to(to), _id(id), _weight(weight) {}

ostream& PACK::operator<<(ostream & out, const pack& p) {
  out << p._sendname << " "
        << p._getname << " "
        << p._from << " "
        << p._to << " "
        << p._id << " "
        << p._weight;
        return out;
}

istream& PACK::operator>>(istream & in, pack& p) {
    in >> p._sendname >> p._getname >> p._from >> p._to >> p._id >> p._weight;
    return in;
}

pack* PACK::create(int & count) {
    count = 1;
    pack* arr = new pack[count];
    return arr;
}

void PACK::save(pack* arr, int count) {
    ofstream out("packages.txt");
    out << count << endl;
    for (int i = 0; i < count; i++) {
        out << arr[i] << endl;
    }
    out.close();
}

void PACK::add(pack** arr, int* count) {
    pack* temp = new (nothrow) pack[*count + 1];
    if (temp == nullptr) {
        cout << "Memory error" << endl;
        return;
    }
    for (int i = 0; i < *count; i++) {
        temp[i] = (*arr)[i];
    }

    string sendname, getname;
    int from, to, id, weight;

    cout << "Введите имя отправителя посылки: " << endl;
    cin >> sendname;
    cout << "Введите имя получателя посылки: " << endl;
    cin >> getname;
    cout << "Введите отделение почты, откуда едет посылка: " << endl;
    cin >> from;
    cout << "Введите отделение почты, куда едет посылка: " << endl;
    cin >> to;
    cout << "Введите трек номер посылки: " << endl;
    cin >> id;
    cout << "Введите вес посылки: " << endl;
    cin >> weight;

    temp[*count].setSendname(sendname);
    temp[*count].setGetname(getname);
    temp[*count].setFrom(from);
    temp[*count].setTo(to);
    temp[*count].setId(id);
    temp[*count].setWeight(weight);

    delete[] * arr;
    *arr = temp;
    (*count)++;
}

void PACK::del(pack* arr, int* count) {
    int n = 0;
    cout << "Введите трек номер посылки: " << endl;
    cin >> n;
    int index = -1;
    for (int i = 0; i < *count; i++) {
        if (arr[i].id() == n) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Такого трек номера не существует " << endl;
        return;
    }

    for (int i = index; i < *count - 1; i++) {
        arr[i] = arr[i + 1];
    }
    (*count)--;
    cout << "Посылка удалена." << endl;
}

void PACK::edit(pack *arr, int count) {
    int n = 0;
    cout << "Введите трек номер посылки для редактирования: " << endl;
    cin >> n;

    // Теперь ищет действительно по айди, а не по индексу в файле
    int index = -1;
    for (int i = 0; i < count; i++) {
        if (arr[i].id() == n) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Такого трек номера не существует " << endl;
        return;
    }
    
string temp;
    cout << "Введите новое имя отправителя: " << endl;
    cin >> temp;
    arr[index].setSendname(temp);
    cout << "Введите новое имя получателя: " << endl;
    cin >> temp;
    arr[index].setGetname(temp);
    int from = 0;
    cout << "Введите новое отделение почты, откуда едет посылка: " << endl;
    cin >> from;
    arr[index].setFrom(from);
    int to = 0;
    cout << "Введите новое отделение почты, куда едет посылка: " << endl;
    cin >> to;
    arr[index].setTo(to);
    int id = 0;
    cout << "Введите новый трек номер посылки: " << endl;
    cin >> id;
    arr[index].setId(id);
    int weight = 0;
    cout << "Укажите новый вес посылки: " << endl;
    cin >> weight;
    arr[index].setWeight(weight);
    // | сделал функцию записи в файл прям здесь, если надо меняйте, я задолбался,аахахах
    ofstream outFile("packages.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < count; i++) {
            outFile << arr[i] << endl;
 }
        outFile.close();
    }
    else {
        cout << "Не удалось открыть файл для записи." << endl;
    }
}

void PACK::search(pack* arr, int count) {
    string sendname;
    string getname;
    int from;
    int to;
    int weight;
    int id;
    int ch;
    cout << "По какому критерию искать?\n1 - Имя отправителя\n2 - Имя получателя\n3 - Трек номер\n" << endl;
    cin >> ch;
    switch(ch){
    case 1:{
        cout << "Введите имя отправителя: ";
        cin >> sendname;
        for (int i = 0; i < count; i++) {
            if (arr[i].sendname() == sendname) {
                cout << "Найдена посылка: " << endl;
                cout << arr[i] << endl;
                break;
            }
        }
    }
    case 2:{
        cout << "Введите имя получателя: ";
        cin >> getname;
        for (int i = 0; i < count; i++) {
            if (arr[i].getname() == getname) {
                cout << "Найдена посылка: " << endl;
                cout << arr[i] << endl;
                break;
            }
        }
    }
    case 3:{
        cout << "Введите трек номер посылки: ";
        cin >> id;
        for (int i = 0; i < count; i++) {
            if (arr[i].id() == id) {
                cout << "Найдена посылка: " << endl;
                cout << arr[i] << endl;
                break;
            }
        }
    }
    default:{
        break;
}}}

void PACK::showList(pack* arr, int count) {
    cout << "Список посылок:" << endl;
    for (int i = 0; i < count; i++) {
        cout << i+1 << ". " << arr[i] << endl;
        cout << "-------------------" << endl;
    }
}
void post::display() {
    string line;
    ifstream file("posts.txt");
    if (file.is_open()) {
    int n = 1;
        while (getline(file, line)) {
            istringstream iss(line); // Используем istringstream для разбора строки            
            int index, x, y;
            vector<int> packs;
            // Читаем индекс, координаты и трек-номера
            iss >> index >> x >> y;
            // Читаем трек-номера посылок
            int trak;
            while (iss >> trak) {
                packs.push_back(trak);
            }
            // Выводим данные с подписями
            cout << n << ". Индекс почтового отделения: " << index << ", "
                 << "Координата X: " << x << ", "
                 << "Координата Y: " << y << ", ";
            for (size_t i = 0; i < packs.size(); i++) {
                cout << packs[i];
                if (i < packs.size() - 1) {
                    cout << ", "; // Добавляем запятую между трек-номерами
                }
            }
            cout << endl; // Переход на новую строку
            n++;
        }
         cout << "---------------" << endl;
        file.close();
    } else {
        cout << "Не удалось открыть файл." << endl;
    }
}

void post::addpost() {
    cout << "Введите название нового почтового отделения: ";
    cin >> _name;
    int index;
    cout << "Введите индекс нового почтового отделения: ";
    cin >> index; // Ввод индекса почтового отделения
    cout << "Введите координату X нового почтового отделения: ";
    cin >> _x; // Ввод координаты X
    cout << "Введите координату Y нового почтового отделения: ";
    cin >> _y; // Ввод координаты Y
    int n;
    cin >> n;
ofstream file("posts.txt", ios::app);
    if (file.is_open()) {
        file << index << " " << _x << " " << _y << " "; // Запись индекса и координат
        for (int trak : _packs) {
            file << trak << " "; // Запись трек-номеров
        }
        file << endl; // Переход на новую строку
        file.close();
        cout << "Почтовое отделение добавлено успешно." << endl;
    } else {
        cout << "Не удалось открыть файл для записи." << endl;
    }
}

double PACK::post::distance(pack* arr, int count){
        ifstream file("packs.txt");
        if (file.is_open()) {
            int x1 = 0;
            int y1 = 0;
            int x2 = 0;
            int y2 = 0;
            int from;
            int to;
            int id;
            double dis;

            cout << "Введите трек номер: ";
            cin >> id;
            for (int i = 0; i < count; i++) {
                if (arr[i].id() == id) {
                    from = arr[i].from();
                    to = arr[i].to();
                }
            }
            file.close();
            ifstream file("posts.txt");
            if (file.is_open()){
                while (file >> index >> _x >> _y) {
                    if (from == index){
                        file.close();
                        x1 = _x;
                        y1 = _y;
                    }

                }
            }
            file.close();
            ifstream file1("posts.txt");
            if (file1.is_open()){
                while (file1 >> index >> _x >> _y) {
                    if (to == index){
                        file1.close();
                        x2 = _x;
                        y2 = _y;
                    }

                }
            }
            dis = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
            
            return dis;
        }
    }

void post::delpost() {
    vector<string> lines;
    string line;
    
    // Чтение файла
    ifstream in("posts.txt");
    while (getline(in, line)) {
        lines.push_back(line);
    }
    in.close();

    // Вывод списка
    for (size_t i = 0; i < lines.size(); ++i) {
        cout << i+1 << ") " << lines[i] << endl;
    }

    // Удаление
    cout << "Введите номер для удаления: ";
    size_t num;
    cin >> num;
    if (num > 0 && num <= lines.size()) {
        lines.erase(lines.begin() + num - 1);
    }

    // Запись обратно
    ofstream out("posts.txt");
    for (const auto& l : lines) {
        out << l << endl;
    }
}
    void give(pack* arr, int* count){
        int id;
        string nameTest;
        string name;
        cout << "Введите трек номер: ";
        cin >> id;
        for (int i = 0; i < *count; i++) {
            if (arr[i].id() == id) {
                nameTest = arr[i].getname();
            }
        }
        cout << "Введите имя получателя: " << endl;
        cin >> name;
        if(name == nameTest){
            cout << "Поссылка получена!" << endl;
            int index = -1;
            for (int i = 0; i < *count; i++) {
                if (arr[i].id() == id) {
                    index = i;
                    break;
                }
            }
        
            if (index == -1) {
                cout << "Такого трек номера не существует " << endl;
                return;
            }
        
            for (int i = index; i < *count - 1; i++) {
                arr[i] = arr[i + 1];
            }
            (*count)--;
            cout << "Посылка удалена." << endl;
        }
        
    }
