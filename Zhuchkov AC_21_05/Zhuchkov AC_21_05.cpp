#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

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


void menu() {
    system("pause");
    system("cls");
    cout << "1. Добавить трубу \n2. Добавить КС \n3. Просмотр всех объектов \n4. Редактировать трубу \n5. Редактировать КС \n6. Сохранить \n7. Загрузить \n8. Поиск объектов по заданному фильтру(Труба) \n9. Поиск объектов по заданному фильтру(КС) \n10. Удалить Трубу\n11. Удалить КС\n0. Выход\n\n";
}

void add_stateMenu(int& stateMenu) {
    string stateMenu_str;

    cin >> stateMenu_str;

    cin.clear();
    cin.ignore(INT_MAX, '\n');

    isInt(stateMenu_str) ? stateMenu = toInt(stateMenu_str) : stateMenu = -1;
}

class Pipe
{
private:
    int _idPipe;
    float _length;
    float _diameter;

public:

    bool _inWork;

    int get_idPipe() {return _idPipe;};
    float get_length() {return _length;};
    float get_diameter() {return _diameter;};
    bool get_inWork() {return _inWork;};

    void add_pipe_inner(int __idPipe, float __length, float __diameter, bool __inWork);

    void out_pipe_inner();
};

void Pipe::add_pipe_inner(int __idPipe, float __length, float __diameter, bool __inWork) {
    _idPipe = __idPipe;
    _length = __length;
    _diameter = __diameter;
    _inWork = __inWork;
}

void Pipe::out_pipe_inner(){
    cout << "\n\nТруба\n" << "ID: " << _idPipe << "\nДлина: " << _length << "\nДиаметр: " << _diameter << "\nВ работе: " << _inWork << "\n";
};

bool is_there_idPipe(unordered_map<int, Pipe> yourPipes, int id, int size_) {
    for (int i = 0; i < size_; i++)
        if (yourPipes[i].get_idPipe() == id && yourPipes[i].get_length() != 0) return true;
    return false;
}

int count_not_null_pipe(unordered_map<int, Pipe> yourPipes,int size_) {
    int count = 0;
    for (int i = 0; i < size_; i++)
        if (yourPipes[i].get_length() != 0) count += 1;
    return count;
}

void add_pipe(unordered_map<int, Pipe>& yourPipes, int& size_){
    string length_str;
    string diameter_str;
    string inWork_str;

    float length = 0;
    float diameter = 0;
    bool inWork = false;

    do {
        cout << "Введите длину трубы: ";
        cin >> length_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        length = toFloat(length_str);
    } while (length == 0);
    do {
        cout << "Введите диаметр трубы: ";
        cin >> diameter_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        diameter = toFloat(diameter_str);
    } while (diameter == 0);
    do {
        cout << "В работе(1/0): ";
        cin >> inWork_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        inWork = toBool(inWork_str);
    } while (!(isBool(inWork_str)));

    yourPipes[size_].add_pipe_inner(size_, length, diameter, inWork);
    size_++;
}

void out_pipe(unordered_map<int, Pipe> yourPipes, int size_){
    for (int i = 0; i < size_; i++){
        if (yourPipes[i].get_length() != 0) yourPipes[i].out_pipe_inner();
    }
}

