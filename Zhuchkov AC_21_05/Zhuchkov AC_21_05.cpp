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
    cout << "Введите длину трубы: "; cin >> length;
    cout << "Введите диаметр трубы: "; cin >> diameter;
    cout << "В работе: "; cin >> inWork;

    yourPipe = {length, diameter, inWork};
};

void out_pipe() {
    cout << "\n\nТруба\nДлина: "<< yourPipe._length <<"\nДиаметр: "<< yourPipe._diameter << "\nВ работе: " << yourPipe._inWork << "\n";
}

int stateMenu;
void menu() {
    setlocale(LC_ALL, "");
    cout << "1. Добавить трубу \n2. Добавить КС \n3. Просмотр всех объектов \n4. Редактировать трубу \n5. Редактировать КС \n6. Сохранить \n7. Загрузить \n0. Выход\n\n";
    cin >> stateMenu;
}


void red_pipe() {
    int state;
    int length;
    int diameter;
    bool inWork;
    cout << "Труба\nРедактировать:\n(1) Длина\n(2) Диаметр\n(3) В работе\n";
    cin >> state;
    if (state == 1) {
        cout << "\nДлина до изменения: " << yourPipe._length << "\nВведите новую длину: ";
        cin >> length;
        yourPipe._length = length;
        system("cls");
        cout << "\nДанные успешно изменены!\n";
        system("pause");
        system("cls");
        menu();
    }
    else if (state == 2) {
        cout << "\nДиаметр до изменения: " << yourPipe._diameter << "\nВведите новый диаметр: ";
        cin >> diameter;
        yourPipe._diameter = diameter;
        system("cls");
        cout << "\nДанные успешно изменены!\n";
        system("pause");
        system("cls");
        menu();
    }
    else if (state == 3) {
        cout << "\nДиаметр до изменения: " << yourPipe._inWork << "\nВведите новый диаметр: ";
        cin >> inWork;
        yourPipe._inWork = inWork;
        system("cls");
        cout << "\nДанные успешно изменены!\n";
        system("pause");
        system("cls");
        menu();
    }
    else{
        cout << "Некорректные данные..";
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
