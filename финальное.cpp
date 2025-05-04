#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>  
#include <unordered_map>
using namespace std;

enum Role {
    CLIENT = 0,
    OPER = 1,
    MANAGER = 2
};

Role getRole(int key) {
    std::unordered_map<int, Role> accessKeys = {
        {1234, CLIENT},
        {1, OPER},
        {23, MANAGER}
    };

    if (accessKeys.find(key) != accessKeys.end()) {
        return accessKeys[key];
    }

    return CLIENT;
}

bool isLoginUnique(const std::string& login, const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return true;
    }

    std::string line;
    while (getline(file, line)) {
        size_t pos = line.find(' ');
        if (pos != std::string::npos) {
            string fileLogin = line.substr(0, pos);
            if (fileLogin == login) {
                return false;
            }
        }
    }

    return true;
}

template<typename T>
void sortData(std::vector<T>& data) {
    cout << "Сортировка выполнена\n";
}

bool isNumber(const string& str) {
    if (str.empty()) return false;

    size_t start = 0;
    if (str[0] == '-') {
        if (str.length() == 1) return false;
        start = 1;
    }

    for (size_t i = start; i < str.length(); ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }

    return true;
}

bool isNum(const string& str) {
    if (str.empty()) return false;

    size_t start = 0;
    if (str[0] == '-') {
        if (str.length() == 1) return false;
        start = 1;
    }

    for (size_t i = start; i < str.length(); ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

int getChoiceFromUser() {
    string input;
    while (true) {
        cin >> input;

        if (!isNum(input)) {
            cout << "Ошибка: введите допустимое число." << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }

        int choice;
        try {
            choice = stoi(input);
        }
        catch (const out_of_range&) {
            cout << "Ошибка: введите число от 0 до 3." << endl;
            continue;
        }

        if (choice < 0 || choice > 3) {
            cout << "Ошибка: введите число от 0 до 3." << endl;
            continue;
        }

        return choice;
    }
}

int getChoice() {
    string input;
    while (true) {
        cin >> input;

        if (!isNum(input)) {
            cout << "Ошибка: введите допустимое число." << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }

        int choice;
        try {
            choice = stoi(input);
        }
        catch (const out_of_range&) {
            cout << "Ошибка: введите число от 0 до 6." << endl;
            continue;
        }

        if (choice < 0 || choice > 6) {
            cout << "Ошибка: введите число от 0 до 6." << endl;
            continue;
        }

        return choice;
    }
}

bool isNumberic(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool isValidLogin(const string& str) {
    if (str.empty()) {
        cout << "Ошибка: логин не может быть пустым." << endl;
        return false;
    }

    for (char ch : str) {
        if (!((ch >= 'A' && ch <= 'Z') ||
            (ch >= 'a' && ch <= 'z') ||
            (ch >= '0' && ch <= '9'))) {
            cout << "Ошибка: логин может содержать только латинские буквы и цифры." << endl;
            return false;
        }
    }

    return true;
}

struct Product {
    int productNumber;
    string productName;
    int quantity;
};

namespace hashing {
    class Hash {
    public:
        string getHash(const string& input) {
            hash<string> hasher;
            return to_string(hasher(input));
        }
    };
}

class Human {
protected:
    string firstName;
    string lastName;
    string country;
public:
    Human() : firstName(""), lastName(""), country("") {}
    Human(string fName, string lName, string cntry) : firstName(fName), lastName(lName), country(cntry) {}
    void setFirstName(string fName) {
        if (!isNumber(fName)) {
            firstName = fName;
        }
        else {
            cout << "Ошибка." << endl;
        }
    }
    void setLastName(string lName) {
        if (!isNumber(lName)) {
            lastName = lName;
        }
        else {
            cout << "Ошибка." << endl;
        }
    }
    void setCountry(string cntry) {
        if (!isNumber(cntry)) {
            country = cntry;
        }
        else {
            cout << "Ошибка." << endl;
        }
    }
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    string getCountry() const { return country; }
};

class Registration {
private:
    Human human;
    string getPass() {
        string pass;
        char symbol;
        while (true) {
            symbol = _getch();
            if (symbol == 13) break;
            if (symbol == 8 && pass.size() > 0) {
                pass.pop_back();
                cout << "\b \b";
            }
            else if (symbol >= 32) {
                pass += symbol;
                cout << '*';
            }
        }
        cout << endl;
        return pass;
    }
    void displayMenu(const string menu[], int active) {
        system("cls");
        for (int i = 0; i < 2; ++i) {
            if (i == active)
                SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE);
            else
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cout << menu[i] << endl;
        }
    }
public:
    string LoginUser, PasswordUser;
    int accessKey;
    Role userRole;
    bool validKey = false;
    string RegDATA = "DATARegistr.txt";
    int Access = -1;
    int userRoleId = -1;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    void Regist() {
        system("cls");
        cout << "-----------Регистрация-------------" << endl;

        string login, password;
        int accessKey;

        do {
            cout << "Введите логин (только латиница и цифры): ";
            cin >> login;

            if (!isLoginUnique(login, "DATARegistr.txt")) {
                cout << "Ошибка: логин уже существует. Попробуйте снова.\n";
                continue;
            }

            if (!isValidLogin(login)) {
                cout << "Ошибка: логин должен содержать только латиницу и цифры. Попробуйте снова.\n";
            }

        } while (!isLoginUnique(login, "DATARegistr.txt") || !isValidLogin(login));

        cout << "Введите пароль: ";
        password = getPass();

        string firstName, lastName, country;
        cout << "Введите имя: ";
        cin >> firstName;
        human.setFirstName(firstName);

        cout << "Введите фамилию: ";
        cin >> lastName;
        human.setLastName(lastName);

        cout << "Введите страну: ";
        cin >> country;
        human.setCountry(country);

        string inputKey;
        Role userRole;
        bool validKey = false;

        do {
            cout << "Введите ключ доступа (только цифры): ";
            cin >> inputKey;

            if (isNumberic(inputKey)) {
                accessKey = stoi(inputKey);
                userRole = getRole(accessKey);

                if (userRole != CLIENT || accessKey == 1234) {
                    validKey = true;
                    break;
                }
                else {
                    cout << "Неверный ключ доступа. Попробуйте снова.\n";
                }
            }
            else {
                cout << "Ошибка: ключ доступа должен содержать только цифры. Попробуйте снова.\n";
            }

        } while (!validKey);

        ofstream fout(RegDATA, ios::app);
        if (!fout.is_open()) {
            cout << "Ошибка: не удалось открыть файл для записи данных.\n";
            return;
        }

        hashing::Hash hash;
        string hashedPassword = hash.getHash(password);

        cout << "Login: " << login << "\n";
        cout << "Hashed Password: " << hashedPassword << "\n";
        cout << "Role: " << static_cast<int>(userRole) << "\n";

        fout << login << " " << hashedPassword << " " << static_cast<int>(userRole) << endl;
        fout.close();

        cout << "\nРегистрация завершена.\n";
        ShowRole(userRole);
        system("pause");
        system("cls");
    }

    void EnterToProgram() {
        hashing::Hash hash;
        system("cls");
        string log, pass;

        cout << "Введите логин: ";
        cin >> log;
        cout << "Введите пароль: ";
        pass = getPass();

        ifstream fin(RegDATA);
        if (!fin.is_open()) {
            cout << "Ошибка: не удалось открыть файл с данными авторизации!\n";
            system("pause");
            return;
        }

        bool foundUser = false;
        string fileLog, filePass;
        int fileRole;

        while (fin >> fileLog >> filePass >> fileRole) {
            if (log == fileLog && hash.getHash(pass) == filePass) {
                foundUser = true;
                LoginUser = log;
                PasswordUser = pass;
                userRoleId = fileRole;
                userRole = static_cast<Role>(fileRole);
                break;
            }
        }

        fin.close();

        if (foundUser) {
            ShowRole(userRole);
        }
        else {
            cout << "Ошибка: неверный логин или пароль.\n";
            system("pause");
        }
    }

    void ShowRole(const Role& userRole) {
        switch (userRole) {
        case CLIENT:
            cout << "Вы вошли как Клиент.\n";
            break;
        case OPER:
            cout << "Вы вошли как Оператор.\n";
            break;
        case MANAGER:
            cout << "Вы вошли как Менеджер.\n";
            break;
        default:
            cout << "Ошибка: роль не распознана.\n";
            break;
        }
    }
};

class User {
protected:
    string login;
    string password;
    Role role;
public:
    User(const string& login, const string& password, Role role)
        : login(login), password(password), role(role) {}

    string getLogin() const { return login; }
    void setLogin(const string& login) { this->login = login; }

    string getPassword() const { return password; }
    void setPassword(const string& password) { this->password = password; }

    Role getRole() const { return role; }
};

class Klient : public User {
private:
    string skladFile;

public:
    Klient(const string& login, const string& password, const string& skladFile)
        : User(login, password, CLIENT), skladFile(skladFile) {}

    string trim(const string& str) {
        size_t first = str.find_first_not_of(" \t");
        if (first == string::npos) return "";
        size_t last = str.find_last_not_of(" \t");
        return str.substr(first, last - first + 1);
    }

    bool isProductQuantityValid(const string& product, int requestedQuantity) {
        ifstream fin(skladFile);
        if (!fin.is_open()) {
            cout << "Ошибка: Не удалось открыть файл склада: " << skladFile << endl;
            return false;
        }

        int totalQuantity = 0;
        string line;

        while (getline(fin, line)) {
            istringstream ss(line);
            string itemNumberStr, fileProduct, fileQuantityStr;
            int fileQuantity;

            if (!getline(ss, itemNumberStr, '|') ||
                !getline(ss, fileProduct, '|') ||
                !getline(ss, fileQuantityStr, '|')) {
                cout << "Ошибка формата данных в файле склада: " << line << endl;
                continue;
            }

            itemNumberStr = trim(itemNumberStr);
            fileProduct = trim(fileProduct);
            fileQuantityStr = trim(fileQuantityStr);

            try {
                fileQuantity = stoi(fileQuantityStr);
            }
            catch (...) {
                cout << "Ошибка преобразования количества в файле склада: " << fileQuantityStr << endl;
                continue;
            }

            if (fileProduct == product) {
                totalQuantity += fileQuantity;
            }
        }

        fin.close();

        if (totalQuantity >= requestedQuantity) {
            cout << "Достаточно товара: требуется " << requestedQuantity << ", на складе " << totalQuantity << endl;
            return true;
        }
        else {
            cout << "Недостаточно товара: требуется " << requestedQuantity << ", на складе " << totalQuantity << endl;
            return false;
        }
    }

    void createOrder(const string& ordersFile) {
        ofstream fout(ordersFile, ios::app);
        if (!fout.is_open()) {
            cout << "Ошибка открытия файла заказов.\n";
            return;
        }

        string product, destination, paymentType, rate;
        string quantityInput;
        int quantity;

        cout << "Введите название товара: ";
        cin.ignore();
        getline(cin, product);

        cout << "Введите пункт назначения: ";
        getline(cin, destination);

        do {
            cout << "Введите количество: ";
            cin >> quantityInput;

            if (!isNumber(quantityInput) ){
                cout << "Ошибка: Введите число.\n";
                continue;
            }

            quantity = stoi(quantityInput);
                if (quantity <= 0) {
                    cout << "Ошибка: Введите положительное число.\n";
                }
                else if (!isProductQuantityValid(product, quantity)) {
                    cout << "Ошибка: Недостаточно товара на складе.\n";
                    fout.close();
                    return;
                }
                else {
                    break;
                }
        } while (true);

        do {
            cout << "Введите тариф (воздушный, наземный, водный): ";
            cin >> rate;
        } while (!isValidTransportType(rate));

        cout << "Выберите оплату (При получении/Сразу): ";
        cin.ignore();
        do {
            getline(cin, paymentType);
        } while (!isValidPaymentType(paymentType));

        fout << login << " " << product << " " << destination << " "
            << quantity << " " << rate << " " << paymentType << endl;

        fout.close();
        cout << "Заказ успешно создан!\n";
    }

    void viewOrders(const string& ordersFile) {
        ifstream fin(ordersFile);
        if (!fin.is_open()) {
            cout << "Ошибка открытия файла заказов.\n";
            return;
        }

        string line;
        cout << "Ваши заказы:\n";
        bool hasOrders = false;

        while (getline(fin, line)) {
            istringstream ss(line);
            string user;
            ss >> user;
            if (user == login) {
                cout << line << endl;
                hasOrders = true;
            }
        }

        if (!hasOrders) {
            cout << "У вас пока нет заказов.\n";
        }

        fin.close();
    }

    void editOrder(const string& ordersFile) {
        ifstream fin(ordersFile);
        if (!fin.is_open()) {
            cout << "Ошибка открытия файла заказов.\n";
            return;
        }

        vector<string> orders;
        string line, productName, newDestination, newPayment;
        string quantityInput;
        int newQuantity;
        string newRate;
        bool found = false;

        cout << "Введите название товара для редактирования: ";
        cin >> productName;
        cin.ignore(INT_MAX, '\n');

        while (getline(fin, line)) {
            istringstream ss(line);
            string user, product, destination, rate, paymentType;
            int qty;

            ss >> user >> product >> destination >> qty >> rate;
            getline(ss, paymentType);

            if (user == login && product == productName) {
                found = true;

                do {
                    cout << "Введите новое количество: ";
                    cin >> quantityInput;
                    if (!isNumber(quantityInput) || (newQuantity = stoi(quantityInput)) <= 0) {
                        cout << "Ошибка: Введите положительное число.\n";
                    }
                    else {
                        break;
                    }
                } while (true);

                cout << "Введите новый пункт назначения: ";
                cin.ignore();
                getline(cin, newDestination);

                do {
                    cout << "Введите новый тариф (воздушный, наземный, водный): ";
                    cin >> newRate;
                } while (!isValidTransportType(newRate));

                // Сохраняем обновлённый заказ
                string updatedOrder = user + " " + product + " " + newDestination + " " +
                    to_string(newQuantity) + " " + newRate + paymentType;
                orders.push_back(updatedOrder);
            }
            else {
                orders.push_back(line);
            }
        }

        fin.close();

        if (!found) {
            cout << "Заказ не найден.\n";
            return;
        }

        ofstream fout(ordersFile);
        if (!fout.is_open()) {
            cout << "Ошибка открытия файла для записи.\n";
            return;
        }

        for (const auto& order : orders) {
            fout << order << endl;
        }

        fout.close();
        cout << "Заказ успешно отредактирован.\n";
    }

    static bool isValidTransportType(const string& transport) {
        string loweredTransport = transport;
        transform(loweredTransport.begin(), loweredTransport.end(), loweredTransport.begin(), ::tolower);
        return loweredTransport == "воздушный" || loweredTransport == "наземный" || loweredTransport == "водный";
    }

    static bool isValidPaymentType(const string& payment) {
        string loweredPayment = payment;
        transform(loweredPayment.begin(), loweredPayment.end(), loweredPayment.begin(), ::tolower);
        return loweredPayment == "при получении" || loweredPayment == "сразу";
    }

    void viewSklad(const string& skladFile) {
        ifstream fin(skladFile);
        if (!fin.is_open()) {
            cout << "Ошибка открытия файла склада.\n";
            return;
        }

        string line;
        cout << "Список товаров на складе:\n";
        while (getline(fin, line)) {
            cout << line << endl;
        }
        fin.close();
    }

    void searchSklad(const string& skladFile, const string& keyword) {
        ifstream fin(skladFile);
        if (!fin.is_open()) {
            cout << "Ошибка открытия файла склада.\n";
            return;
        }

        string line;
        bool found = false;
        cout << "Результаты поиска по ключевому слову '" << keyword << "':\n";
        while (getline(fin, line)) {
            if (line.find(keyword) != string::npos) {
                cout << line << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "Товары не найдены." << endl;
        }
        fin.close();
    }
};

class Operator : public User {
public:
    Operator(const string& login, const string& password)
        : User(login, password, OPER) {}

    void viewSklad(const string& skladFile) {
        ifstream fin(skladFile);
        if (!fin.is_open()) {
            cout << "Ошибка открытия файла склада.\n";
            return;
        }

        string line;
        cout << "Список товаров на складе:\n";
        while (getline(fin, line)) {
            cout << line << endl;
        }
        fin.close();
    }

    void viewAllOrders(const string& ordersFile) {
        ifstream fin(ordersFile);
        if (!fin.is_open()) {
            cout << "Ошибка открытия файла заказов.\n";
            return;
        }

        string line;
        cout << "Все заказы:\n";
        while (getline(fin, line)) {
            cout << line << endl;
        }
        fin.close();
    }

    void searchOrders(const string& ordersFile, const string& clientLogin) {
        ifstream fin(ordersFile);
        if (!fin.is_open()) {
            cout << "Ошибка открытия файла заказов.\n";
            return;
        }

        string line;
        bool found = false;
        cout << "Заказы клиента '" << clientLogin << "':\n";
        while (getline(fin, line)) {
            istringstream ss(line);
            string user;
            ss >> user;
            if (user == clientLogin) {
                cout << line << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "Заказы не найдены." << endl;
        }
        fin.close();
    }

    void filterOrdersByStatus(const string& ordersFile, const string& status) {
        ifstream fin(ordersFile);
        if (!fin.is_open()) {
            cout << "Ошибка открытия файла заказов.\n";
            return;
        }

        string line;
        bool found = false;
        cout << "Заказы со статусом '" << status << "':\n";
        while (getline(fin, line)) {
            if (line.find(status) != string::npos) {
                cout << line << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "Заказы не найдены." << endl;
        }
        fin.close();
    }

    void editOrderStatus(const string& ordersFile, const string& clientLogin, const string& newStatus) {
        ifstream fin(ordersFile);
        if (!fin.is_open()) {
            cout << "Ошибка открытия файла заказов.\n";
            return;
        }

        vector<string> orders;
        string line;
        bool found = false;

        while (getline(fin, line)) {
            istringstream ss(line);
            string user;
            ss >> user;

            if (user == clientLogin) {
                found = true;
                // Добавляем статус в конец строки
                line += " Статус: " + newStatus;
            }
            orders.push_back(line);
        }
        fin.close();

        if (!found) {
            cout << "Заказ клиента '" << clientLogin << "' не найден.\n";
            return;
        }

        ofstream fout(ordersFile);
        if (!fout.is_open()) {
            cout << "Ошибка открытия файла для записи.\n";
            return;
        }

        for (const auto& order : orders) {
            fout << order << endl;
        }
        fout.close();
        cout << "Статус заказа успешно изменен.\n";
    }

    void calculateAndAddCost(const string& ordersFile, const string& clientLogin, double ratePerUnit) {
        ifstream fin(ordersFile);
        if (!fin.is_open()) {
            cout << "Ошибка открытия файла заказов.\n";
            return;
        }

        vector<string> orders;
        string line;
        bool found = false;

        while (getline(fin, line)) {
            istringstream ss(line);
            string user, product, destination, paymentType;
            int quantity;
            string rate;

            ss >> user >> product >> destination >> quantity >> rate;
            getline(ss, paymentType); // Получаем остаток строки

            if (user == clientLogin) {
                found = true;
                double cost = quantity * ratePerUnit;
                line += " Стоимость: " + to_string(cost);
            }
            orders.push_back(line);
        }
        fin.close();

        if (!found) {
            cout << "Заказ клиента '" << clientLogin << "' не найден.\n";
            return;
        }

        ofstream fout(ordersFile);
        if (!fout.is_open()) {
            cout << "Ошибка открытия файла для записи.\n";
            return;
        }

        for (const auto& order : orders) {
            fout << order << endl;
        }
        fout.close();
        cout << "Стоимость заказа успешно добавлена.\n";
    }
};

class Manager : public User {
private:
    string skladFile;
    string clientsFile;
    string ordersFile;

    void displayError(const string& fileName) const {
        cout << "Ошибка открытия файла: " << fileName << endl;
    }

    vector<string> readFileLines(const string& fileName) const {
        ifstream fin(fileName);
        if (!fin.is_open()) {
            displayError(fileName);
            return {};
        }

        vector<string> lines;
        string line;
        while (getline(fin, line)) {
            lines.push_back(line);
        }
        fin.close();
        return lines;
    }

    void writeFileLines(const string& fileName, const vector<string>& lines) const {
        ofstream fout(fileName);
        if (!fout.is_open()) {
            displayError(fileName);
            return;
        }

        for (const auto& line : lines) {
            fout << line << endl;
        }
        fout.close();
    }

public:
    Manager(const string& login, const string& password, Role role, const string& skladFile, const string& clientsFile, const string& ordersFile)
        : User(login, password, role), skladFile(skladFile), clientsFile(clientsFile), ordersFile(ordersFile) {}

    void viewFile(const string& fileName) const {
        vector<string> lines = readFileLines(fileName);
        if (lines.empty()) return;

        for (const auto& line : lines) {
            cout << line << endl;
        }
    }

    void addProductToSklad() {
        Product product;

        cout << "Введите номер товара: ";
        while (!(cin >> product.productNumber)) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Ошибка: введите число для номера товара: ";
        }
        cin.ignore();

        cout << "Введите название товара: ";
        getline(cin, product.productName);

        cout << "Введите количество товара: ";
        while (!(cin >> product.quantity)) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Ошибка: введите число для количества: ";
        }

        ofstream fout(skladFile, ios::app);
        if (!fout.is_open()) {
            displayError(skladFile);
            return;
        }

        fout << product.productNumber << " | " << product.productName << " | " << product.quantity << endl;
        fout.close();

        cout << "Товар успешно добавлен в склад.\n";
    }

    void addClient() {
        ofstream fout(clientsFile, ios::app);
        if (!fout.is_open()) {
            displayError(clientsFile);
            return;
        }

        string login, name, surname, email, phone;

        cout << "Введите логин клиента: ";
        cin.ignore();
        getline(cin, login);

        cout << "Введите имя клиента: ";
        getline(cin, name);

        cout << "Введите фамилию клиента: ";
        getline(cin, surname);

        cout << "Введите email клиента: ";
        getline(cin, email);

        cout << "Введите телефон клиента: ";
        getline(cin, phone);

        fout << login << " | " << name << " | " << surname << " | " << email << " | " << phone << endl;
        fout.close();

        cout << "Клиент успешно добавлен!\n";
    }

    void addOrderRecord() {
        string clientLogin, product, destination, paymentType, rate;
        int quantity;

        cout << "Введите логин клиента: ";
        cin >> clientLogin;
        cout << "Введите название товара: ";
        cin.ignore();
        getline(cin, product);
        cout << "Введите пункт назначения: ";
        getline(cin, destination);

        cout << "Введите количество: ";
        while (!(cin >> quantity) || quantity <= 0) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Ошибка: введите положительное число: ";
        }

        do {
            cout << "Введите тариф (воздушный, наземный, водный): ";
            cin >> rate;
        } while (rate != "воздушный" && rate != "наземный" && rate != "водный");

        do {
            cout << "Введите способ оплаты (при получении/сразу): ";
            cin >> paymentType;
        } while (paymentType != "при получении" && paymentType != "сразу");

        ofstream fout(ordersFile, ios::app);
        if (!fout.is_open()) {
            displayError(ordersFile);
            return;
        }

        fout << clientLogin << " | " << product << " | " << destination << " | "
            << quantity << " | " << rate << " | " << paymentType << endl;
        fout.close();

        cout << "Заказ успешно добавлен.\n";
    }

    void searchInFile(const string& fileName, const string& keyword) const {
        vector<string> lines = readFileLines(fileName);
        if (lines.empty()) return;

        bool found = false;
        for (const auto& line : lines) {
            if (line.find(keyword) != string::npos) {
                cout << line << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "Записи не найдены." << endl;
        }
    }

    void sortFile(const string& fileName) const {
        vector<string> lines = readFileLines(fileName);
        if (lines.empty()) return;

        sort(lines.begin(), lines.end());
        writeFileLines(fileName, lines);

        cout << "Файл успешно отсортирован.\n";
    }

    void deleteFromFile(const string& fileName, const string& key) {
        vector<string> lines = readFileLines(fileName);
        if (lines.empty()) return;

        size_t initialSize = lines.size();
        lines.erase(remove_if(lines.begin(), lines.end(),
            [&key](const string& line) { return line.find(key) != string::npos; }),
            lines.end());

        if (lines.size() == initialSize) {
            cout << "Запись с ключом '" << key << "' не найдена.\n";
            return;
        }

        writeFileLines(fileName, lines);
        cout << "Запись успешно удалена.\n";
    }

    void viewSklad() const { viewFile(skladFile); }
    void searchInSklad(const string& keyword) const { searchInFile(skladFile, keyword); }
    void sortSklad() const { sortFile(skladFile); }
    void deleteSkladRecord(const string& key) { deleteFromFile(skladFile, key); }

    void viewClients() const { viewFile(clientsFile); }
    void searchInClients(const string& keyword) const { searchInFile(clientsFile, keyword); }
    void sortClients() const { sortFile(clientsFile); }
    void deleteClientRecord(const string& key) { deleteFromFile(clientsFile, key); }

    void viewOrders() const { viewFile(ordersFile); }
    void searchInOrders(const string& keyword) const { searchInFile(ordersFile, keyword); }
    void sortOrders() const { sortFile(ordersFile); }
    void deleteOrderRecord(const string& key) { deleteFromFile(ordersFile, key); }
};

void ClientMenu(Klient& klient, const string& ordersFile, const string& skladFile) {
    int option;
    do {
        system("cls");
        cout << "----- Меню Клиента -----\n";
        cout << "1. Работа со складом\n";
        cout << "2. Создать заказ\n";
        cout << "3. Просмотр заказов\n";
        cout << "4. Редактирование незакрытого заказа\n";
        cout << "5. Выход в главное меню\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        option = getChoice();

        switch (option) {
        case 1: {
            system("cls");
            cout << "----- Работа со складом -----\n";
            cout << "1. Просмотреть склад\n";
            cout << "2. Поиск товаров\n";
            cout << "0. Назад в меню клиента\n";
            cout << "Выберите действие: ";
            int skladOption = getChoiceFromUser();

            switch (skladOption) {
            case 1:
                klient.viewSklad(skladFile);
                break;
            case 2: {
                cout << "Введите ключевое слово для поиска: ";
                string keyword;
                cin.ignore();
                getline(cin, keyword);
                klient.searchSklad(skladFile, keyword);
                break;
            }
            case 0:
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
                break;
            }
            break;
        }
        case 2:
            klient.createOrder(ordersFile);
            break;
        case 3:
            klient.viewOrders(ordersFile);
            break;
        case 4:
            klient.editOrder(ordersFile);
            break;
        case 5:
            cout << "Возврат в главное меню...\n";
            return;
        case 0:
            cout << "Выход из программы...\n";
            exit(0);
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
            break;
        }
        system("pause");
    } while (option != 5);
}

void OperatorMenu(Operator& operatorObj, const string& skladFile, const string& ordersFile) {
    int option;
    do {
        system("cls");
        cout << "----- Меню Оператора -----\n";
        cout << "1. Проверка Склада\n";
        cout << "2. Поиск заказа по клиенту\n";
        cout << "3. Фильтрация заказов по статусу\n";
        cout << "4. Изменение статуса заказа\n";
        cout << "5. Расчет и добавление стоимости заказа\n";
        cout << "6. Выход в главное меню\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        option = getChoice();
        switch (option) {
        case 1:
            cout << "Просмотр склада:\n";
            operatorObj.viewSklad(skladFile);
            operatorObj.viewAllOrders(ordersFile);
            break;

        case 2: {
            string clientLogin;
            cout << "Введите логин клиента для поиска заказа: ";
            cin >> clientLogin;
            operatorObj.searchOrders(ordersFile, clientLogin);
            break;
        }

        case 3: {
            string status;
            cout << "Введите статус для фильтрации (например, 'Ожидается'): ";
            cin.ignore();
            getline(cin, status);
            operatorObj.filterOrdersByStatus(ordersFile, status);
            break;
        }

        case 4: {
            string clientLogin, newStatus;
            cout << "Введите логин клиента для изменения статуса: ";
            cin >> clientLogin;
            cout << "Введите новый статус: ";
            cin.ignore();
            getline(cin, newStatus);
            operatorObj.editOrderStatus(ordersFile, clientLogin, newStatus);
            break;
        }

        case 5: {
            string clientLogin;
            double ratePerUnit;
            cout << "Введите логин клиента для расчета стоимости: ";
            cin >> clientLogin;
            cout << "Введите ставку за единицу товара: ";
            cin >> ratePerUnit;
            operatorObj.calculateAndAddCost(ordersFile, clientLogin, ratePerUnit);
            break;
        }

        case 6:
            cout << "Возврат в главное меню...\n";
            return;
            break;

        case 0:
            cout << "Выход из программы...\n";
            exit(0);
            break;

        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
            break;
        }
        system("pause");
    } while (option != 8);
}

void ManagerMenu(Manager& manager) {
    int option;
    do {
        system("cls");
        cout << "----- Работа Менеджера -----\n";
        cout << "1. Добавить запись\n";
        cout << "2. Удалить запись\n";
        cout << "3. Просмотр файла\n";
        cout << "4. Поиск в файле\n";
        cout << "5. Сортировка файла\n";
        cout << "6. Выход в главное меню\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        option = getChoice();

        switch (option) {
        case 1: {
            cout << "Выберите файл для добавления записи:\n";
            cout << "1. Склад\n";
            cout << "2. Клиенты\n";
            cout << "3. Заказы\n";
            int fileChoice = getChoiceFromUser();

            if (fileChoice == 1) manager.addProductToSklad();
            else if (fileChoice == 2) manager.addClient();
            else if (fileChoice == 3) manager.addOrderRecord();
            else cout << "Неверный выбор файла.\n";
            break;
        }
        case 2: {
            cout << "Выберите файл для удаления записи:\n";
            cout << "1. Склад\n";
            cout << "2. Клиенты\n";
            cout << "3. Заказы\n";
            int fileChoice = getChoiceFromUser();

            cout << "Введите ключ записи для удаления: ";
            string key;
            cin.ignore();
            getline(cin, key);

            if (fileChoice == 1) manager.deleteSkladRecord(key);
            else if (fileChoice == 2) manager.deleteClientRecord(key);
            else if (fileChoice == 3) manager.deleteOrderRecord(key);
            else cout << "Неверный выбор файла.\n";
            break;
        }
        case 3: {
            cout << "Выберите файл для просмотра:\n";
            cout << "1. Склад\n";
            cout << "2. Клиенты\n";
            cout << "3. Заказы\n";
            int fileChoice = getChoiceFromUser();

            if (fileChoice == 1) manager.viewSklad();
            else if (fileChoice == 2) manager.viewClients();
            else if (fileChoice == 3) manager.viewOrders();
            else cout << "Неверный выбор файла.\n";
            break;
        }
        case 4: {
            cout << "Выберите файл для поиска:\n";
            cout << "1. Склад\n";
            cout << "2. Клиенты\n";
            cout << "3. Заказы\n";
            int fileChoice = getChoiceFromUser();

            cout << "Введите ключевое слово для поиска: ";
            string keyword;
            cin.ignore();
            getline(cin, keyword);

            if (fileChoice == 1) manager.searchInSklad(keyword);
            else if (fileChoice == 2) manager.searchInClients(keyword);
            else if (fileChoice == 3) manager.searchInOrders(keyword);
            else cout << "Неверный выбор файла.\n";
            break;
        }
        case 5: {
            cout << "Выберите файл для сортировки:\n";
            cout << "1. Склад\n";
            cout << "2. Клиенты\n";
            cout << "3. Заказы\n";
            int fileChoice = getChoiceFromUser();

            if (fileChoice == 1) manager.sortSklad();
            else if (fileChoice == 2) manager.sortClients();
            else if (fileChoice == 3) manager.sortOrders();
            else cout << "Неверный выбор файла.\n";
            break;
        }
        
        case 6:
            cout << "Возврат в главное меню...\n";
            return;
            break;
        case 0:
            cout << "Выход из программы...\n";
            exit(0);
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
        system("pause");
    } while (option != 7);
}

int main() {
    system("color F0");
    setlocale(LC_ALL, "russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Registration function;
    int choice;
    string ordersFile = "orders.txt";
    string skladFile = "sklad.txt";

    do {
        system("cls");
        cout << "----- Добро пожаловать -----\n";
        cout << "1. Вход в систему\n";
        cout << "2. Регистрация\n";
        cout << "3. Выход\n";
        cout << "Выберите действие: ";
        choice = getChoiceFromUser();

        switch (choice) {
        case 1: {
            function.EnterToProgram();
            if (function.userRoleId != -1) {
                Role currentRole = function.userRole;

                switch (currentRole) {
                case CLIENT: {
                    Klient klient(function.LoginUser, function.PasswordUser, skladFile);
                    cout << "Открытие меню клиента...\n";
                    ClientMenu(klient, ordersFile, skladFile);
                    break;
                }
                case OPER: {
                    Operator oper(function.LoginUser, function.PasswordUser);
                    cout << "Открытие меню оператора...\n";
                    OperatorMenu(oper, skladFile, ordersFile);
                    break;
                }
                case MANAGER: {
                    Manager manager(function.LoginUser, function.PasswordUser, currentRole, skladFile, "clients.txt", ordersFile);
                    cout << "Открытие меню менеджера...\n";
                    ManagerMenu(manager);
                    break;
                }
                default:
                    cout << "Ошибка: неизвестная роль.\n";
                    break;
                }
            }
            else {
                cout << "Ошибка авторизации\n";
            }
            break;  // Добавлен break
        }
        case 2: {
            function.Regist();
            if (function.userRoleId != -1) {
                Role currentRole = function.userRole;

                switch (currentRole) {
                case CLIENT: {
                    Klient klient(function.LoginUser, function.PasswordUser, skladFile);
                    cout << "Открытие меню клиента...\n";
                    ClientMenu(klient, ordersFile, skladFile);
                    break;
                }
                case OPER: {
                    Operator oper(function.LoginUser, function.PasswordUser);
                    cout << "Открытие меню оператора...\n";
                    OperatorMenu(oper, skladFile, ordersFile);
                    break;
                }
                case MANAGER: {
                    Manager manager(function.LoginUser, function.PasswordUser, currentRole, skladFile, "clients.txt", ordersFile);
                    cout << "Открытие меню менеджера...\n";
                    ManagerMenu(manager);
                    break;
                }
                default:
                    cout << "Ошибка: неизвестная роль.\n";
                    break;
                }
            }
            else {
                cout << "Ошибка регистрации\n";
            }
            break;  // Добавлен break
        }
        case 3: {
            cout << "Выход из программы...\n";
            break;
        }
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 3);
    return 0;
}