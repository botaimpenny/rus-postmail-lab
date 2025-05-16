#include <iostream>
#include <string>
#include <vector>
/**
 * @namespace PACK
 * @brief Пространство имен, содержащее классы и функции для работы с почтовой системой.
 */
namespace PACK {
/**
 * @class pack
 * @brief Класс, представляющий почтовую посылку.
 */
    class pack {
    public:
        std::string _sendname; 
        std::string _getname;  
        int _from;             
        int _to;              
        int _weight;           
        int _id;               
        int _remainingTime;    
/**
 * @brief Конструктор по умолчанию.
 */
        pack() = default;
/**
 * @brief Конструктор с параметрами.
 * @param sendname Имя отправителя.
 * @param getname Имя получателя.
 * @param from Индекс отправочного отделения.
 * @param to Индекс приемного отделения.
 * @param weight Вес посылки.
 * @param id Трек-номер.
 * @param remainingTime Оставшееся время доставки.
 */
        pack(std::string sendname, std::string getname, int from, int to, int weight, int id, int remainingTime);

    std::string sendname(); ///< Возвращает имя отправителя.
std::string getname();  ///< Возвращает имя получателя.
int from();             ///< Возвращает индекс отправочного отделения.
int to();               ///< Возвращает индекс приемного отделения.
int weight();           ///< Возвращает вес посылки.
int id();               ///< Возвращает трек-номер.
int remainingTime() const; ///< Возвращает оставшееся время доставки.
void setRemainingTime(int time); ///< Устанавливает оставшееся время доставки.

        /**
 * @brief Оператор вывода для класса pack.
 * @param out Поток вывода.
 * @param p Объект класса pack.
 * @return Поток вывода.
 */
        friend std::ostream& operator<<(std::ostream& out, const pack& p);
/**
 * @brief Оператор ввода для класса pack.
 * @param in Поток ввода.
 * @param p Объект класса pack.
 * @return Поток ввода.
 */
        friend std::istream& operator>>(std::istream& in, pack& p);

    void setGetname(const std::string& getname); ///< Устанавливает имя получателя.
void setSendname(const std::string& sendname); ///< Устанавливает имя отправителя.
void setFrom(int from); ///< Устанавливает индекс отправочного отделения.
void setTo(int to); ///< Устанавливает индекс приемного отделения.
void setWeight(int weight); ///< Устанавливает вес посылки.
void setId(int id); ///< Устанавливает трек-номер.
    };
/**
* @class post
* @brief Класс, представляющий почтовое отделение.
*/
    class post {
        std::string _name;
        int index;
        int _x; 
        int _y; 
        std::vector<int> _packs; 

    public:
        post() = default;
/**
 * @brief Конструктор с параметрами.
 * @param index Индекс отделения.
 * @param x Координата X.
 * @param y Координата Y.
 * @param packs Список трек-номеров посылок.
 */
        post(int index, int x, int y, std::vector<int> packs);

    void display(); ///< Выводит информацию о всех отделениях.
void addpost(); ///< Добавляет новое почтовое отделение.
void delpost(pack* arr, int count); ///< Удаляет почтовое отделение.
static double distance(pack* arr, int count, int id); ///< Рассчитывает время доставки посылки.
    };

pack* load(int& count); ///< Загружает данные о посылках из файла.
void save(pack* arr, int count); ///< Сохраняет данные о посылках в файл.
void add(pack** arr, int* count); ///< Добавляет новую посылку.
void del(pack* arr, int* count); ///< Удаляет посылку.
void edit(pack* arr, int count); ///< Редактирует посылку.
void search(pack* arr, int count); ///< Ищет посылку.
void showList(pack* arr, int count); ///< Выводит список посылок.
void give(pack* arr, int* count); ///< Выдает посылку получателю.
void advanceTime(pack* arr, int count); ///< Пропускает время для всех посылок.
}
