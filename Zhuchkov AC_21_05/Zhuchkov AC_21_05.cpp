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
    cout << "1. Добавить трубу \n2. Добавить КС \n3. Просмотр всех объектов \n4. Редактировать трубу \n5. Редактировать КС \n6. Сохранить \n7. Загрузить \n0. Выход\n\n";
    cin >> stateMenu;
}
 
void add_pipe() { 
 
    int length = 0;
    int diameter = 0;
    bool inWork = false;
 
    do {
        cout << "Введите длину трубы: "; cin >> length;
    } while (length <= 0);
    do {
        cout << "Введите диаметр трубы: "; cin >> diameter;
    } while (diameter <= 0);
    cout << "В работе(1/0): "; cin >> inWork;
    
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
    cout << "\n\nТруба\nДлина: "<< yourPipe._length <<"\nДиаметр: "<< yourPipe._diameter << "\nВ работе: " << yourPipe._inWork << "\n";
}
 
void red_pipe() {
    if (yourPipe._length != 0 || yourPipe._diameter != 0) {
        bool inWork;
        cout << "\nПараметр 'В работе': " << yourPipe._inWork << "\nВведите новое значение: ";
        cin >> inWork;
        
        cout << isBool(inWork) << endl << inWork << endl;
        inWork == false ? yourPipe._inWork = 0 : yourPipe._inWork = 1;
 
        system("cls");
        cout << "\nДанные успешно изменены!\n";
        //if (isBool(inWork) == 0) {
        //    yourPipe._inWork = inWork ;
        //    system("cls");
        //    cout << "\nДанные успешно изменены!\n";
        //}
        //else {
        //    system("cls");
        //    cout << "\nДанные некорректны!\n";
        //}
    }
    else
    {
        cout << "\nДобавьте трубу\n\n";
    }
}
 
void add_CS() {
 
    char nameCS[100];
    int shopCount;
    int workShopCount;
 
    cout << "Введите название КС: "; cin >> nameCS;
    do {
        cout << "Введите количество цехов: "; cin >> shopCount;
    } while (shopCount <= 0);
    do {
        cout << "Введите количество цехов в работе (Max: " << shopCount << "): "; cin >> workShopCount;
    } while (shopCount < workShopCount || workShopCount < 0);
    
    cout << nameCS;
 
    yourCS = { nameCS[0], shopCount, workShopCount };
    
    cout << "Эффективность: " << yourCS._efficiency;
};
 
void out_CS() {
    cout << "\n\nKC\nНазвание: " << yourCS._name << "\nКоличество цехов: " << yourCS._shopCount << "\nКоличество цехов в работе: " << yourCS._workShopCount << "\nЭффективность: " << yourCS._efficiency << "\n";
}
 
void red_CS() {
    if (yourCS._shopCount != 0 || yourCS._workShopCount != 0) {
        
        int workShopCount;
        
        cout << "\nПараметр 'Количество цехов в работе': " << yourCS._workShopCount;
 
        do {
            cout << "\nВведите новое значение(Max: " << yourCS._shopCount << "): ";  cin >> workShopCount;
        } while (yourCS._shopCount < workShopCount || workShopCount < 0);
        
        
        yourCS._workShopCount = workShopCount;
        system("cls");
        cout << "\nДанные успешно изменены!\n";
    }
    else
    {
        cout << "\nДобавьте KC\n\n";
    }
}
 
void out_all_to_file() {
    ofstream fout("out.txt");
    if (!(yourPipe._length == 0 && yourPipe._diameter == 0 && yourPipe._inWork == 0)) {
        fout << "Труба\nДлина: " << yourPipe._length << "\nДиаметр: " << yourPipe._diameter << "\nВ работе: " << yourPipe._inWork << "\n\n\n";
    }
    else
    {
        fout << "Трубы не найдено!\n";
    }
    if (!(yourCS._shopCount == 0 && yourCS._workShopCount == 0)) {
        fout << "KC\nНазвание: " << yourCS._name << "\nКоличество цехов: " << yourCS._shopCount << "\nКоличество цехов в работе: " << yourCS._workShopCount << "\nЭффективность: " << yourCS._efficiency << "\n";
    }
    else
    {
        fout << "KC не найдено!\n";
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
