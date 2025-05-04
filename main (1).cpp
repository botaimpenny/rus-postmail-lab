#include "pack.h"
using namespace std;
using namespace PACK;
int main() {
    post post;
    pack *arr = nullptr;
    int count = 0;
    arr = load(count);
    int a;
    do {
        cout << ("Список посылок\n") << endl;
        cout << ("1. загрузить посылку\n") << endl;
        cout << ("2. Показать список посылок\n") << endl;
        cout << ("3. добавить посылку\n") << endl;
        cout << ("4. Удалить посылку\n") << endl;
        cout << ("5. Изменить данные посылки\n") << endl;
        cout << ("6. Найти посылку\n") << endl;
        cout << ("7. Показать список отделений\n") << endl;
        cout << ("8. Добывить отделение\n") << endl;
        cout << ("0. выйти\n") << endl;
        cin >> a;
        switch (a) {
        case 1:
            arr = create(count);
            break;
        case 2:
            showList(arr, count);
            break;
        case 3:
            add(&arr, &count);
            break;
        case 4:
            del(arr, &count);
            break;
        case 5:
            edit(arr, count);
            break;
        case 6:
            search(arr, count);
            break;
        case 7:
            post.display();
            break;
        case 8:
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
