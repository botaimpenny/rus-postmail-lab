#include "pack.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
using namespace PACK;

// Реализация конструктора
pack::pack(string sendname, string getname, int from, int to, int weight, int id, int remainingTime)
    : _sendname(sendname), _getname(getname), _from(from), _to(to), _weight(weight), _id(id), _remainingTime(remainingTime) {}

// Геттеры
string pack::sendname() { return _sendname; }
string pack::getname() { return _getname; }
int pack::from() { return _from; }
int pack::to() { return _to; }
int pack::weight() { return _weight; }
int pack::id() { return _id; }
int pack::remainingTime() const { return _remainingTime; }

void pack::setRemainingTime(int time) { _remainingTime = time; }

// Перегрузка операторов ввода/вывода
ostream& operator<<(ostream& out, const pack& p) {
    out << "Имя отправителя: " << p._sendname << ", "
        << "Имя получателя: " << p._getname << ", "
        << "Отправочное отделение: " << p._from << ", "
        << "Приемное отделение: " << p._to << ", "
        << "Трек номер: " << p._id << ", "
        << "Вес: " << p._weight << " кг";
    return out;
}

istream& operator>>(istream& in, pack& p) {
    in >> p._sendname >> p._getname >> p._from >> p._to >> p._id >> p._weight;
    return in;
}

// Загрузка данных из файла
pack* PACK::load(int& count) {
    ifstream in("packages.txt");
    if (!in.is_open()) {
        cout << "Не удалось открыть файл для чтения." << endl;
        count = 0;
        return nullptr;
    }
    in >> count;
    pack* arr = new pack[count];
    for (int i = 0; i < count; i++) {
        if (!(in >> arr[i]._sendname >> arr[i]._getname >> arr[i]._from >> arr[i]._to >> arr[i]._id >> arr[i]._weight)) {
            cerr << "Ошибка чтения данных для посылки #" << i + 1 << endl;
            delete[] arr;
            count = 0;
            return nullptr;
        }
    }
    in.close();
    return arr;
}

// Сохранение данных в файл
void PACK::save(pack* arr, int count) {
    ofstream out("packages.txt");
    out << count << endl;
    for (int i = 0; i < count; i++) {
        out << arr[i]._sendname << " "
            << arr[i]._getname << " "
            << arr[i]._from << " "
            << arr[i]._to << " "
            << arr[i]._id << " "
            << arr[i]._weight << endl;
    }
    out.close();
}