void edit_pipe(unordered_map<int, Pipe>& yourPipes, int size_) {

    if (count_not_null_pipe(yourPipes, size_) != 0) {

        string state_str;
        int state = -1;

        cout << "1 - Редактирование всех труб \n2 - Редактирование по выбору пользователя \n";

        do {
            cout << "Введите число: "; cin >> state_str;
            state = toInt(state_str);
        } while (!(isInt(state_str)) || !(state == 1 || state == 2));

        string inWork_str;
        bool inWork;

        do {
            cout << "\nВведите новое значение параметра 'В работе': "; cin >> inWork_str;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            inWork = toBool(inWork_str);
        } while (!(isBool(inWork_str)));

        if (state == 1) {
            for (int i = 0; i < size_; i++)
                if (yourPipes[i].get_length() != 0) yourPipes[i]._inWork = toBool(inWork_str);
        }
        if (state == 2) {

            cout << "Вводите ID Труб, параметры которых хотите изменить('.' - окончание цикла)";

            string id_str;

            do {
                cout << "\nВведите ID: "; cin >> id_str;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                if (isInt(id_str) && is_there_idPipe(yourPipes, toInt(id_str), size_))
                    for (int i = 0; i < yourPipes.size(); i++) {
                        if (yourPipes[i].get_idPipe() == toInt(id_str) && yourPipes[i].get_length() != 0) {
                            yourPipes[i]._inWork = inWork;
                            cout << "Успешно";
                            break;
                        }
                    }
                else if (id_str == ".") cout << "Завершение редактирования! ";
                else cout << "Ошибка, введите корректный ID!";
            } while (id_str != ".");

        }
    }
    else cout << "\nДобавьте трубу\n\n";
}

void find_pipe(unordered_map<int, Pipe> yourPipes, int size_) {
    if (count_not_null_pipe(yourPipes, size_) != 0) {

        string state_str;
        int state;

        do {
            cout << "Поиск: 1 - по длинне\n2 - по параметру 'В работе'\nВведите число: "; cin >> state_str;
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
                    cout << "Введите длину: "; cin >> parametr_str;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    parametr_first_case = toFloat(parametr_str);
                } while (!(isFloat(parametr_str)));

                for (int i = 0; i < yourPipes.size(); i++) {
                    if (yourPipes[i].get_length() >= parametr_first_case && yourPipes[i].get_length() != 0) cout << "\n\nТруба\n" << "ID: " << yourPipes[i].get_idPipe() << "\nДлина: " << yourPipes[i].get_length() << "\nДиаметр: " << yourPipes[i].get_diameter() << "\nВ работе: " << yourPipes[i]._inWork << "\n";
                }
                break;
            case 2:
                bool parametr_second_case;
                do {
                    cout << "Введите параметр 'В работе': "; cin >> parametr_str;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    parametr_second_case = toBool(parametr_str);
                } while (!(isBool(parametr_str)));

                for (int i = 0; i < yourPipes.size(); i++) {
                    if (yourPipes[i]._inWork == parametr_second_case && yourPipes[i].get_length() != 0) cout << "\n\nТруба\n" << "ID: " << yourPipes[i].get_idPipe() << "\nДлина: " << yourPipes[i].get_length() << "\nДиаметр: " << yourPipes[i].get_diameter() << "\nВ работе: " << yourPipes[i]._inWork << "\n";
                }
                break;
        }
    }
    else cout << "\nДобавьте трубу\n\n";
}

void del_pipe(unordered_map<int, Pipe>& yourPipes, int size_) {
    if (count_not_null_pipe(yourPipes, size_) == 0) cout << "\nДобавьте трубу\n\n";
    else {
        string id_str;
        int id = -1;

        out_pipe(yourPipes,size_);
        do {
            cout << "Введите ID: "; cin >> id_str;
            if (isInt(id_str)) id = toInt(id_str);
        } while (id < 0 || !(is_there_idPipe(yourPipes, id,size_)));
        yourPipes.erase(id);

        cout << "\n\nТруба успешно удалена!\n\n";
    }
}

class CS {
private:
    int _idCS;
    string _name;
    int _shopCount;
    double _efficiency;
    double _prosentBadShop = (1 - (double(_workShopCount) / double(_shopCount))) * 100;
public:
    int _workShopCount;

    int get_idCS() {return _idCS;};
    string get_name() {return _name;};
    int get_shopCount() {return _shopCount;};
    double get_efficiency() {return _efficiency;};
    double get_prosentBadShop() {return _prosentBadShop;};

    void prosentBadShop_add(double prosent) {_prosentBadShop = prosent;};

