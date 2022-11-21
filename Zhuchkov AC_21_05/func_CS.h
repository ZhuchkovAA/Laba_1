#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "func.h"
#include "cs.h"

bool is_there_idCS(unordered_map<int, CS> yourCSs, int id, int size_) {
    for (int i = 0; i < size_; i++)
        if (yourCSs[i].get_idCS() == id && (!(yourCSs[i].get_name().empty()))) return true;
    return false;
}

int count_not_null_CS(unordered_map<int, CS> yourCSs, int size_) {
    int count = 0;
    for (int i = 0; i < size_; i++)
        if (!(yourCSs[i].get_name().empty())) count += 1;
    return count;
}

void add_CS(unordered_map<int, CS>& yourCSs, int& size_) {

    string nameCS_str;
    string shopCount_str;
    string workShopCount_str;
    string efficiency_str;

    int shopCount;
    int workShopCount;
    double efficiency;

    do {
        cout << "Введите название КС: ";
        getline(cin, nameCS_str, '\n');
    } while (nameCS_str.empty());

    do {
        cout << "Введите количество цехов: "; cin >> shopCount_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        shopCount = toInt(shopCount_str);
    } while (shopCount == 0);
    do {
        cout << "Введите количество цехов в работе (Max: " << shopCount << "): "; cin >> workShopCount_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        workShopCount = toInt(workShopCount_str);
    } while (shopCount < workShopCount || !(isInt(workShopCount_str)));
    do {
        cout << "Введите эффективность: "; cin >> efficiency_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        efficiency = toFloat(efficiency_str);
    } while (!(isFloat(efficiency_str)));

    yourCSs[size_].add_CS_inner(size_, nameCS_str, shopCount, workShopCount, efficiency);
    size_++;
    /*cout << "Эффективность: " << yourCSs._efficiency;*/
};

void out_CS(unordered_map<int, CS> yourCSs, int size_) {
    for (int i = 0; i < size_; i++)
        if (!(yourCSs[i].get_name().empty()))
            cout << "\n\nKC\n" << "ID: " << yourCSs[i].get_idCS() << "\nНазвание: " << yourCSs[i].get_name() << "\nКоличество цехов: " << yourCSs[i].get_shopCount() << "\nКоличество цехов в работе: " << yourCSs[i]._workShopCount << "\nЭффективность: " << yourCSs[i].get_efficiency() << "\nПроцент незадействованных цехов: " << yourCSs[i].get_prosentBadShop() << "\n";
}

void edit_CS(unordered_map<int, CS>& yourCSs, int size_) {
    if (count_not_null_CS(yourCSs, size_) != 0) {

        string id_str;
        int id = -1;

        out_CS(yourCSs, size_);

        do {
            cout << "\nВведите ID: "; cin >> id_str;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            id = toInt(id_str);
        } while (!(isInt(id_str)) || !(is_there_idCS(yourCSs, toInt(id_str), size_)));

        string workShopCount_str;
        int workShopCount;

        cout << "\nПараметр 'Количество цехов в работе': " << yourCSs[id]._workShopCount;

        do {
            cout << "\nВведите новое значение(Max: " << yourCSs[id].get_shopCount() << "): ";  cin >> workShopCount_str;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            workShopCount = toInt(workShopCount_str);
        } while (yourCSs[id].get_shopCount() < workShopCount || !(isInt(workShopCount_str)));

        yourCSs[id]._workShopCount = workShopCount;

        system("cls");
        cout << "\nДанные успешно изменены!\n\n";
        yourCSs[id].prosentBadShop_add((1 - (double(yourCSs[id]._workShopCount) / double(yourCSs[id].get_shopCount()))) * 100);
    }
    else cout << "\nДобавьте KC\n\n";
}

void del_CS(unordered_map<int, CS>& yourCSs, int size_) {
    if (count_not_null_CS(yourCSs, size_) == 0) cout << "\nДобавьте КС\n\n";
    else {
        string id_str;
        int id = -1;

        out_CS(yourCSs, size_);
        do {
            cout << "Введите ID: "; cin >> id_str;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            id = toInt(id_str);
        } while (!(isInt(id_str)) || !(is_there_idCS(yourCSs, id, size_)));
        yourCSs.erase(id);

        cout << "\n\nКС успешно удалена!\n\n";
    }
}

void find_CS(unordered_map<int, CS> yourCSs, int size_) {
    if (count_not_null_CS(yourCSs, size_) != 0) {

        string state_str;
        int state;

        do {
            cout << "Поиск: 1 - по названию\n2 - по проценту незадействованных цехов\nВведите число: "; cin >> state_str;

            cin.clear();
            cin.ignore(INT_MAX, '\n');

            state = toInt(state_str);
        } while (!(isInt(state_str)) || !(toInt(state_str) == 1 || toInt(state_str) == 2));

        string parametr_str;

        switch (state)
        {
        case 1:
            cout << "Введите название: ";
            getline(cin, parametr_str, '\n');
            /*cout << parametr_str << endl;*/
            for (int i = 0; i < size_; i++) {
                cout << '"' << (yourCSs[i].get_name()) << '"' << endl;
                if (yourCSs[i].get_name() == parametr_str && !(yourCSs[i].get_name().empty())) cout << "\n\nKC\n" << "ID: " << yourCSs[i].get_idCS() << "\nНазвание: " << yourCSs[i].get_name() << "\nКоличество цехов: " << yourCSs[i].get_shopCount() << "\nКоличество цехов в работе: " << yourCSs[i]._workShopCount << "\nЭффективность: " << yourCSs[i].get_efficiency() << "\nПроцент незадействованных цехов: " << yourCSs[i].get_prosentBadShop() << "\n";
            }
            break;
        case 2:
            float parametr;
            do {
                cout << "Введите процент незадействованных цехов: "; cin >> parametr_str;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                parametr = toFloat(parametr_str);
            } while (!(isFloat(parametr_str)));

            for (int i = 0; i < size_; i++) {
                if (yourCSs[i].get_prosentBadShop() >= parametr && !(yourCSs[i].get_name().empty())) cout << "\n\nKC\n" << "ID: " << yourCSs[i].get_idCS() << "\nНазвание: " << yourCSs[i].get_name() << "\nКоличество цехов: " << yourCSs[i].get_shopCount() << "\nКоличество цехов в работе: " << yourCSs[i]._workShopCount << "\nЭффективность: " << yourCSs[i].get_efficiency() << "\nПроцент незадействованных цехов: " << yourCSs[i].get_prosentBadShop() << "\n";
            }
            break;
        }
    }
    else cout << "\nДобавьте КС\n\n";
}
