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

int isInt(string str) {
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
    return atoi(str.c_str());
}

float isFloat(string str) {
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
    return atof(str.c_str());
}

int isBool(string str) {
    if (str == "0" || str == "1") return 0;
    else return -1;
}

pipe yourPipe{};
CS yourCS{};

int stateMenu;
void menu() {
    string stateMenu_str;
    cout << "1. Добавить трубу \n2. Добавить КС \n3. Просмотр всех объектов \n4. Редактировать трубу \n5. Редактировать КС \n6. Сохранить \n7. Загрузить \n0. Выход\n\n";
    cin >> stateMenu_str;
    
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    
    bool err = false;
    for (int i = 0; i < stateMenu_str.size(); i++) {
        if (isdigit(stateMenu_str[i]) == 0) {
            err = true;
            break;
        }
    }

    err ? stateMenu = -1 : stateMenu = isInt(stateMenu_str);
}

void add_pipe() {

    string length_str;
    string diameter_str;
    string inWork_str;

    float length = 0;
    float diameter = 0;
    bool inWork = false;

    do {
        cout << "Введите длину трубы: "; cin >> length_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        length = isFloat(length_str);
    } while (length <= 0);
    do {
        cout << "Введите диаметр трубы: "; cin >> diameter_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n'); 
        diameter = isFloat(diameter_str);
    } while (diameter <= 0);
    do {
        cout << "В работе(1/0): "; cin >> inWork_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        if (isBool(inWork_str) == 0) inWork = isInt(inWork_str);
    } while (isBool(inWork_str) == -1);
    yourPipe = { length, diameter, inWork };
};

void out_pipe() {
    cout << "\n\nТруба\nДлина: " << yourPipe._length << "\nДиаметр: " << yourPipe._diameter << "\nВ работе: " << yourPipe._inWork << "\n";
}

void red_pipe() {
    if (yourPipe._length != 0 || yourPipe._diameter != 0) {

        string inWork_str;

        cout << "\nПараметр 'В работе': " << yourPipe._inWork;
        do {
            cout << "\nВведите новое значение: ";
            cin >> inWork_str;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            if (isBool(inWork_str) == 0) yourPipe._inWork = bool(isInt(inWork_str));
        } while (isBool(inWork_str) == -1);
        system("pause");
        system("cls");

        cout << "\nДанные успешно сохранены!\n";
    }
    else
    {
        cout << "\nДобавьте трубу\n\n";
    }
}

void add_CS() {
    string nameCS_str;
    string shopCount_str;
    string workShopCount_str;

    int shopCount;
    int workShopCount;

    cout << "Введите название КС: "; 
    getline(cin, nameCS_str, '\n');
    do {
        cout << "Введите количество цехов: "; cin >> shopCount_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        shopCount = isInt(shopCount_str);
    } while (shopCount <= 0);
    do {
        cout << "Введите количество цехов в работе (Max: " << shopCount << "): "; cin >> workShopCount_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        workShopCount = isInt(workShopCount_str);
    } while (shopCount < workShopCount || workShopCount < 0);

    yourCS = { nameCS_str, shopCount, workShopCount };

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
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        } while (yourCS._shopCount < workShopCount || workShopCount < 0);


        yourCS._workShopCount = workShopCount;
        system("cls");
        cout << "\nДанные успешно изменены!\n";
        yourCS._efficiency = double(yourCS._workShopCount) / double(yourCS._shopCount);
    }
    else
    {
        cout << "\nДобавьте KC\n\n";
    }
}

//int count_str() {
//    ifstream fin("data.txt");
//
//    string line;
//    int count = 0;
//
//    while (getline(fin, line))
//    {
//        count+=1;
//    }
//
//    return count;
//}

void out_all_to_file() {
    ofstream fout("data.txt");
    if (!(yourPipe._length == 0 && yourPipe._diameter == 0 && yourPipe._inWork == 0)) {
        fout << "Труба\n" << yourPipe._length << "\n" << yourPipe._diameter << "\n" << yourPipe._inWork << "\n";
    }
    else
    {
        fout << "Труба не найдена!\n";
    }
    if (!(yourCS._shopCount == 0 && yourCS._workShopCount == 0)) {
        fout << "\nKC\n" << yourCS._name << "\n" << yourCS._shopCount << "\n" << yourCS._workShopCount << "\n" << yourCS._efficiency << "\n";
    }
    else
    {
        fout << "KC не найдена!\n";
    }
    fout.close();
}

void in_all_at_file() {
    ifstream fin("data.txt");
    

    if (fin.is_open()) {
        
        string str;

        getline(fin, str, '\n');
        if (str == "Труба") {

            getline(fin, str, '\n');
            yourPipe._length = isFloat(str);

            getline(fin, str, '\n');
            yourPipe._diameter = isFloat(str);

            getline(fin, str, '\n');

            if (isBool(str) == -1) {
                yourPipe = { 0, 0, 0 };
                cout << "Ошибка Трубы\n";
            }
            else {
                yourPipe._inWork = isInt(str);
            }
            
            if (yourPipe._length <= 0 || yourPipe._diameter <= 0) {
                yourPipe = { 0, 0, 0 };
                cout << "Ошибка Трубы\n";
            }
            else out_pipe();

        }
        else cout << "Труба не найдена!\n";

        getline(fin, str, '\n');
        getline(fin, str, '\n');
        if (str == "KC") {
            
            getline(fin, str, '\n');
            yourCS._name = str;

            getline(fin, str, '\n');
            yourCS._shopCount = isInt(str);

            getline(fin, str, '\n');
            yourCS._workShopCount = isInt(str);

            yourCS._efficiency = double(yourCS._workShopCount) / double(yourCS._shopCount);

            if (yourCS._shopCount <= 0 || yourCS._workShopCount <= 0 || yourCS._workShopCount > yourCS._shopCount) {
                yourCS = { "", 0, 0, 0 };
                cout << "Ошибка КС\n";
            }
            else out_CS();
        }
        else cout << "KC не найдена!\n";
    }
    else cout << "Файл не удалось открыть\nСоздайте data.txt\n";
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
            break;
        }
    }
}
