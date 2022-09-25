#include <iostream>
#include <fstream>

using namespace std;

struct pipe {
    int _length;
    int _diameter;
    bool _inWork;
};

struct CS {
    string _name;
    int _shopCount;
    int _workShopCount;
    double _efficiency = double(_workShopCount) / double(_shopCount);
};

int isNum(string str) {
    bool err = false;
    for (int i = 0; i < str.length(); i++) {
        /*cout << isdigit(str[i]) << " " << str[i] << "\n";*/
        if (isdigit(str[i]) != 4 || str[i] == ' ') {
            err = true;
            break;
        }
    }
    if (err)
        return 0;
    return atoi(str.c_str());
}

pipe yourPipe{};
CS yourCS{};

int stateMenu;
void menu() {
    string stateMenu_str;
    cout << "1. �������� ����� \n2. �������� �� \n3. �������� ���� �������� \n4. ������������� ����� \n5. ������������� �� \n6. ��������� \n7. ��������� \n0. �����\n\n";
    cin >> stateMenu_str;
    stateMenu = isNum(stateMenu_str);
}

void add_pipe() {

    string length_str;
    string diameter_str;
    string inWork_str;

    int length = 0;
    int diameter = 0;
    bool inWork = false;

    do {
        cout << "������� ����� �����: "; cin >> length_str;
        length = isNum(length_str);
    } while (length <= 0);
    do {
        cout << "������� ������� �����: "; cin >> diameter_str;
        diameter = isNum(diameter_str);
    } while (diameter <= 0);
    cout << "� ������(1/0): "; cin >> inWork_str;
    inWork = bool(isNum(inWork_str));

    yourPipe = { length, diameter, inWork };
};

void out_pipe() {
    cout << "\n\n�����\n�����: " << yourPipe._length << "\n�������: " << yourPipe._diameter << "\n� ������: " << yourPipe._inWork << "\n";
}

void red_pipe() {
    if (yourPipe._length != 0 || yourPipe._diameter != 0) {

        string inWork_str;

        cout << "\n�������� '� ������': " << yourPipe._inWork << "\n������� ����� ��������: ";
        cin >> inWork_str;

        yourPipe._inWork = bool(isNum(inWork_str));

        cout << yourPipe._inWork;

        system("pause");
        system("cls");

        cout << "\n������ ������� ��������!\n";
    }
    else
    {
        cout << "\n�������� �����\n\n";
    }
}

void add_CS() {
    string nameCS_str;
    string shopCount_str;
    string workShopCount_str;

    int shopCount;
    int workShopCount;

    cout << "������� �������� ��: "; cin >> nameCS_str;
    do {
        cout << "������� ���������� �����: "; cin >> shopCount_str;
        shopCount = isNum(shopCount_str);
    } while (shopCount <= 0);
    do {
        cout << "������� ���������� ����� � ������ (Max: " << shopCount << "): "; cin >> workShopCount_str;
        workShopCount = isNum(workShopCount_str);
    } while (shopCount < workShopCount || workShopCount < 0);

    yourCS = { nameCS_str, shopCount, workShopCount };

    cout << "�������������: " << yourCS._efficiency;
};

void out_CS() {
    cout << "\n\nKC\n��������: " << yourCS._name << "\n���������� �����: " << yourCS._shopCount << "\n���������� ����� � ������: " << yourCS._workShopCount << "\n�������������: " << yourCS._efficiency << "\n";
}

void red_CS() {
    if (yourCS._shopCount != 0 || yourCS._workShopCount != 0) {

        int workShopCount;

        cout << "\n�������� '���������� ����� � ������': " << yourCS._workShopCount;

        do {
            cout << "\n������� ����� ��������(Max: " << yourCS._shopCount << "): ";  cin >> workShopCount;
        } while (yourCS._shopCount < workShopCount || workShopCount < 0);


        yourCS._workShopCount = workShopCount;
        system("cls");
        cout << "\n������ ������� ��������!\n";
    }
    else
    {
        cout << "\n�������� KC\n\n";
    }
}

void out_all_to_file() {
    ofstream fout("out.txt");
    if (!(yourPipe._length == 0 && yourPipe._diameter == 0 && yourPipe._inWork == 0)) {
        fout << "�����\n�����: " << yourPipe._length << "\n�������: " << yourPipe._diameter << "\n� ������: " << yourPipe._inWork << "\n\n\n";
    }
    else
    {
        fout << "����� �� �������!\n";
    }
    if (!(yourCS._shopCount == 0 && yourCS._workShopCount == 0)) {
        fout << "KC\n��������: " << yourCS._name << "\n���������� �����: " << yourCS._shopCount << "\n���������� ����� � ������: " << yourCS._workShopCount << "\n�������������: " << yourCS._efficiency << "\n";
    }
    else
    {
        fout << "KC �� �������!\n";
    }
    fout.close();
}

void in_all_at_file() {
    ifstream fin("in.txt");

    string length_str;
    string diameter_str;
    string inWork_str;

    string nameCS_str;
    string shopCount_str;
    string workShopCount_str;

    fin >> length_str >> diameter_str >> inWork_str >> nameCS_str >> shopCount_str >> workShopCount_str;

    yourPipe._length = isNum(length_str);
    yourPipe._diameter = isNum(diameter_str);
    yourPipe._inWork = isNum(inWork_str);

    if (isNum(length_str) <= 0 || isNum(diameter_str) <= 0) {
        yourPipe = { 0, 0, 0 };
    }

    yourCS._name = nameCS_str;
    yourCS._shopCount = isNum(shopCount_str);
    yourCS._workShopCount = isNum(workShopCount_str);
    yourCS._efficiency = double(yourCS._workShopCount) / double(yourCS._shopCount);

    if (isNum(shopCount_str) <= 0 || isNum(workShopCount_str) <= 0 || isNum(workShopCount_str) > isNum(shopCount_str)) {
        yourCS = { "", 0, 0, 0};
    }
    
    out_pipe();
    out_CS();
}

int main()
{
    setlocale(LC_ALL, "");
    menu();
    while (stateMenu != 0)
    {
        switch (stateMenu) {
        case 1:
            add_pipe();
            out_pipe();
            system("pause");
            system("cls");
            menu();
            break;
        case 2:
            add_CS();
            out_CS();
            system("pause");
            system("cls");
            menu();
            break;
        case 3:
            if (!(yourPipe._length == 0 && yourPipe._diameter == 0 && yourPipe._inWork == 0)) {
                out_pipe();
            }
            if (!(yourCS._shopCount == 0 && yourCS._workShopCount == 0)) {
                out_CS();
            }
            system("pause");
            system("cls");
            menu();
            break;

        case 4:
            red_pipe();
            system("pause");
            system("cls");
            menu();
            break;

        case 5:
            red_CS();
            system("pause");
            system("cls");
            menu();
            break;
        case 6:
            out_all_to_file();
            system("pause");
            system("cls");
            menu();
            break;
        case 7:
            in_all_at_file();
            system("pause");
            system("cls");
            menu();
            break;
        default:
            system("cls");
            menu();
        }
    }
}
