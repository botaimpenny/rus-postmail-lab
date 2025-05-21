#include "head.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
namespace PACK{
ostream& operator<<(ostream& os, const PACK::pack& Pack){
    os << Pack.id << " " << Pack.sendname << " " << Pack.getname << " " << Pack.from << " " << Pack.to<< " " <<Pack.weight<< " " << Pack.remainingTime << " " << Pack.currentX<< " " << Pack.currentY << "\n";
    return os;
}

istream& operator>>(istream& is, PACK::pack& Pack){
    is >> Pack.id >> Pack.sendname >> Pack.getname >> Pack.from >> Pack.to>>Pack.weight>>Pack.remainingTime>> Pack.currentX>> Pack.currentY;
    return is;
}

ostream& operator<<(ostream& os, const PACK::post& Post){
    os << Post.name << " " << Post.x << " " << Post.y;
          for (int track : Post.packs) {
              os << " " << track;
          };
          os << '\n';
    return os;
}

istream& operator>>(istream& is, PACK::post& Post){
    string line;
    getline(is, line);
    istringstream iss(line);
    Post.packs.clear();
    iss >> Post.name >> Post.x >> Post.y;
    int track;
    while(iss >> track){
        Post.packs.push_back(track);
    }
    return is;
}
}

int count_strings(string a){ //Пересчёт строк. Для использования:    int a = count_strings("название файла");
    ifstream f;
    f.open(a);
    string line;
    int i = 0;
    while(getline(f, line)){
        i++;
    };
    f.close();
    return i;
}

void PACK::add(){
    pack editable;
    cout << "Введите имя отправителя: ";
    cin >> editable.sendname;
    cout << "Введите имя получателя: ";
    cin >> editable.getname;
    cout << "Введите отправочное отделение: ";
    string from;
    cin >> from;
    editable.from = from;
    editable.currentX = 0;
    editable.currentY = 0;
    ifstream file3("post.txt");
    post editable3;
    int check = 0;
    if (!file3.is_open())
        cout << "Не удалось открыть файл5." << endl;
    while(file3 >> editable3){
        if (from == editable3.name){
            editable.currentX = editable3.x;
            editable.currentY = editable3.y;
            check = 1;
            break;
        }
    }
    file3.close();
    if (check == 0){
        cout << "Такого отправочного отделения не существует." << endl;
        return;
    }

    cout << "Введите приемное отделение: ";
    cin >> editable.to;

    ifstream file4("post.txt");
    post editable4;
    check = 0;
    if (!file4.is_open())
        cout << "Не удалось открыть файл4." << endl;
    while(file4 >> editable4){
        if (editable.to == editable4.name){
            check = 1;
            break;
        }
    }
    file4.close();
    if (check == 0){
        cout << "Такого приемного  отделения не существует." << endl;
        return;
    }

    cout << "Введите вес: ";
    cin >> editable.weight;
    int flag = 1;
    int potencialId = 0;
    while(flag == 1){
        flag = 0;
        potencialId = rand() % 9000 + 1000;
        ifstream file("pack.txt");
        pack editable2;
        if (!file.is_open())
            cout << "Не удалось открыть файл3." << endl;
        while(file >> editable2){
            if (potencialId == editable2.id){
                flag = 1;
                break;
            }
        }
        file.close();
    }
    editable.id = potencialId;
    int x2;
    int y2;
    ifstream file7("post.txt");
    if (!file7.is_open())
        cout << "Не удалось открыть файл7." << endl;
    post editable7;
    while(file7 >> editable7){
        if(editable.to == editable7.name){
            x2 = editable7.x;
            y2 = editable7.y;
        }
    }
    int dist = sqrt(pow(x2 - editable.currentX , 2) + pow(y2 - editable.currentY , 2));
    int speed = 60;
    editable.remainingTime = dist/speed;
    file7.close();
    ofstream file1("pack.txt", ios::app);
    if (!file1.is_open())
        cout << "Не удалось открыть файл1." << endl;
    file1 << editable;
    file1.close();
    vector<post> posts;
    ifstream fin("post.txt");
    post p;

Егор Попельницкий, [5/21/2025 3:23 PM]
while (fin >> p) {
        posts.push_back(p);
    }
    fin.close();
    for(size_t i = 0; i < posts.size();i++)
        if(posts[i].name == editable.to)
            posts[i].packs.push_back(editable.id);
    ofstream fout("post.txt");
    for(size_t i = 0; i < posts.size(); i++){
        fout << posts[i];
    }
}

