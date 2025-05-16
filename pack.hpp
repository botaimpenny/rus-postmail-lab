#include <iostream>
#include <string>
#include <vector>

namespace PACK {
    class pack {
    public:
        std::string _sendname; // имя отправителя
        std::string _getname;  // имя получателя
        int _from;             // отправочное отделение
        int _to;               // приемное отделение
        int _weight;           // вес посылки
        int _id;               // трек-номер
        int _remainingTime;    // оставшееся время доставки в днях
        pack() = default;
        pack(std::string sendname, std::string getname, int from, int to, int weight, int id, int remainingTime);

        // Геттеры и сеттеры
        std::string sendname();
        std::string getname();
        int from();
        int to();
        int weight();
        int id();
        int remainingTime() const;
        void setRemainingTime(int time);

        // Дружественные операторы для ввода/вывода
        friend std::ostream& operator<<(std::ostream& out, const pack& p);
        friend std::istream& operator>>(std::istream& in, pack& p);

        // Сеттеры для других полей
        void setGetname(const std::string& getname) { _getname = getname; }
        void setSendname(const std::string& sendname) { _sendname = sendname; }
        void setFrom(int from) { _from = from; }
        void setTo(int to) { _to = to; }
        void setWeight(int weight) { _weight = weight; }
        void setId(int id) { _id = id; }
    };

    class post {
        std::string _name;
        int index;
        int _x; // Координата отделения по X
        int _y; // Координата отделения по Y
        std::vector<int> _packs; // Список посылок внутри отделения

    public:
        post() = default;
        post(int index, int x, int y, std::vector<int> packs);

        // Методы
        void display();
        void addpost();
        void delpost(pack* arr, int count);
        static double distance(pack* arr, int count, int id);
    };

    // Внешние функции

    pack* load(int& count);
    void save(pack* arr, int count);
    void add(pack* arr, int* count);
    void del(pack* arr, int* count);
    void edit(pack* arr, int count);
    void search(pack* arr, int count);
    void showList(pack* arr, int count);
    void give(pack* arr, int* count);
    void advanceTime(pack* arr, int count);
}
