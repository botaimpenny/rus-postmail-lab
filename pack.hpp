#include <iostream>
#include <string>
#include <vector>
namespace PACK {//PACK=посылка
class pack {
    std::string _sendname;//имя отправителя
    std::string _getname;//имя получателя
    std::string _from; //откуда отправляется
    std::string _to;//куда отправляется
    int _weight;//вес посылки
    int _id; //трек номер

public:
    pack() = default;
    pack(std::string sendname, std::string getname, std::string from, std::string to, int weight, int id);
    std::string sendname();
    std::string getname();
    std::string from();
    std::string to();
    int weight();
    int id();
    friend std::ostream& operator << (std::ostream & out, const pack& p);
    friend std::istream& operator >> (std::istream & in, pack& p);
    void setGetname(const std::string& getname) { _getname = getname; }
    void setSendname(const std::string& sendname) { _sendname = sendname; }
    void setFrom(const std::string& from) { _from = from; }
    void setTo(const std::string& to) { _to = to; }
    void setWeight (int weight) { _weight = weight; }
    void setId(int id) { _id = id; }
};
class post {
    int _x;//Координата отделения по х
    int _y;//Координата отделения по у
    std::vector <int> _packs;//Список посылок внутри отделения
public:
    post() = default;
    post(int x, int y, std::vector <int> packs);
    friend std::ostream& operator << (std::ostream & out, post& p);
    friend std::istream& operator >> (std::istream & in, post& p);
    void display();
    void delpost();
    void addpost();

};

std::ostream& operator << (std::ostream & out, const pack& p);
std::istream& operator >> (std::istream & in, pack& p);
pack * load(int & count);
pack * create(int & count);
void save(pack *arr, int count);
void add(pack **arr, int *count);
void del(pack *arr, int *count);
void edit(pack *arr, int count);
void search(pack *arr, int count);
void showList(pack *arr, int count);

}
