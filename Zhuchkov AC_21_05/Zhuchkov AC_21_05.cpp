#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Zhuchkov AC_21_05.h"

using namespace std;

struct pipe {
    int _idPipe;
    float _length;
    float _diameter;
    bool _inWork;
};

struct CS {
    int _idCS;
    string _name;
    int _shopCount;
    int _workShopCount;
    double _efficiency = double(_workShopCount) / double(_shopCount) * 100;
};

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
    else return 0;
}

bool isFloat(string str) {
    bool err = false;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '.') str[i] = ',';
        /*cout << str[i] << " " << (isdigit(str[i]) == 0) << " " << (str[i] != ',') << " " << ((isdigit(str[i]) == 0) && (str[i] != ',')) << endl;*/
        if ((isdigit(str[i]) == 0) && (str[i] != ',')) {
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
    else return 0;
}

bool isBool(string str) {
    if (str == "0" || str == "1") return 1;
    else return 0;
}

void menu() {
    system("pause");
    system("cls");
    cout << "1. �������� ����� \n2. �������� �� \n3. �������� ���� �������� \n4. ������������� ����� \n5. ������������� �� \n6. ��������� \n7. ��������� \n0. �����\n\n";
}

void add_stateMenu(int& stateMenu) {
    string stateMenu_str;

    cin >> stateMenu_str;

    cin.clear();
    cin.ignore(INT_MAX, '\n');
    
    isInt(stateMenu_str) ? stateMenu = toInt(stateMenu_str) : stateMenu = -1;
}

int new_idPipe(vector<pipe> yourPipes) {
    if (yourPipes.size() == 0) return 0;
    else return yourPipes[yourPipes.size() - 1]._idPipe + 1;
}

bool is_there_idPipe(vector<pipe> yourPipes, int id) {
    for (int i = 0; i < yourPipes.size(); i++)
        if (yourPipes[i]._idPipe == id) return true;
    return false;
}

bool is_there_idCS(vector<CS> yourCSs, int id) {
    for (int i = 0; i < yourCSs.size(); i++)
        if (yourCSs[i]._idCS == id) return true;
    return false;
}

int new_idCS(vector<CS> yourCSs) {
    if (yourCSs.size() == 0) return 0;
    else return yourCSs[yourCSs.size() - 1]._idCS + 1;
}

void add_pipe(vector<pipe>& yourPipes) {

    string length_str;
    string diameter_str;
    string inWork_str;

    float length = 0;
    float diameter = 0;
    bool inWork = false;

    do {
        cout << "������� ����� �����: "; cin >> length_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        length = toFloat(length_str);
    } while (length <= 0);
    do {
        cout << "������� ������� �����: "; cin >> diameter_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        diameter = toFloat(diameter_str);
    } while (diameter <= 0);
    do {
        cout << "� ������(1/0): "; cin >> inWork_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        if (isBool(inWork_str) == 1) inWork = toInt(inWork_str);
    } while (isBool(inWork_str) == 0);
    
    yourPipes.push_back({new_idPipe(yourPipes), length, diameter, inWork });
};

void out_pipe(vector<pipe> yourPipes) {
    for (int i = 0; i < yourPipes.size(); i++)
    cout << "\n\n�����\n" <<"ID: " << yourPipes[i]._idPipe<< "\n�����: " << yourPipes[i]._length << "\n�������: " << yourPipes[i]._diameter << "\n� ������: " << yourPipes[i]._inWork << "\n";
}

void edit_pipe(vector<pipe>& yourPipes) {
    if (yourPipes.size() != 0) {

        string id_str;
        int id = -1;

        out_pipe(yourPipes);

        do {
            cout << "\n������� ID: "; cin >> id_str;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            if (isInt(id_str)) id = toInt(id_str); 
        } while (!(isInt(id_str)) || !(is_there_idPipe(yourPipes, toInt(id_str))));
        
        string inWork_str;

        cout << "\n�������� '� ������': " << yourPipes[id]._inWork;
        do {
            cout << "\n������� ����� ��������: ";
            cin >> inWork_str;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            if (isBool(inWork_str) == 1) yourPipes[id]._inWork = bool(toInt(inWork_str));
        } while (isBool(inWork_str) == 0);
        system("pause");
        system("cls");

        cout << "\n������ ������� ���������!\n";
    }
    else
    {
        cout << "\n�������� �����\n\n";
    }
}