    void add_CS_inner(int __idCS, string __name, int __shopCount, int __workShopCount, double __efficiency);

    void out_CS_inner();
};

void CS::add_CS_inner(int __idCS, string __name, int __shopCount, int __workShopCount, double __efficiency) {
    _idCS = __idCS;
    _name = __name;
    _shopCount = __shopCount;
    _workShopCount = __workShopCount;
    _efficiency = __efficiency;
}

void CS::out_CS_inner(){
    cout << "\n\nKC\n" << "ID: " << _idCS << "\nНазвание: " << _name << "\nКоличество цехов: " << _shopCount << "\nКоличество цехов в работе: " << _workShopCount << "\nЭффективность: " << _efficiency << "\nПроцент незадействованных цехов: " << _prosentBadShop << "\n";
};

bool is_there_idCS(unordered_map<int, CS> yourCSs, int id, int size_) {
    for (int i = 0; i < size_; i++)
        if (yourCSs[i].get_idCS() == id && (!(yourCSs[i].get_name().empty()))) return true;
    return false;
}

int count_not_null_CS(unordered_map<int, CS> yourCSs, int size_) {
    int count = 0;
    for (int i = 0; i < size_; i++)
        if (!(yourCSs[i].get_name().empty())) count += 1;
    return count;
}

void add_CS(unordered_map<int, CS>& yourCSs, int& size_) {

    string nameCS_str;
    string shopCount_str;
    string workShopCount_str;
    string efficiency_str;

    int shopCount;
    int workShopCount;
    double efficiency;

    do {
        cout << "Введите название КС: ";
        getline(cin, nameCS_str, '\n');
    } while (nameCS_str.empty());

    do {
        cout << "Введите количество цехов: "; cin >> shopCount_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        shopCount = toInt(shopCount_str);
    } while (shopCount == 0);
    do {
        cout << "Введите количество цехов в работе (Max: " << shopCount << "): "; cin >> workShopCount_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        workShopCount = toInt(workShopCount_str);
    } while (shopCount < workShopCount || !(isInt(workShopCount_str)));
    do {
        cout << "Введите эффективность: "; cin >> efficiency_str;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        efficiency = toFloat(efficiency_str);
    } while (!(isFloat(efficiency_str)));

    yourCSs[size_].add_CS_inner(size_, nameCS_str, shopCount, workShopCount, efficiency);
    size_++;
    /*cout << "Эффективность: " << yourCSs._efficiency;*/
};

void out_CS(unordered_map<int, CS> yourCSs, int size_) {
    for (int i = 0; i < size_; i++)
        if (!(yourCSs[i].get_name().empty()))
            cout << "\n\nKC\n" << "ID: " << yourCSs[i].get_idCS() << "\nНазвание: " << yourCSs[i].get_name() << "\nКоличество цехов: " << yourCSs[i].get_shopCount() << "\nКоличество цехов в работе: " << yourCSs[i]._workShopCount << "\nЭффективность: " << yourCSs[i].get_efficiency() << "\nПроцент незадействованных цехов: " << yourCSs[i].get_prosentBadShop() << "\n";
}

void edit_CS(unordered_map<int, CS>& yourCSs, int size_) {
    if (count_not_null_CS(yourCSs, size_) != 0) {

        string id_str;
        int id = -1;

        out_CS(yourCSs,size_);

        do {
            cout << "\nВведите ID: "; cin >> id_str;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            id = toInt(id_str);
        } while (!(isInt(id_str)) || !(is_there_idCS(yourCSs, toInt(id_str), size_)));

        string workShopCount_str;
        int workShopCount;

        cout << "\nПараметр 'Количество цехов в работе': " << yourCSs[id]._workShopCount;

        do {
            cout << "\nВведите новое значение(Max: " << yourCSs[id].get_shopCount() << "): ";  cin >> workShopCount_str;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            workShopCount = toInt(workShopCount_str);
        } while (yourCSs[id].get_shopCount() < workShopCount || !(isInt(workShopCount_str)));

        yourCSs[id]._workShopCount = workShopCount;

        system("cls");
        cout << "\nДанные успешно изменены!\n\n";
        yourCSs[id].prosentBadShop_add((1 - (double(yourCSs[id]._workShopCount) / double(yourCSs[id].get_shopCount()))) * 100);
    }
    else cout << "\nДобавьте KC\n\n";
}

