#pragma once

#include <iostream>
#include <string>
using namespace std;

bool isInt(string str) {
    bool err = false;
    for (int i = 0; i < str.length(); i++) {
        /*cout << isdigit(str[i]) << " " << str[i] << "\n";*/
        if (isdigit(str[i]) == 0) {
            err = true;
            break;
        }
    }
    if (err)
        return 0;
    return 1;
}

int toInt(string str) {
    if (isInt(str)) return atoi(str.c_str());
    return 0;
}

bool isFloat(string str) {
    bool err = false;
    int count = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '.') str[i] = ',';
        /*cout << str[i] << " " << (isdigit(str[i]) == 0) << " " << (str[i] != ',') << " " << ((isdigit(str[i]) == 0) && (str[i] != ',')) << endl;*/
        if ((isdigit(str[i]) == 0) && (str[i] != ',')) {
            err = true;
            break;
        }
        if (str[i] == ',') count += 1;
        if (count > 1) {
            err = true;
            break;
        }
    }
    if (err)
        return 0;
    return 1;
}

float toFloat(string str) {
    if (isFloat(str)) return atof(str.c_str());
    return 0;
}

bool isBool(string str) {
    if (str == "0" || str == "1") return 1;
    return 0;
}

bool toBool(string str) {
    if (isBool(str)) return atoi(str.c_str());
    return 0;
}


