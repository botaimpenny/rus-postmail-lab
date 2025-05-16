#include "pack.hpp"
using namespace std;
using namespace PACK;

int main() {
    post post;
    pack* arr = nullptr;
    int count = 0;
    int a;

    do {
        cout << "1. Отправить посылку\n"
            << "2. Добавить отделение\n"
            << "3. Удалить отделение\n"
            << "4. Узнать информацию о отделении\n"
            << "5. Отследить посылку по трек номеру\n"
            << "6. Выдать посылку\n"
            << "7. Пропуск времени\n"
            << "0. Выйти\n";
        cin >> a;

        switch (a) {
        case 1:
            add(arr, &count);
            break;
        case 2:
            post.addpost();
            break;
        case 3:
            post.delpost(arr, count);
            break;
        case 4:
            post.display();
            break;
        case 5:
            cout << "Введите трек номер: ";
            int id;
            cin >> id;
            post.distance(arr, count, id);
            break;
        case 6:
            give(arr, &count);
            break;
        case 7:
            advanceTime(arr, count);
            break;
        case 0:
            cout << "Выход из программы." << endl;
            save(arr, count);
            delete[] arr;
            break;
        default:
            cout << "Неверный ввод. Пожалуйста, попробуйте снова." << endl;
        }
    } while (a != 0);

    return 0;
}