void del_CS(unordered_map<int, CS>& yourCSs, int size_) {
    if (count_not_null_CS(yourCSs, size_) == 0) cout << "\nДобавьте КС\n\n";
    else {
        string id_str;
        int id = -1;

        out_CS(yourCSs, size_);
        do {
            cout << "Введите ID: "; cin >> id_str;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            id = toInt(id_str);
        } while (!(isInt(id_str)) || !(is_there_idCS(yourCSs, id,size_)));
        yourCSs.erase(id);

        cout << "\n\nКС успешно удалена!\n\n";
    }
}

void find_CS(unordered_map<int, CS> yourCSs, int size_) {
    if (count_not_null_CS(yourCSs, size_) != 0) {

        string state_str;
        int state;

        do {
            cout << "Поиск: 1 - по названию\n2 - по проценту незадействованных цехов\nВведите число: "; cin >> state_str;

            cin.clear();
            cin.ignore(INT_MAX, '\n');

            state = toInt(state_str);
        } while (!(isInt(state_str)) || !(toInt(state_str) == 1 || toInt(state_str) == 2));

        string parametr_str;

        switch (state)
        {
            case 1:
                cout << "Введите название: ";
                getline(cin, parametr_str, '\n');
                /*cout << parametr_str << endl;*/
                for (int i = 0; i < size_; i++) {
                    cout << '"' << (yourCSs[i].get_name()) << '"' << endl;
                    if (yourCSs[i].get_name() == parametr_str && !(yourCSs[i].get_name().empty())) cout << "\n\nKC\n" << "ID: " << yourCSs[i].get_idCS() << "\nНазвание: " << yourCSs[i].get_name() << "\nКоличество цехов: " << yourCSs[i].get_shopCount() << "\nКоличество цехов в работе: " << yourCSs[i]._workShopCount << "\nЭффективность: " << yourCSs[i].get_efficiency() << "\nПроцент незадействованных цехов: " << yourCSs[i].get_prosentBadShop() << "\n";
                }
                break;
            case 2:
                float parametr;
                do {
                    cout << "Введите процент незадействованных цехов: "; cin >> parametr_str;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    parametr = toFloat(parametr_str);
                } while (!(isFloat(parametr_str)));

                for (int i = 0; i < size_; i++) {
                    if (yourCSs[i].get_prosentBadShop() >= parametr && !(yourCSs[i].get_name().empty())) cout << "\n\nKC\n" << "ID: " << yourCSs[i].get_idCS() << "\nНазвание: " << yourCSs[i].get_name() << "\nКоличество цехов: " << yourCSs[i].get_shopCount() << "\nКоличество цехов в работе: " << yourCSs[i]._workShopCount << "\nЭффективность: " << yourCSs[i].get_efficiency() << "\nПроцент незадействованных цехов: " << yourCSs[i].get_prosentBadShop() << "\n";
                }
                break;
        }
    }
    else cout << "\nДобавьте КС\n\n";
}

