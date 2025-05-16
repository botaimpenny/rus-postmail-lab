#include "pack.hpp"
#include <iostream>
using namespace std;
using namespace PACK;

int main() {
    post post;
    pack* arr = nullptr;
    int count = 0;

    // Загрузка данных
    arr = load(count);

    int a;
    do {
        cout << "\n--- Меню ---\n"
             << "1. Отправить посылку\n"
             << "2. Добавить отделение\n"
             << "3. Удалить отделение\n"
             << "4. Показать информацию об отделениях\n"
             << "5. Рассчитать время доставки\n"
             << "6. Выдать посылку\n"
             << "7. Пропустить день\n"
             << "0. Выйти\n"
             << "Выберите действие: ";
        cin >> a;

        switch (a) {
            case 1: add(&arr, &count); break;
            case 2: post.addpost(); break;
            case 3: post.delpost(arr, count); break;
            case 4: post.display(); break;
            case 5: post.distance(arr, count); break;
            case 6: give(arr, &count); break;
            case 7: advanceTime(arr, count); break;
            case 0:
                cout << "Выход. Сохранение данных..." << endl;
                save(arr, count);
                delete[] arr;
                break;
            default:
                cout << "Неверный выбор. Повторите." << endl;
        }
    } while (a != 0);

    return 0;
}
