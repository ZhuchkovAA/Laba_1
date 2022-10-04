#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct pipe {
    float _length;
    float _diameter;
    bool _inWork;
};

struct CS {
    string _name;
    int _shopCount;
    int _workShopCount;
    double _efficiency = double(_workShopCount) / double(_shopCount);
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

void add_pipe(pipe& yourPipe) {

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
    yourPipe = { length, diameter, inWork };
};

void out_pipe(pipe yourPipe) {
    cout << "\n\n�����\n�����: " << yourPipe._length << "\n�������: " << yourPipe._diameter << "\n� ������: " << yourPipe._inWork << "\n";
}

void edit_pipe(pipe& yourPipe) {
    if (yourPipe._length != 0 || yourPipe._diameter != 0) {

        string inWork_str;

        cout << "\n�������� '� ������': " << yourPipe._inWork;
        do {
            cout << "\n������� ����� ��������: ";
            cin >> inWork_str;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            if (isBool(inWork_str) == 1) yourPipe._inWork = bool(toInt(inWork_str));
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

void add_CS(CS& yourCS) {
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

    yourCS = { nameCS_str, shopCount, workShopCount };

    cout << "�������������: " << yourCS._efficiency;
};

void out_CS(CS yourCS) {
    cout << "\n\nKC\n��������: " << yourCS._name << "\n���������� �����: " << yourCS._shopCount << "\n���������� ����� � ������: " << yourCS._workShopCount << "\n�������������: " << yourCS._efficiency << "\n";
}

void edit_CS(CS& yourCS) {
    if (yourCS._shopCount != 0 || yourCS._workShopCount != 0) {

        int workShopCount;

        cout << "\n�������� '���������� ����� � ������': " << yourCS._workShopCount;

        do {
            cout << "\n������� ����� ��������(Max: " << yourCS._shopCount << "): ";  cin >> workShopCount;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        } while (yourCS._shopCount < workShopCount || workShopCount < 0);

        yourCS._workShopCount = workShopCount;
        system("cls");
        cout << "\n������ ������� ��������!\n";
        yourCS._efficiency = double(yourCS._workShopCount) / double(yourCS._shopCount);
    }
    else
    {
        cout << "\n�������� KC\n\n";
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

void in_all_at_file(pipe& yourPipe, CS& yourCS) {
    ifstream fin("data.txt");

    if (fin.is_open()) {

        string str;

        getline(fin, str, '\n');
        if (str == "�����") {

            getline(fin, str, '\n');
            yourPipe._length = toFloat(str);

            getline(fin, str, '\n');
            yourPipe._diameter = toFloat(str);

            getline(fin, str, '\n');

            if (isBool(str) == 0) {
                yourPipe = { 0, 0, 0 };
                cout << "������ �����\n";
            }
            else {
                yourPipe._inWork = toInt(str);
            }

            if (yourPipe._length <= 0 || yourPipe._diameter <= 0) {
                yourPipe = { 0, 0, 0 };
                cout << "������ �����\n";
            }
            else out_pipe(yourPipe);

        }
        else cout << "����� �� �������!\n";

        getline(fin, str, '\n');
        getline(fin, str, '\n');
        if (str == "KC") {

            getline(fin, str, '\n');
            yourCS._name = str;

            getline(fin, str, '\n');
            yourCS._shopCount = toInt(str);

            getline(fin, str, '\n');
            yourCS._workShopCount = toInt(str);

            yourCS._efficiency = double(yourCS._workShopCount) / double(yourCS._shopCount);

            if (yourCS._shopCount <= 0 || yourCS._workShopCount <= 0 || yourCS._workShopCount > yourCS._shopCount) {
                yourCS = { "", 0, 0, 0 };
                cout << "������ ��\n";
            }
            else out_CS(yourCS);
        }
        else cout << "\nKC �� �������!\n";
        fin.close();
    }
    else cout << "���� �� ������� �������\n�������� data.txt\n";
}

int main()
{
    pipe yourPipe{};
    CS yourCS{};

    int stateMenu = -1;
    setlocale(LC_ALL, "");
    menu();
    while (stateMenu)
    {
        add_stateMenu(stateMenu);
        switch (stateMenu) {
        case 1:
            add_pipe(yourPipe);
            out_pipe(yourPipe);
            menu();
            break;
        case 2:
            add_CS(yourCS);
            out_CS(yourCS);
            menu();
            break;
        case 3:
            if (!(yourPipe._length == 0 && yourPipe._diameter == 0 && yourPipe._inWork == 0)) {
                out_pipe(yourPipe);
            }
            if (!(yourCS._shopCount == 0 && yourCS._workShopCount == 0)) {
                out_CS(yourCS);
            }
            menu();
            break;
        case 4:
            edit_pipe(yourPipe);
            menu();
            break;
        case 5:
            edit_CS(yourCS);
            menu();
            break;
        case 6:
            out_all_to_file(yourPipe, yourCS);
            menu();
            break;
        case 7:
            in_all_at_file(yourPipe, yourCS);
            menu();
            break;
        default:
            menu();
            break;
        }
    }
}