void find_pipe(vector<pipe> yourPipes) {
    string state_str;
    int state;

    do {
        cout << "�����: 1 - �� ������, 2 - �� ��������� '� ������'\n������� �����: "; cin >> state_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        if (isInt(state_str)) state = toInt(state_str);
    } while (!(isInt(state_str)) || !(toInt(state_str) == 1 || toInt(state_str) == 2));

    string parametr_str;



    switch (state)
    {
    case 1:
        float parametr_first_case;
        do {
            cout << "������� �����: "; cin >> parametr_str;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            if (isFloat(parametr_str)) parametr_first_case = toFloat(parametr_str);
        } while (!(isFloat(parametr_str)));

        for (int i = 0; i < yourPipes.size(); i++) {
            if (yourPipes[i]._length > parametr_first_case) cout << "\n\n�����\n" << "ID: " << yourPipes[i]._idPipe << "\n�����: " << yourPipes[i]._length << "\n�������: " << yourPipes[i]._diameter << "\n� ������: " << yourPipes[i]._inWork << "\n";
        }
        break;
    case 2:
        bool parametr_second_case;
        do {
            cout << "������� �������� '� ������': "; cin >> parametr_str;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            if (isBool(parametr_str)) parametr_second_case = toInt(parametr_str);
        } while (!(isBool(parametr_str)));

        for (int i = 0; i < yourPipes.size(); i++) {
            if (yourPipes[i]._inWork == parametr_second_case) cout << "\n\n�����\n" << "ID: " << yourPipes[i]._idPipe << "\n�����: " << yourPipes[i]._length << "\n�������: " << yourPipes[i]._diameter << "\n� ������: " << yourPipes[i]._inWork << "\n";
        }
        break;
    default:
        break;
    }
}

void add_CS(vector<CS>& yourCSs) {
    string nameCS_str;
    string shopCount_str;
    string workShopCount_str;

    int shopCount;
    int workShopCount;

    cout << "������� �������� ��: ";
    getline(cin, nameCS_str, '\n');
    do {
        cout << "������� ���������� �����: "; cin >> shopCount_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        shopCount = toInt(shopCount_str);
    } while (shopCount <= 0);
    do {
        cout << "������� ���������� ����� � ������ (Max: " << shopCount << "): "; cin >> workShopCount_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        workShopCount = toInt(workShopCount_str);
    } while (shopCount < workShopCount || workShopCount < 0);

    yourCSs.push_back({ new_idCS(yourCSs), nameCS_str, shopCount, workShopCount});

    /*cout << "�������������: " << yourCSs._efficiency;*/
};

void out_CS(vector<CS> yourCSs) {
    for (int i = 0; i < yourCSs.size(); i++)
    cout << "\n\nKC\n"<< "ID: " << yourCSs[i]._idCS <<"\n��������: " << yourCSs[i]._name << "\n���������� �����: " << yourCSs[i]._shopCount << "\n���������� ����� � ������: " << yourCSs[i]._workShopCount << "\n�������������: " << yourCSs[i]._efficiency << "\n";
}

void edit_CS(vector<CS>& yourCSs) {
    if (yourCSs.size() != 0) {

        string id_str;
        int id = -1;

        out_CS(yourCSs);

        do {
            cout << "\n������� ID: "; cin >> id_str;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            if (isInt(id_str)) id = toInt(id_str);
        } while (!(isInt(id_str)) || !(is_there_idCS(yourCSs, toInt(id_str))));

        int workShopCount;

        cout << "\n�������� '���������� ����� � ������': " << yourCSs[id]._workShopCount;

        do {
            cout << "\n������� ����� ��������(Max: " << yourCSs[id]._shopCount << "): ";  cin >> workShopCount;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        } while (yourCSs[id]._shopCount < workShopCount || workShopCount < 0);

        yourCSs[id]._workShopCount = workShopCount;
        system("cls");
        cout << "\n������ ������� ��������!\n";
        yourCSs[id]._efficiency = double(yourCSs[id]._workShopCount) / double(yourCSs[id]._shopCount);
    }
    else
    {
        cout << "\n�������� KC\n\n";
    }
}

