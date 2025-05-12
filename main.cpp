#include "pack.hpp"
using namespace std;
using namespace PACK;
int main() {
    post post;
    pack *arr = nullptr;
    int count = 0;
    int a;
    do {
        //убрал load птмчт хрен пойми че он делает, тупо занулял все значения посылок
        cout << ("1. Показать список посылок\n") << endl;
        cout << ("2. добавить посылку\n") << endl;
        cout << ("3. Удалить посылку\n") << endl;
        cout << ("4. Изменить данные посылки\n") << endl;
        cout << ("5. Найти посылку\n") << endl;
        cout << ("6. Показать список отделений\n") << endl;
        cout << ("7. Добавить отделение\n") << endl;
        cout << ("0. Выйти\n") << endl;
        cin >> a;
        switch (a) {
        case 1:
            showList(arr, count);
            break;
        case 2:
            add(&arr, &count);
            break;
        case 3:
            del(arr, &count);
            break;
        case 4:
            edit(arr, count);
            break;
        case 5:
            search(arr, count);
            break;
        case 6:
            post.display();
            break;
        case 7:
            post.addpost();
            break;
        case 0:
            cout << "" << endl;
            save(arr, count);
            delete[] arr;
            break;
        default:
            printf("hz \n");
        }
    } while (a != 0);
    return 0;}
