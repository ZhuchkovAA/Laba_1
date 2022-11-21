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
        cout << "������� �������� ��: ";
        getline(cin, nameCS_str, '\n');
    } while (nameCS_str.empty());

    do {
        cout << "������� ���������� �����: "; cin >> shopCount_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        shopCount = toInt(shopCount_str);
    } while (shopCount == 0);
    do {
        cout << "������� ���������� ����� � ������ (Max: " << shopCount << "): "; cin >> workShopCount_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        workShopCount = toInt(workShopCount_str);
    } while (shopCount < workShopCount || !(isInt(workShopCount_str)));
    do {
        cout << "������� �������������: "; cin >> efficiency_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        efficiency = toFloat(efficiency_str);
    } while (!(isFloat(efficiency_str)));

    yourCSs[size_].add_CS_inner(size_, nameCS_str, shopCount, workShopCount, efficiency);
    size_++;
    /*cout << "�������������: " << yourCSs._efficiency;*/
};

void out_CS(unordered_map<int, CS> yourCSs, int size_) {
    for (int i = 0; i < size_; i++)
        if (!(yourCSs[i].get_name().empty()))
            cout << "\n\nKC\n" << "ID: " << yourCSs[i].get_idCS() << "\n��������: " << yourCSs[i].get_name() << "\n���������� �����: " << yourCSs[i].get_shopCount() << "\n���������� ����� � ������: " << yourCSs[i]._workShopCount << "\n�������������: " << yourCSs[i].get_efficiency() << "\n������� ����������������� �����: " << yourCSs[i].get_prosentBadShop() << "\n";
}

void edit_CS(unordered_map<int, CS>& yourCSs, int size_) {
    if (count_not_null_CS(yourCSs, size_) != 0) {

        string id_str;
        int id = -1;

        out_CS(yourCSs, size_);

        do {
            cout << "\n������� ID: "; cin >> id_str;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            id = toInt(id_str);
        } while (!(isInt(id_str)) || !(is_there_idCS(yourCSs, toInt(id_str), size_)));

        string workShopCount_str;
        int workShopCount;

        cout << "\n�������� '���������� ����� � ������': " << yourCSs[id]._workShopCount;

        do {
            cout << "\n������� ����� ��������(Max: " << yourCSs[id].get_shopCount() << "): ";  cin >> workShopCount_str;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            workShopCount = toInt(workShopCount_str);
        } while (yourCSs[id].get_shopCount() < workShopCount || !(isInt(workShopCount_str)));

        yourCSs[id]._workShopCount = workShopCount;

        system("cls");
        cout << "\n������ ������� ��������!\n\n";
        yourCSs[id].prosentBadShop_add((1 - (double(yourCSs[id]._workShopCount) / double(yourCSs[id].get_shopCount()))) * 100);
    }
    else cout << "\n�������� KC\n\n";
}

void del_CS(unordered_map<int, CS>& yourCSs, int size_) {
    if (count_not_null_CS(yourCSs, size_) == 0) cout << "\n�������� ��\n\n";
    else {
        string id_str;
        int id = -1;

        out_CS(yourCSs, size_);
        do {
            cout << "������� ID: "; cin >> id_str;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            id = toInt(id_str);
        } while (!(isInt(id_str)) || !(is_there_idCS(yourCSs, id, size_)));
        yourCSs.erase(id);

        cout << "\n\n�� ������� �������!\n\n";
    }
}

void find_CS(unordered_map<int, CS> yourCSs, int size_) {
    if (count_not_null_CS(yourCSs, size_) != 0) {

        string state_str;
        int state;

        do {
            cout << "�����: 1 - �� ��������\n2 - �� �������� ����������������� �����\n������� �����: "; cin >> state_str;

            cin.clear();
            cin.ignore(INT_MAX, '\n');

            state = toInt(state_str);
        } while (!(isInt(state_str)) || !(toInt(state_str) == 1 || toInt(state_str) == 2));

        string parametr_str;

        switch (state)
        {
        case 1:
            cout << "������� ��������: ";
            getline(cin, parametr_str, '\n');
            /*cout << parametr_str << endl;*/
            for (int i = 0; i < size_; i++) {
                cout << '"' << (yourCSs[i].get_name()) << '"' << endl;
                if (yourCSs[i].get_name() == parametr_str && !(yourCSs[i].get_name().empty())) cout << "\n\nKC\n" << "ID: " << yourCSs[i].get_idCS() << "\n��������: " << yourCSs[i].get_name() << "\n���������� �����: " << yourCSs[i].get_shopCount() << "\n���������� ����� � ������: " << yourCSs[i]._workShopCount << "\n�������������: " << yourCSs[i].get_efficiency() << "\n������� ����������������� �����: " << yourCSs[i].get_prosentBadShop() << "\n";
            }
            break;
        case 2:
            float parametr;
            do {
                cout << "������� ������� ����������������� �����: "; cin >> parametr_str;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                parametr = toFloat(parametr_str);
            } while (!(isFloat(parametr_str)));

            for (int i = 0; i < size_; i++) {
                if (yourCSs[i].get_prosentBadShop() >= parametr && !(yourCSs[i].get_name().empty())) cout << "\n\nKC\n" << "ID: " << yourCSs[i].get_idCS() << "\n��������: " << yourCSs[i].get_name() << "\n���������� �����: " << yourCSs[i].get_shopCount() << "\n���������� ����� � ������: " << yourCSs[i]._workShopCount << "\n�������������: " << yourCSs[i].get_efficiency() << "\n������� ����������������� �����: " << yourCSs[i].get_prosentBadShop() << "\n";
            }
            break;
        }
    }
    else cout << "\n�������� ��\n\n";
}