void find_CS(vector<CS> yourCSs) {
    string state_str;
    int state;

    do {
        cout << "�����: 1 - �� ��������, 2 - �� �������� ����������������� �����\n������� �����: "; cin >> state_str;

        cin.clear();
        cin.ignore(INT_MAX, '\n');

        if (isInt(state_str)) state = toInt(state_str);
    } while (!(isInt(state_str)) || !(toInt(state_str) == 1 || toInt(state_str) == 2));

    string parametr_str;



    switch (state)
    {
    case 1:
        cout << "������� ��������: "; 
        getline(cin, parametr_str, '\n');
        for (int i = 0; i < yourCSs.size(); i++) {
            if (yourCSs[i]._name == parametr_str) cout << "\n\nKC\n" << "ID: " << yourCSs[i]._idCS << "\n��������: " << yourCSs[i]._name << "���������� �����\n: " << yourCSs[i]._shopCount << "\n���������� ����� � ������: " << yourCSs[i]._workShopCount << "\n�������������: " << yourCSs[i]._efficiency << "\n";
        }
        break;
    case 2:
        float parametr;
        do {
            cout << "������� ������� ����������������� �����: "; cin >> parametr_str;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            if (isFloat(parametr_str)) parametr = toFloat(parametr_str);
        } while (!(isFloat(parametr_str)));

        for (int i = 0; i < yourCSs.size(); i++) {
            if ((100-yourCSs[i]._efficiency) > parametr) cout << "\n\nKC\n" << "ID: " << yourCSs[i]._idCS << "\n��������: " << yourCSs[i]._name << "\n���������� �����: " << yourCSs[i]._shopCount << "\n���������� ����� � ������: " << yourCSs[i]._workShopCount << "\n�������������: " << yourCSs[i]._efficiency << "\n";
        }
        break;
    default:
        break;
    }
}

void out_all_to_file(pipe yourPipe, CS yourCS) {
    ofstream fout("data.txt");
    if (!(yourPipe._length == 0 && yourPipe._diameter == 0 && yourPipe._inWork == 0)) {
        fout << "�����\n" << yourPipe._length << "\n" << yourPipe._diameter << "\n" << yourPipe._inWork << "\n";
    }
    else
    {
        fout << "����� �� �������!\n";
    }
    if (!(yourCS._shopCount == 0 && yourCS._workShopCount == 0)) {
        fout << "\nKC\n" << yourCS._name << "\n" << yourCS._shopCount << "\n" << yourCS._workShopCount << "\n" << yourCS._efficiency << "\n";
    }
    else
    {
        fout << "KC �� �������!\n";
    }
    fout.close();
}

//void in_all_at_file(vector<pipe> yourPipes, vector<CS> yourCSs) {
//    ifstream fin("data.txt");
//
//    if (fin.is_open()) {
//
//        string str;
//
//        getline(fin, str, '\n');
//        if (str == "�����") {
//
//            getline(fin, str, '\n');
//            yourPipe._length = toFloat(str);
//
//            getline(fin, str, '\n');
//            yourPipe._diameter = toFloat(str);
//
//            getline(fin, str, '\n');
//
//            if (isBool(str) == 0) {
//                yourPipe = { 0, 0, 0 };
//                cout << "������ �����\n";
//            }
//            else {
//                yourPipe._inWork = toInt(str);
//            }
//
//            if (yourPipe._length <= 0 || yourPipe._diameter <= 0) {
//                yourPipe = { 0, 0, 0 };
//                cout << "������ �����\n";
//            }
//            else out_pipe(yourPipe);
//
//        }
//        else cout << "����� �� �������!\n";
//
//        getline(fin, str, '\n');
//        getline(fin, str, '\n');
//        if (str == "KC") {
//
//            getline(fin, str, '\n');
//            yourCS._name = str;
//
//            getline(fin, str, '\n');
//            yourCS._shopCount = toInt(str);
//
//            getline(fin, str, '\n');
//            yourCS._workShopCount = toInt(str);
//
//            yourCS._efficiency = double(yourCS._workShopCount) / double(yourCS._shopCount);
//
//            if (yourCS._shopCount <= 0 || yourCS._workShopCount <= 0 || yourCS._workShopCount > yourCS._shopCount) {
//                yourCS = { "", 0, 0, 0 };
//                cout << "������ ��\n";
//            }
//            else out_CS(yourCS);
//        }
//        else cout << "\nKC �� �������!\n";
//        fin.close();
//    }
//    else cout << "���� �� ������� �������\n�������� data.txt\n";
//}

int main()
{
    vector<pipe> yourPipes;
    vector<CS> yourCSs;

    int stateMenu = -1;
    setlocale(LC_ALL, "");
    menu();
    while (stateMenu)
    {
        add_stateMenu(stateMenu);
        switch (stateMenu) {
        case 1:
            add_pipe(yourPipes);
            menu();
            break;
        case 2:
            add_CS(yourCSs);
            menu();
            break;
        case 3:
            out_pipe(yourPipes);
            out_CS(yourCSs);
            menu();
            break;
        case 4:
            edit_pipe(yourPipes);
            menu();
            break;
        case 5:
            edit_CS(yourCSs);
            menu();
            break;
        //case 6:
        //    out_all_to_file(yourPipes, yourCSs);
        //    menu();
        //    break;
        //case 7:
        //    in_all_at_file(yourPipes, yourCSs);
        //    menu();
        //    break;
        case 10:
            find_pipe(yourPipes);
            menu();
            break;
        case 11:
            find_CS(yourCSs);
            menu();
            break;
        default:
            menu();
            break;
        }
    }
}