void PACK::display() {
    string line;
    ifstream file("post.txt");
    if (file.is_open()) {
        int n = 1;
        while (getline(file, line)) {
            istringstream iss(line);
            string name;
            int  x, y;
            vector<int> packs;
            iss >> name >> x >> y;
            int trak;
            while (iss >> trak) {
                packs.push_back(trak);
            }
            cout << n << ". Название: " << name << ", Координаты: (" << x << ", " << y << "), Трек-номера: ";
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
void PACK::addpost(){
     post editable;
     cout << "Введите название отделения: ";
     cin >> editable.name;
     cout << "Введите координату Х: ";
     cin >> editable.x;
     cout << "Введите координату Y: ";
     cin >> editable.y;
     ofstream file("post.txt", ios::app);
     file << editable;
}
void PACK::time(){
    PACK::post editable;
    int a = count_strings("pack.txt");
    PACK::pack arr[a];
    ifstream fpack;
    ifstream fpost;
    fpack.open("pack.txt");
    fpost.open("post.txt");
    for(int i = 0; i < a; i++){
        fpack >> arr[i];
        if(arr[i].remainingTime != 0){
            arr[i].remainingTime -= 1;
            while(fpost >> editable){
                if(editable.name == arr[i].to){
                    int x = editable.x-arr[i].currentX;
                    int y = editable.y-arr[i].currentY;
                    int c=sqrt(pow(x,2)+pow(y,2));
                    int speed=60;
                    arr[i].currentX=x*speed/c;
                    arr[i].currentY=y*speed/c;
                    break;
                }
            }
        }else{
            cout << "Посылка " << arr[i].id << " прибыла" << endl;
                }
        }
    fpack.close();
    fpost.close();
    ofstream f;
    f.open("pack.txt");
    for(int i = 0; i < a; i++){
        f << arr[i];
    }
    f.close();
}
void PACK::delpost(){
    display();
    int num;
    cout << "Введите номер отделения для удаления:";
    cin >> num;
    ifstream fpost("post.txt");
    ifstream fpack("pack.txt");
    vector <post> posts;
    vector <pack> packs;
    post p;
    pack pa;
    while(fpost >> p){
        posts.push_back(p);
    }
    fpost.close();
    while(fpack >> pa){
        packs.push_back(pa);
    }
    fpack.close();
    for(size_t i = 0; i < packs.size(); i++){
        for(size_t j = 0; j < posts[num-1].packs.size(); j++){
            if(packs[i].id == posts[num-1].packs[j]){
                packs[i].to = packs[i].from;
                packs[i].from = "----";
                packs[i].remainingTime = (sqrt(pow(posts[num-1].x - packs[i].currentX,2) + pow(posts[num-1].y - packs[i].currentY,2)))/60;
            }
        }
    }
    posts.erase(posts.begin() + (num - 1));
    ofstream fpost1("post.txt");
    ofstream fpack1("pack.txt");
    for(size_t i = 0; i < posts.size(); i++){
        fpost1 << posts[i];
    }
    fpost1.close();
    for(size_t i = 0; i < packs.size(); i++){
        fpack1 << packs[i];
    }
    fpack1.close();
}
void PACK::give(){
    cout << "Введите 4-х значный трек номер для выдачи:";
    int num;
    cin >> num;
    ifstream fpack("pack.txt");
    ifstream fpost("post.txt");
    vector <post> posts;
    vector<pack> packs;
    post p;
    pack pa;
    while(fpost >> p){
        posts.push_back(p);
    }
    fpost.close();
    while(fpack >> pa){
        packs.push_back(pa);
    }
    fpack.close();
    int idnum;

Егор Попельницкий, [5/21/2025 3:23 PM]
for(size_t i = 0; i < packs.size(); i++){
        if(packs[i].id == num){
            cout << "Введите имя получателя посылки" << num << ":";
            string name;
            cin >> name;
            if(name == packs[i].getname){
                cout << "Посылка получена!" << endl;
                idnum = i;

            }
        }
    }
    packs.erase(packs.begin() + idnum);
    int ii;
    int jj;
    for(size_t i = 0; i < posts.size(); i++){
        for(size_t j = 0; j < posts[i].packs.size(); j++){
            if(posts[i].packs[j] == num){
                ii = i;
                jj = j;
            }
        }
    }
    posts[ii].packs.erase(posts[ii].packs.begin()+jj);
    ofstream fpost1("post.txt");
    ofstream fpack1("pack.txt");
    for(size_t i = 0; i < posts.size(); i++){
        fpost1 << posts[i];
    }
    fpost1.close();
    for(size_t i = 0; i < packs.size(); i++){
        fpack1 << packs[i];
    }
    fpack1.close();
}
