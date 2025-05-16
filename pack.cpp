/**
 * @file pack.cpp
 * @brief Реализация методов классов и функций для работы с почтовыми посылками и отделениями.
*/
#include "pack.hpp"
    #include <fstream>
    #include <sstream>
    #include <iostream>
    #include <cmath>
    using namespace std;
    using namespace PACK;
    
    /**
 * @brief Конструктор класса pack.
 * @param sendname Имя отправителя.
 * @param getname Имя получателя.
 * @param from Индекс отправочного отделения.
 * @param to Индекс приемного отделения.
 * @param weight Вес посылки.
 * @param id Трек-номер.
 * @param remainingTime Оставшееся время доставки.
 */
    pack::pack(string sendname, string getname, int from, int to, int weight, int id, int remainingTime)
        : _sendname(sendname), _getname(getname), _from(from), _to(to), _weight(weight), _id(id), _remainingTime(0) {
    }
    
    string pack::sendname() { return _sendname; }
    string pack::getname() { return _getname; }
    int pack::from() { return _from; }
    int pack::to() { return _to; }
    int pack::weight() { return _weight; }
    int pack::id() { return _id; }
    int pack::remainingTime() const{ return _remainingTime; }
    void pack::setRemainingTime(int time) { _remainingTime = time; }
    /**
 * @brief Оператор вывода для класса pack.
 * @param out Поток вывода.
 * @param p Объект класса pack.
 * @return Поток вывода.
 */
    ostream& operator<<(ostream& out, const pack& p) {
        out << " " << p._sendname << " "
            << " " << p._getname << " "
            << " " << p._from << " "
            << " " << p._to << " "
            << " " << p._id << " "
            << " " << p._weight << " ";
        return out;
    }
    /**
 * @brief Оператор ввода для класса pack.
 * @param in Поток ввода.
 * @param p Объект класса pack.
 * @return Поток ввода.
 */
    istream& operator>>(istream& in, pack& p) {
        in >> p._sendname >> p._getname >> p._from >> p._to >> p._id >> p._weight;
        return in;
    }
    
    /**
 * @brief Загружает данные о посылках из файла.
 * @param count Ссылка на переменную, в которую будет записано количество посылок.
 * @return Указатель на массив посылок.
 */
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
            int remainingTime;
            if (!(in >> arr[i]._sendname >> arr[i]._getname >> arr[i]._from >> arr[i]._to >> arr[i]._id >> arr[i]._weight >> remainingTime)) {
                cerr << "Ошибка чтения данных для посылки #" << i + 1 << endl;
                delete[] arr; // Освобождаем память при ошибке
                count = 0;
                return nullptr;
            }
            arr[i].setRemainingTime(remainingTime); // Устанавливаем оставшееся время
        }
        in.close();
        return arr;
    }
    
    /**
 * @brief Сохраняет данные о посылках в файл.
 * @param arr Указатель на массив посылок.
 * @param count Количество посылок.
 */
    void PACK::save(pack* arr, int count) {
        ofstream out("packages.txt");
        out << count << endl;
        for (int i = 0; i < count; i++) {
            out << arr[i]._sendname << " "
                << arr[i]._getname << " "
                << arr[i]._from << " "
                << arr[i]._to << " "
                << arr[i]._id << " "
                << arr[i]._weight << " "
                << arr[i].remainingTime() << endl; // Сохраняем оставшееся время
        }
        out.close();
    }
    /**
 * @brief Добавляет новую посылку.
 * @param arr Указатель на массив посылок.
 * @param count Указатель на переменную с количеством посылок.
 */
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
    /**
 * @brief Удаляет посылку.
 * @param arr Указатель на массив посылок.
 */
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
/**
 * @brief Показывает отделения почты.
 */
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
                cout << n << ". Индекс почтового отделения: " << index << ", "
                     << "Координата X: " << x << ", "
                     << "Координата Y: " << y << ", ";
                for (size_t i = 0; i < packs.size(); i++) {
                    cout << packs[i];
                    if (i < packs.size() - 1) {
                        cout << ", ";
                    }
                 }
                cout << endl;
                n++;
            }
             cout << "---------------" << endl;
            file.close();
        } else {
            cout << "Не удалось открыть файл." << endl;
        }}
/**
 * @brief Добавляет новое отделение.

 */
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

        ofstream file("posts.txt", ios::app);
        if (file.is_open()) {
            file << index << " " << _x << " " << _y << "\n"; // Запись индекса и координат
        file.close();
        cout << "Почтовое отделение добавлено успешно\n" << endl;
        }
        else {
            cout << "Не удалось открыть файл для записи\n" << endl;
        }
    }
    /**
 * @brief Рассчитывает время пути
 */
    double post::distance(pack* arr, int count, int id) {
        ifstream file("posts.txt");
        if (!file.is_open()) {
            cout << "Не удалось открыть файл posts.txt" << endl;
            return -1;
        }
    
        int from = 0, to = 0;
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
    
            if (foundFrom && foundTo) {
                break;
            }
        }
        file.close();
    
        if (!foundFrom || !foundTo) {
            cout << "Ошибка: одно из отделений не найдено." << endl;
            return -1;
        }
    
        double dist = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
        int time = static_cast<int>(ceil(dist / 10)); // Скорость доставки: 10 единиц расстояния в день
        cout << "Время доставки: " << time << " дней" << endl;
        return time;
    }
/**
 * @brief Удаляет отделение
 */
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
        }
        else {
            cout << "Неверный номер отделения." << endl;
        }
    }
    /**
 * @brief Выдает посылку
 */
    void PACK::give(pack* arr, int* count){
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
	   // cout << id << endl;
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
		cout << id << endl;
                (*count)--;
                cout << "Посылка удалена." << endl;
            }
    
        }
/**
 * @brief Перематывает время(должна)
 */
    void PACK::advanceTime(pack* arr, int count) {
        for (int i = 0; i < count; i++) {
            int remainingTime = arr[i].remainingTime(); // Получаем текущее оставшееся время
            cout << "time:" << remainingTime << endl;
            if (remainingTime > 0) {
                arr[i].setRemainingTime(remainingTime - 1); // Уменьшаем время на 1 день
                cout << "Посылка с трек-номером " << arr[i].id() << " осталось времени: " << arr[i].remainingTime() << " дней" << endl;
            } else {
                cout << "Посылка с трек-номером " << arr[i].id() << " уже доставлена." << endl;
            }
        }
    }
