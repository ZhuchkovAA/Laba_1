#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

#include "Union.h"

#include "func.h"

#include "func_pipe.h"
#include "func_cs.h"

int take_free_count_pipes_at_CS(unordered_map<int, CS>& yourCSs, int id_CS, unordered_map<int, Union>& yourUnions) {
    int lock_count = 0;
    for (auto Union : yourUnions) {
        if (Union.second.CS_1.get_idCS() == id_CS || Union.second.CS_2.get_idCS() == id_CS) lock_count++;
    }
    
    return yourCSs[id_CS].get_shopCount() - yourCSs[id_CS]._workShopCount - lock_count;
}

bool checking(unordered_map<int, Pipe>& yourPipes, int& size_p, unordered_map<int, CS>& yourCSs, int size_c, unordered_map<int, Union>& yourUnions, int& size_u) {
    int count = 0;

    if (count_not_null_pipe(yourPipes, size_p) > 0) {
        for (auto CS : yourCSs) {
            if (CS.second.get_shopCount() - CS.second._workShopCount != 0) count++;
        }
    }
    if (size_u == 0 && count >= 2) { return true; }
    if (size_u > 0 && count >= 1) { return true; }
    return false;
}

bool is_there_idCS_u(unordered_map<int, Union>& yourUnions, int id) {
    for (auto Union : yourUnions) {
        if (Union.second.CS_1.get_idCS() == id || Union.second.CS_2.get_idCS() == id) return true;
    }
    return false;
}

void out_Union(unordered_map<int, Union>& yourUnions) {
    for (auto u : yourUnions) {
        u.second.out_Union_inner();
        cout << "------------------------------------------";
    }
}

void add_Union(unordered_map<int, Pipe>& yourPipes, int& size_p, unordered_map<int, CS>& yourCSs, int size_c, unordered_map<int, Union>& yourUnions, int& size_u) {
    if (checking(yourPipes, size_p, yourCSs, size_c, yourUnions, size_u)){
        
        out_CS(yourCSs, size_c);

        string ref_1;
        string ref_2;
        string ref_3;
        
        do {
            cout << "Введите id КС_1: "; cin >> ref_1;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        } while (!isInt(ref_1) || take_free_count_pipes_at_CS(yourCSs, toInt(ref_1), yourUnions) == 0 || !(is_there_idCS(yourCSs, toInt(ref_1), size_c) || is_there_idCS_u(yourUnions, toInt(ref_1))));
        do {
            cout << "Введите id КС_2: "; cin >> ref_2;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        } while (!isInt(ref_2) || ref_2 == ref_1 || take_free_count_pipes_at_CS(yourCSs, toInt(ref_2), yourUnions) == 0 || !(is_there_idCS(yourCSs, toInt(ref_2), size_c) || is_there_idCS_u(yourUnions, toInt(ref_2))));
        
        out_pipe(yourPipes, size_p);

        do {
            cout << "Введите длину трубы: "; cin >> ref_3;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        } while (!isInt(ref_3) || toInt(ref_3) == 0);
        
        bool flag = false;
        int ref_id;
        
        for (int i = 0; i < yourPipes.size(); i++) {
            if (yourPipes[i].get_length() == (toInt(ref_3)) && yourPipes[i].get_length() != 0) { flag = true; ref_id = yourPipes[i].get_idPipe(); break; }
        }

        if (flag) {

            yourCSs[toInt(ref_1)]._workShopCount++ ;
            yourCSs[toInt(ref_2)]._workShopCount++;

            yourCSs[toInt(ref_1)].prosentBadShop_add(yourCSs[toInt(ref_1)]._workShopCount / yourCSs[toInt(ref_1)].get_shopCount());
            yourCSs[toInt(ref_2)].prosentBadShop_add(yourCSs[toInt(ref_2)]._workShopCount / yourCSs[toInt(ref_2)].get_shopCount());

            yourUnions[size_u].out_Union_inner();

            yourPipes.erase(ref_id);

            yourUnions[size_u].add_Union_inner(size_u, yourCSs[toInt(ref_1)], yourCSs[toInt(ref_2)], yourPipes[ref_id]);
            size_u++;
            return;
        }

        string ref_4;

        do {
            cout << "Хотите создать трубу с длиной: " << ref_3 << "?\n0 - Нет\n1 - Да\n"; cin >> ref_4;
        } while (!(ref_4 == "1" || ref_4 == "0"));
        
        if (ref_4 == "0") { cout << "\n\nВыход\n\n"; return; }

        float diameter = 0;
        bool inWork = false;

        do {
            cout << "Введите диаметр трубы: ";
            cin >> ref_4;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            diameter = toFloat(ref_4);
        } while (diameter == 0);
        do {
            cout << "В работе(1/0): ";
            cin >> ref_4;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            inWork = toBool(ref_4);
        } while (!(isBool(ref_4)));

        yourPipes[size_p].add_pipe_inner(size_p, toInt(ref_3), diameter, inWork);
        size_p++;
        
        yourCSs[toInt(ref_1)]._workShopCount++;
        yourCSs[toInt(ref_2)]._workShopCount++;

        yourCSs[toInt(ref_1)].prosentBadShop_add(yourCSs[toInt(ref_1)]._workShopCount / yourCSs[toInt(ref_1)].get_shopCount());
        yourCSs[toInt(ref_2)].prosentBadShop_add(yourCSs[toInt(ref_2)]._workShopCount / yourCSs[toInt(ref_2)].get_shopCount());

        yourUnions[size_u].add_Union_inner(size_u, yourCSs[toInt(ref_1)], yourCSs[toInt(ref_2)], yourPipes[size_p - 1]);

        yourUnions[size_u].out_Union_inner();

        yourPipes.erase(size_p - 1);

        size_u++;
    }
    else
    {
        cout << "\n\nКоличество доступных труб и КС меньше требуемого значения\n\n";
    }
}