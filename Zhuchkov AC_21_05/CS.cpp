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
    cout << "\n\nKC\n" << "ID: " << _idCS << "\nНазвание: " << _name << "\nКоличество цехов: " << _shopCount << "\nКоличество цехов в работе: " << _workShopCount << "\nЭффективность: " << _efficiency << "\nПроцент незадействованных цехов: " << _prosentBadShop << "\n";
};