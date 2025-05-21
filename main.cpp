#include <iostream>
#include "head.h"

using namespace std;
using namespace PACK;
int main()
{
    int a;
    do {
           cout << "\n--- Меню ---\n"
                << "1. Отправить посылку\n"
                << "2. Добавить отделение\n"
                << "3. Удалить отделение\n"
                << "4. Показать информацию об отделениях\n"
                << "5. Выдать посылку\n"
                << "6. Пропустить день\n"
                << "0. Выйти\n"
                << "Выберите действие: ";
           cin >> a;

           switch (a) {
               case 1: add(); break;
               case 2: addpost(); break;
               case 3: delpost(); break;
               case 4: display(); break;
               case 5: give(); break;
               case 6: time(); break;
               case 0:
                   cout << "Выход." << endl;
                   break;
               default:
                   cout << "Неверный выбор. Повторите." << endl;
           }
       } while (a != 0);

       return 0;
   }
