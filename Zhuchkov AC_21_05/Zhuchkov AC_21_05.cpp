#include <iostream>
#include <fstream>

using namespace std;

struct pipe {
    int _length;
    int _diameter;
    bool _inWork;
};

struct CS {
    char _name;
    int _shopCount;
    int _workShopCount;
    double _efficiency = double(_workShopCount) / double(_shopCount);
};

int isBool(bool num) {
    if (num == 1 || num == 0) {
        return 0;
    }
    else {
        return -1;
    }
}

pipe yourPipe{};
CS yourCS{};

int stateMenu;
void menu() {
    setlocale(LC_ALL, "");
    cout << "1. �������� ����� \n2. �������� �� \n3. �������� ���� �������� \n4. ������������� ����� \n5. ������������� �� \n6. ��������� \n7. ��������� \n0. �����\n\n";
    cin >> stateMenu;
}

void add_pipe() { 

    int length = 0;
    int diameter = 0;
    bool inWork = false;

    do {
        cout << "������� ����� �����: "; cin >> length;
    } while (length <= 0);
    do {
        cout << "������� ������� �����: "; cin >> diameter;
    } while (diameter <= 0);
    cout << "� ������(1/0): "; cin >> inWork;
    
    if (yourPipe._inWork == 204) {
        length = 0;
        diameter = 0;
        inWork = false;
        system("cls");
        menu();
    }

    yourPipe = { length, diameter, inWork };
};

void out_pipe() {
    cout << "\n\n�����\n�����: "<< yourPipe._length <<"\n�������: "<< yourPipe._diameter << "\n� ������: " << yourPipe._inWork << "\n";
}

void red_pipe() {
    if (yourPipe._length != 0 || yourPipe._diameter != 0) {
        bool inWork;
        cout << "\n�������� '� ������': " << yourPipe._inWork << "\n������� ����� ��������: ";
        cin >> inWork;
        
        cout << isBool(inWork) << endl << inWork << endl;
        inWork == false ? yourPipe._inWork = 0 : yourPipe._inWork = 1;

        system("cls");
        cout << "\n������ ������� ��������!\n";
        //if (isBool(inWork) == 0) {
        //    yourPipe._inWork = inWork ;
        //    system("cls");
        //    cout << "\n������ ������� ��������!\n";
        //}
        //else {
        //    system("cls");
        //    cout << "\n������ �����������!\n";
        //}
    }
    else
    {
        cout << "\n�������� �����\n\n";
    }
}

void add_CS() {

    char nameCS[100];
    int shopCount;
    int workShopCount;

    cout << "������� �������� ��: "; cin >> nameCS;
    do {
        cout << "������� ���������� �����: "; cin >> shopCount;
    } while (shopCount <= 0);
    do {
        cout << "������� ���������� ����� � ������ (Max: " << shopCount << "): "; cin >> workShopCount;
    } while (shopCount < workShopCount || workShopCount < 0);
    
    cout << nameCS;

    yourCS = { nameCS[0], shopCount, workShopCount };
    
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
    char temp[100];
    ifstream some_file("in.txt");

    some_file >> temp;
    cout << temp << endl;

    if (temp == 1) {
        some_file.getline(temp, 100);
        yourPipe._length = temp[1];
        yourPipe._diameter = temp[2];
        yourPipe._inWork = temp[3];
    }

    some_file.close();

    cin.get();
}
int main()
{
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
        }
    }
}
