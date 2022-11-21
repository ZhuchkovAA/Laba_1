#pragma once
#include <string>

using namespace std;

class CS {
private:
    int _idCS;
    string _name;
    int _shopCount;
    double _efficiency;
    double _prosentBadShop = (1 - (double(_workShopCount) / double(_shopCount))) * 100;
public:
    int _workShopCount;

    int get_idCS() { return _idCS; };
    string get_name() { return _name; };
    int get_shopCount() { return _shopCount; };
    double get_efficiency() { return _efficiency; };
    double get_prosentBadShop() { return _prosentBadShop; };

    void prosentBadShop_add(double prosent) { _prosentBadShop = prosent; };

    void add_CS_inner(int __idCS, string __name, int __shopCount, int __workShopCount, double __efficiency);

    void out_CS_inner();
};
