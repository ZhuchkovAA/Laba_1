#include <iostream>
#include <list>

using namespace std;

struct pipe {
    int _length;
    int _diameter;
    bool _inWork;
};

pipe yourPipe{};
void add_pipe() { 

    int length;
    int diameter;
    bool inWork;
    cout << "������� ����� �����: "; cin >> length;
    cout << "������� ������� �����: "; cin >> diameter;
    cout << "� ������: "; cin >> inWork;

    yourPipe = {length, diameter, inWork};
};

void out_pipe() {
    cout << "\n\n�����\n�����: "<< yourPipe._length <<"\n�������: "<< yourPipe._diameter << "\n� ������: " << yourPipe._inWork << "\n";
}

int stateMenu;
void menu() {
    setlocale(LC_ALL, "");
    cout << "1. �������� ����� \n2. �������� �� \n3. �������� ���� �������� \n4. ������������� ����� \n5. ������������� �� \n6. ��������� \n7. ��������� \n0. �����\n\n";
    cin >> stateMenu;
}


void red_pipe() {
    int state;
    int length;
    int diameter;
    bool inWork;
    cout << "�����\n�������������:\n(1) �����\n(2) �������\n(3) � ������\n";
    cin >> state;
    if (state == 1) {
        cout << "\n����� �� ���������: " << yourPipe._length << "\n������� ����� �����: ";
        cin >> length;
        yourPipe._length = length;
        system("cls");
        cout << "\n������ ������� ��������!\n";
        system("pause");
        system("cls");
        menu();
    }
    else if (state == 2) {
        cout << "\n������� �� ���������: " << yourPipe._diameter << "\n������� ����� �������: ";
        cin >> diameter;
        yourPipe._diameter = diameter;
        system("cls");
        cout << "\n������ ������� ��������!\n";
        system("pause");
        system("cls");
        menu();
    }
    else if (state == 3) {
        cout << "\n������� �� ���������: " << yourPipe._inWork << "\n������� ����� �������: ";
        cin >> inWork;
        yourPipe._inWork = inWork;
        system("cls");
        cout << "\n������ ������� ��������!\n";
        system("pause");
        system("cls");
        menu();
    }
    else{
        cout << "������������ ������..";
        system("pause");
        system("cls");
        menu();
    }
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

        case 3:
            out_pipe();
            system("pause");
            system("cls");
            menu();
            break;

        case 4:
            red_pipe();
            break;
        }
    }
}
