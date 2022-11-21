#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "func.h"
#include "pipe.h"
using namespace std;

bool is_there_idPipe(unordered_map<int, Pipe> yourPipes, int id, int size_) {
    for (int i = 0; i < size_; i++)
        if (yourPipes[i].get_idPipe() == id && yourPipes[i].get_length() != 0) return true;
    return false;
}

int count_not_null_pipe(unordered_map<int, Pipe> yourPipes, int size_) {
    int count = 0;
    for (int i = 0; i < size_; i++)
        if (yourPipes[i].get_length() != 0) count += 1;
    return count;
}

void add_pipe(unordered_map<int, Pipe>& yourPipes, int& size_) {
    string length_str;
    string diameter_str;
    string inWork_str;

    float length = 0;
    float diameter = 0;
    bool inWork = false;

    do {
        cout << "������� ����� �����: ";
        cin >> length_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        length = toFloat(length_str);
    } while (length == 0);
    do {
        cout << "������� ������� �����: ";
        cin >> diameter_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        diameter = toFloat(diameter_str);
    } while (diameter == 0);
    do {
        cout << "� ������(1/0): ";
        cin >> inWork_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        inWork = toBool(inWork_str);
    } while (!(isBool(inWork_str)));

    yourPipes[size_].add_pipe_inner(size_, length, diameter, inWork);
    size_++;
}

void out_pipe(unordered_map<int, Pipe> yourPipes, int size_) {
    for (int i = 0; i < size_; i++) {
        if (yourPipes[i].get_length() != 0) yourPipes[i].out_pipe_inner();
    }
}

void edit_pipe(unordered_map<int, Pipe>& yourPipes, int size_) {

    if (count_not_null_pipe(yourPipes, size_) != 0) {

        string state_str;
        int state = -1;

        cout << "1 - �������������� ���� ���� \n2 - �������������� �� ������ ������������ \n";

        do {
            cout << "������� �����: "; cin >> state_str;
            state = toInt(state_str);
        } while (!(isInt(state_str)) || !(state == 1 || state == 2));

        string inWork_str;
        bool inWork;

        do {
            cout << "\n������� ����� �������� ��������� '� ������': "; cin >> inWork_str;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            inWork = toBool(inWork_str);
        } while (!(isBool(inWork_str)));

        if (state == 1) {
            for (int i = 0; i < size_; i++)
                if (yourPipes[i].get_length() != 0) yourPipes[i]._inWork = toBool(inWork_str);
        }
        if (state == 2) {

            cout << "������� ID ����, ��������� ������� ������ ��������('.' - ��������� �����)";

            string id_str;

            do {
                cout << "\n������� ID: "; cin >> id_str;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                if (isInt(id_str) && is_there_idPipe(yourPipes, toInt(id_str), size_))
                    for (int i = 0; i < yourPipes.size(); i++) {
                        if (yourPipes[i].get_idPipe() == toInt(id_str) && yourPipes[i].get_length() != 0) {
                            yourPipes[i]._inWork = inWork;
                            cout << "�������";
                            break;
                        }
                    }
                else if (id_str == ".") cout << "���������� ��������������! ";
                else cout << "������, ������� ���������� ID!";
            } while (id_str != ".");

        }
    }
    else cout << "\n�������� �����\n\n";
}

void find_pipe(unordered_map<int, Pipe> yourPipes, int size_) {
    if (count_not_null_pipe(yourPipes, size_) != 0) {

        string state_str;
        int state;

        do {
            cout << "�����: 1 - �� ������\n2 - �� ��������� '� ������'\n������� �����: "; cin >> state_str;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            state = toInt(state_str);
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
                parametr_first_case = toFloat(parametr_str);
            } while (!(isFloat(parametr_str)));

            for (int i = 0; i < yourPipes.size(); i++) {
                if (yourPipes[i].get_length() >= parametr_first_case && yourPipes[i].get_length() != 0) cout << "\n\n�����\n" << "ID: " << yourPipes[i].get_idPipe() << "\n�����: " << yourPipes[i].get_length() << "\n�������: " << yourPipes[i].get_diameter() << "\n� ������: " << yourPipes[i]._inWork << "\n";
            }
            break;
        case 2:
            bool parametr_second_case;
            do {
                cout << "������� �������� '� ������': "; cin >> parametr_str;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                parametr_second_case = toBool(parametr_str);
            } while (!(isBool(parametr_str)));

            for (int i = 0; i < yourPipes.size(); i++) {
                if (yourPipes[i]._inWork == parametr_second_case && yourPipes[i].get_length() != 0) cout << "\n\n�����\n" << "ID: " << yourPipes[i].get_idPipe() << "\n�����: " << yourPipes[i].get_length() << "\n�������: " << yourPipes[i].get_diameter() << "\n� ������: " << yourPipes[i]._inWork << "\n";
            }
            break;
        }
    }
    else cout << "\n�������� �����\n\n";
}

void del_pipe(unordered_map<int, Pipe>& yourPipes, int size_) {
    if (count_not_null_pipe(yourPipes, size_) == 0) cout << "\n�������� �����\n\n";
    else {
        string id_str;
        int id = -1;

        out_pipe(yourPipes, size_);
        do {
            cout << "������� ID: "; cin >> id_str;
            if (isInt(id_str)) id = toInt(id_str);
        } while (id < 0 || !(is_there_idPipe(yourPipes, id, size_)));
        yourPipes.erase(id);

        cout << "\n\n����� ������� �������!\n\n";
    }
}
