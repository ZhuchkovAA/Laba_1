#include "CS.h"
#include <iostream>
using namespace std;

void CS::add_CS_inner(int __idCS, string __name, int __shopCount, int __workShopCount, double __efficiency) {
    _idCS = __idCS;
    _name = __name;
    _shopCount = __shopCount;
    _workShopCount = __workShopCount;
    _efficiency = __efficiency;
    _prosentBadShop = (1 - (double(_workShopCount) / double(_shopCount))) * 100;
}

void CS::out_CS_inner() {
    cout << "\n\nKC\n" << "ID: " << _idCS << "\n��������: " << _name << "\n���������� �����: " << _shopCount << "\n���������� ����� � ������: " << _workShopCount << "\n�������������: " << _efficiency << "\n������� ����������������� �����: " << _prosentBadShop << "\n";
};