void out_all_to_file(unordered_map<int, Pipe> yourPipes,int size_p, unordered_map<int, CS> yourCSs, int size_c) {
    if (count_not_null_pipe(yourPipes, size_p) == 0 && count_not_null_CS(yourCSs,size_c) == 0) cout << "\nДобавьте Трубу или КС\n\n";
    else {
        string fileName_str;

        cout << "Введите название файла: "; cin >> fileName_str;

        ofstream fout(fileName_str + ".txt");

        fout << size_p << "\n" << size_c << "\n";

        for (int i = 0; i < size_p; i++) {
            fout << yourPipes[i].get_idPipe() << "\n" << yourPipes[i].get_length() << "\n" << yourPipes[i].get_diameter() << "\n" << yourPipes[i]._inWork << "\n";
        }
        for (int i = 0; i < size_c; i++) {
            fout << yourCSs[i].get_idCS() << "\n" << yourCSs[i].get_name() << "\n" << yourCSs[i].get_shopCount() << "\n" << yourCSs[i]._workShopCount << "\n" << yourCSs[i].get_efficiency() << "\n";
        }

        fout.close();
    }
}

void in_all_at_file(unordered_map<int, Pipe>& yourPipes,int& size_p, unordered_map<int, CS>& yourCSs, int& size_c) {

    string fileName_str;
    cout << "Введите название файла: "; cin >> fileName_str;

    ifstream fin(fileName_str + ".txt");

    if (fin.is_open()) {

        string str;
        string count_pipe;
        string count_CS;

        int id;

        float length;
        float diameter;
        bool inWork;

        string name;
        int shopCount;
        int workShopCount;
        double efficiency;
        double prosentBadShop;

        getline(fin, count_pipe, '\n');
        getline(fin, count_CS, '\n');

        yourPipes.clear();
        yourCSs.clear();

        for (int i = 0; i < toInt(count_pipe); i++) {

            getline(fin, str, '\n');
            id = toInt(str);

            getline(fin, str, '\n');
            length = toFloat(str);

            getline(fin, str, '\n');
            diameter = toFloat(str);

            getline(fin, str, '\n');
            inWork = bool(str.c_str());

            yourPipes[id].add_pipe_inner( id, length , diameter , inWork );
            size_p = id++;
        }
        out_pipe(yourPipes, size_p);

        for (int i = 0; i < toInt(count_CS); i++) {

            getline(fin, str, '\n');
            id = toInt(str);

            getline(fin, name, '\n');

            getline(fin, str, '\n');
            shopCount = toInt(str);

            getline(fin, str, '\n');
            workShopCount = toInt(str);

            getline(fin, str, '\n');
            efficiency = toFloat(str);

            prosentBadShop = (1 - (double(workShopCount) / double(shopCount))) * 100;

            yourCSs[id].add_CS_inner(id, name , shopCount , workShopCount , efficiency);
            size_c = id++;
        }
        out_CS(yourCSs,size_c);

        fin.close();
    }
    else cout << "Не удалось найти файл\n";
}

int main(){
    int size_p = 0;
    int size_c = 0;
    unordered_map<int, Pipe> yourPipes;
    unordered_map<int, CS> yourCSs;
    int stateMenu = -1;

    setlocale(LC_ALL, "");
    menu();

    while (stateMenu)
    {
        add_stateMenu(stateMenu);
        switch (stateMenu) {
            case 1:
                add_pipe(yourPipes, size_p);
                menu();
                break;
            case 2:
                add_CS(yourCSs, size_c);
                menu();
                break;
            case 3:
                out_pipe(yourPipes, size_p);
                out_CS(yourCSs, size_c);
                menu();
                break;
            case 4:
                edit_pipe(yourPipes, size_p);
                menu();
                break;
            case 5:
                edit_CS(yourCSs, size_c);
                menu();
                break;
            case 6:
                out_all_to_file(yourPipes, size_p, yourCSs, size_c);
                menu();
                break;
            case 7:
                in_all_at_file(yourPipes, size_p, yourCSs, size_c);
                menu();
                break;
            case 8:
                find_pipe(yourPipes, size_p);
                menu();
                break;
            case 9:
                find_CS(yourCSs, size_c);
                menu();
                break;
            case 10:
                del_pipe(yourPipes, size_p);
                menu();
                break;
            case 11:
                del_CS(yourCSs, size_c);
                menu();
                break;
            default:
                menu();
                break;
        }}}