// Добавление посылки
void PACK::add(pack** arr, int* count) {
    pack* temp = new pack[*count + 1];
    for (int i = 0; i < *count; i++) {
        temp[i] = (*arr)[i];
    }
    string sendname, getname;
    int from, to, id, weight;
    cout << "Введите имя отправителя: ";
    cin >> sendname;
    cout << "Введите имя получателя: ";
    cin >> getname;
    cout << "Введите отправочное отделение: ";
    cin >> from;
    cout << "Введите приемное отделение: ";
    cin >> to;
    cout << "Введите трек-номер: ";
    cin >> id;
    cout << "Введите вес: ";
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

// Удаление посылки
void PACK::del(pack* arr, int* count) {
    int id;
    cout << "Введите трек-номер для удаления: ";
    cin >> id;
    int index = -1;
    for (int i = 0; i < *count; i++) {
        if (arr[i].id() == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        cout << "Такого трек-номера не существует." << endl;
        return;
    }
    for (int i = index; i < *count - 1; i++) {
        arr[i] = arr[i + 1];
    }
    (*count)--;
    cout << "Посылка удалена." << endl;
}

// Отображение почтовых отделений
void post::display() {
    string line;
    ifstream file("posts.txt");
    if (file.is_open()) {
        int n = 1;
        while (getline(file, line)) {
            istringstream iss(line);
            int index, x, y;
            vector<int> packs;
            iss >> index >> x >> y;
            int trak;
            while (iss >> trak) {
                packs.push_back(trak);
            }
            cout << n << ". Индекс: " << index << ", Координаты: (" << x << ", " << y << "), Трек-номера: ";
            for (size_t i = 0; i < packs.size(); ++i) {
                cout << packs[i];
                if (i < packs.size() - 1) cout << ", ";
            }
            cout << endl;
            n++;
        }
        cout << "---------------" << endl;
        file.close();
    } else {
        cout << "Не удалось открыть файл." << endl;
    }
}

// Добавить новое почтовое отделение
void post::addpost() {
    cout << "Введите название нового почтового отделения: ";
    cin >> _name;
    int index;
    cout << "Введите индекс нового почтового отделения: ";
    cin >> index;
    cout << "Введите координату X: ";
    cin >> _x;
    cout << "Введите координату Y: ";
    cin >> _y;
    ofstream file("posts.txt", ios::app);
    if (file.is_open()) {
        file << index << " " << _x << " " << _y << " \n";
        file.close();
        cout << "Почтовое отделение добавлено успешно\n" << endl;
    } else {
        cout << "Не удалось открыть файл для записи\n" << endl;
    }
}

// Расчет времени пути
double post::distance(pack* arr, int count) {
    ifstream file("posts.txt");
    if (!file.is_open()) {
        cout << "Не удалось открыть файл posts.txt" << endl;
        return -1;
    }
    int id, from = 0, to = 0;
    cout << "Введите трек-номер: ";
    cin >> id;
    for (int i = 0; i < count; i++) {
        if (arr[i].id() == id) {
            from = arr[i].from();
            to = arr[i].to();
            break;
        }
    }

    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    bool foundFrom = false, foundTo = false;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int index, x, y;
        iss >> index >> x >> y;
        if (index == from) {
            x1 = x;
            y1 = y;
            foundFrom = true;
        }
        if (index == to) {
            x2 = x;
            y2 = y;
            foundTo = true;
        }
        if (foundFrom && foundTo) break;
    }
    file.close();

    if (!foundFrom || !foundTo) {
        cout << "Ошибка: одно из отделений не найдено." << endl;
        return -1;
    }

    double dist = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    int time = static_cast<int>(ceil(dist / 10));
    arr[0].setRemainingTime(time); // Пример установки времени первой посылке
    cout << "Время доставки: " << time << " дней" << endl;
    return time;
}

// Удаление почтового отделения
void post::delpost(pack* arr, int count) {
    vector<string> lines;
    string line;
    ifstream in("posts.txt");
    while (getline(in, line)) {
        lines.push_back(line);
    }
    in.close();

    cout << "Список почтовых отделений:" << endl;
    for (size_t i = 0; i < lines.size(); ++i) {
        cout << i + 1 << ") " << lines[i] << endl;
    }

    cout << "Введите номер отделения для удаления: ";
    size_t num;
    cin >> num;

    if (num > 0 && num <= lines.size()) {
        istringstream iss(lines[num - 1]);
        int index, x, y;
        vector<int> packs;
        iss >> index >> x >> y;
        int trak;
        while (iss >> trak) {
            packs.push_back(trak);
        }

        for (int track : packs) {
            for (int i = 0; i < count; i++) {
                if (arr[i].id() == track) {
                    arr[i].setTo(arr[i].from());
                    cout << "Посылка с трек-номером " << track
                         << " отправлена обратно в отделение " << arr[i].from() << endl;
                }
            }
        }

        lines.erase(lines.begin() + num - 1);
        ofstream out("posts.txt");
        for (const auto& l : lines) {
            out << l << endl;
        }
        out.close();
        save(arr, count);
        cout << "Отделение успешно удалено. Все посылки отправлены обратно." << endl;
    } else {
        cout << "Неверный номер отделения." << endl;
    }
}

// Выдача посылки
void PACK::give(pack* arr, int* count){
    int id;
    string nameTest, name;
    cout << "Введите трек номер: ";
    cin >> id;
    for (int i = 0; i < *count; i++) {
        if (arr[i].id() == id) {
            nameTest = arr[i].getname();
        }
    }
    cout << "Введите имя получателя: ";
    cin >> name;
    if(name == nameTest){
        cout << "Посылка получена!" << endl;
        int index = -1;
        for (int i = 0; i < *count; i++) {
            if (arr[i].id() == id) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            for (int i = index; i < *count - 1; i++) {
                arr[i] = arr[i + 1];
            }
            (*count)--;
            cout << "Посылка удалена." << endl;
        } else {
            cout << "Такого трек номера не существует." << endl;
        }
    } else {
        cout << "Имя не совпадает. Получение невозможно." << endl;
    }
}

// Пропуск одного дня — реализация advanceTime()
void PACK::advanceTime(pack* arr, int count) {
    for (int i = 0; i < count; i++) {
        int remTime = arr[i].remainingTime();
        if (remTime > 0) {
            arr[i].setRemainingTime(remTime - 1);
            cout << "Посылка с трек-номером " << arr[i].id()
                 << " осталось времени: " << arr[i].remainingTime() << " дней" << endl;
        } else {
            cout << "Посылка с трек-номером " << arr[i].id() << " уже доставлена." << endl;
        }
    }
}

