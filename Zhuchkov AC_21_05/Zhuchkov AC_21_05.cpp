#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "func.h"
#include "pipe.h"
#include "func_pipe.h"
#include "cs.h"
#include "func_cs.h"

using namespace std;

void menu() {
    system("pause");
    system("cls");
    cout << "1. Добавить трубу \n2. Добавить КС \n3. Просмотр всех объектов \n4. Редактировать трубу \n5. Редактировать КС \n6. Сохранить \n7. Загрузить \n8. Поиск объектов по заданному фильтру(Труба) \n9. Поиск объектов по заданному фильтру(КС) \n10. Удалить Трубу\n11. Удалить КС\n0. Выход\n\n";
}

void add_stateMenu(int& stateMenu) {
    string stateMenu_str;

    cin >> stateMenu_str;

    cin.clear();
    cin.ignore(INT_MAX, '\n');

    isInt(stateMenu_str) ? stateMenu = toInt(stateMenu_str) : stateMenu = -1;
}


void out_all_to_file(unordered_map<int, Pipe> yourPipes,int size_p, unordered_map<int, CS> yourCSs, int size_c) {
    if (count_not_null_pipe(yourPipes, size_p) == 0 && count_not_null_CS(yourCSs,size_c) == 0) cout << "\nДобавьте Трубу или КС\n\n";
    else {
        string fileName_str;

        cout << "Введите название файла: "; cin >> fileName_str;

        ofstream fout(fileName_str + ".txt");

        fout << size_p << "\n" << size_c << "\n";

        for (int i = 0; i < size_p; i++) {
            fout << yourPipes[i].get_idPipe() << "\n" << yourPipes[i].get_length() << "\n" << yourPipes[i].get_diameter() << "\n" << yourPipes[i]._inWork << "\n";
        }
        for (int i = 0; i < size_c; i++) {
            fout << yourCSs[i].get_idCS() << "\n" << yourCSs[i].get_name() << "\n" << yourCSs[i].get_shopCount() << "\n" << yourCSs[i]._workShopCount << "\n" << yourCSs[i].get_efficiency() << "\n";
        }

        fout.close();
    }
}

void in_all_at_file(unordered_map<int, Pipe>& yourPipes,int& size_p, unordered_map<int, CS>& yourCSs, int& size_c) {

    string fileName_str;
    cout << "Введите название файла: "; cin >> fileName_str;

    ifstream fin(fileName_str + ".txt");

    if (fin.is_open()) {

        string str;
        string count_pipe;
        string count_CS;

        int id;

        float length;
        float diameter;
        bool inWork;

        string name;
        int shopCount;
        int workShopCount;
        double efficiency;
        double prosentBadShop;

        getline(fin, count_pipe, '\n');
        getline(fin, count_CS, '\n');

        yourPipes.clear();
        yourCSs.clear();

        for (int i = 0; i < toInt(count_pipe); i++) {

            getline(fin, str, '\n');
            id = toInt(str);

            getline(fin, str, '\n');
            length = toFloat(str);

            getline(fin, str, '\n');
            diameter = toFloat(str);

            getline(fin, str, '\n');
            inWork = bool(str.c_str());

            yourPipes[id].add_pipe_inner( id, length , diameter , inWork );
            size_p = id++;
        }
        out_pipe(yourPipes, size_p);

        for (int i = 0; i < toInt(count_CS); i++) {

            getline(fin, str, '\n');
            id = toInt(str);

            getline(fin, name, '\n');

            getline(fin, str, '\n');
            shopCount = toInt(str);

            getline(fin, str, '\n');
            workShopCount = toInt(str);

            getline(fin, str, '\n');
            efficiency = toFloat(str);

            prosentBadShop = (1 - (double(workShopCount) / double(shopCount))) * 100;

            yourCSs[id].add_CS_inner(id, name , shopCount , workShopCount , efficiency);
            size_c = id++;
        }
        out_CS(yourCSs,size_c);

        fin.close();
    }
    else cout << "Не удалось найти файл\n";
}

int main(){
    int size_p = 0;
    int size_c = 0;
    unordered_map<int, Pipe> yourPipes;
    unordered_map<int, CS> yourCSs;
    int stateMenu = -1;

    setlocale(LC_ALL, "");
    menu();

    while (stateMenu)
    {
        add_stateMenu(stateMenu);
        switch (stateMenu) {
            case 1:
                add_pipe(yourPipes, size_p);
                menu();
                break;
            case 2:
                add_CS(yourCSs, size_c);
                menu();
                break;
            case 3:
                out_pipe(yourPipes, size_p);
                out_CS(yourCSs, size_c);
                menu();
                break;
            case 4:
                edit_pipe(yourPipes, size_p);
                menu();
                break;
            case 5:
                edit_CS(yourCSs, size_c);
                menu();
                break;
            case 6:
                out_all_to_file(yourPipes, size_p, yourCSs, size_c);
                menu();
                break;
            case 7:
                in_all_at_file(yourPipes, size_p, yourCSs, size_c);
                menu();
                break;
            case 8:
                find_pipe(yourPipes, size_p);
                menu();
                break;
            case 9:
                find_CS(yourCSs, size_c);
                menu();
                break;
            case 10:
                del_pipe(yourPipes, size_p);
                menu();
                break;
            case 11:
                del_CS(yourCSs, size_c);
                menu();
                break;
            default:
                menu();
                break;
        }}}