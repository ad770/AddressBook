#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <string>
#include <conio.h>

using namespace std;

void mainMenuLogin() {
    system("cls");
    cout << "    ---===KSIAZKA ADRESOWA===---    "  << endl;
    cout << "------------------------------------"  << endl;
    cout << "--1. Logowanie"                        << endl;
    cout << "--2. Rejestracja"                      << endl;
    cout << "------------------------------------"  << endl;
    cout << "--9. Zamknij program"                  << endl;
    cout << "------------------------------------"  << endl;
}

void mainMenuAddressBook() {
    system("cls");
    cout << "    ---===KSIAZKA ADRESOWA===---    "  << endl;
    cout << "------------------------------------"  << endl;
    cout << "--1.Dodaj adresata"                    << endl;
    cout << "--2.Wyszukaj po imieniu"               << endl;
    cout << "--3.Wyszukaj po nazwisku"              << endl;
    cout << "--4.Wyswietl wszystkich adresatow"     << endl;
    cout << "--5.Usun adresata"                     << endl;
    cout << "--6.Edytuj adresata"                   << endl;
    cout << "------------------------------------"  << endl;
    cout << "--7.Zmien haslo"                       << endl;
    cout << "--8.Wyloguj sie"                       << endl;
    cout << "------------------------------------"  << endl;
}

class User {
    int userId;
    string login, password;
    vector <User> users;

public:
    User(int userId=0, string login="", string password=""){
        this->userId = userId;
        this->login = login;
        this->password = password;
    };

    int getUserId(){
        return userId;
    }
    string getLogin(){
        return login;
    }
    string getPassword(){
        return password;
    }
    void setUserId(int newUserId){
        userId = newUserId;
    }
    void setLogin(string newLogin){
        login = newLogin;
    }
    void setPassword(string newPassword){
        password = newPassword;
    }

    vector <User> getDataFromLoginFile();
    void registration();
    void saveNewUserToFile();
    void changeUserPassword (int);
    int logging();
};

struct Contact {
    int contactId, userId;
    string firstName, lastName, phoneNumber, email, adress;
};

string getStringLine() {
    string inputLine = "";
    cin.sync();
    getline(cin, inputLine);
    return inputLine;
}

void getLoginFileInfo() {
    fstream inputFile;
    inputFile.open("Uzytkownicy.txt",ios::in);
    if(inputFile.good()==false) {
        cout << "Ups! Niezbedny plik nie istnieje!" << endl;
        Sleep(500);
        cout <<"Ale nie przejmuj sie! Pracuje wlasnie nad jego utworzeniem..." << endl << endl;
        Sleep(1000);
        ofstream inputFile("Uzytkownicy.txt");
        cout << "Pomyslnie utworzono nowy, pusty plik." << endl;
        cout << "Aby kontynuowac, nacisnij dowolny klawisz.";
        getchar();
        getchar();
    }
    inputFile.close();
}

void getAddressBookFileInfo() {
    fstream inputFile;
    inputFile.open("Adresaci.txt",ios::in);
    if(inputFile.good()==false) {
        cout << "Ups! Niezbedny plik nie istnieje!" << endl;
        Sleep(500);
        cout <<"Ale nie przejmuj sie! Pracuje wlasnie nad jego utworzeniem..." << endl << endl;
        Sleep(1000);
        ofstream inputFile("Adresaci.txt");
        cout << "Pomyslnie utworzono nowy, pusty plik." << endl;
        cout << "Aby kontynuowac, nacisnij dowolny klawisz.";
        getchar();
        getchar();
    }
    inputFile.close();
}

vector <User> User::getDataFromLoginFile() {
    User getUsers;
    string line;
    int lineNumber=1;
    int usersAmount=0;

    fstream inputFile;
    inputFile.open("Uzytkownicy.txt",ios::in);
    if(inputFile.good()==true) {
        while(getline(inputFile,line,'|')) {
            switch(lineNumber) {
            case 1:
                getUsers.userId=(atoi(line.c_str()));
                break;
            case 2:
                getUsers.login=(line);
                break;
            case 3:
                getUsers.password=(line);
                break;
            }
            if (lineNumber==3) {
                lineNumber=0;
                usersAmount++;
                users.push_back(getUsers);
            }
            lineNumber++;
        }
    }
    inputFile.close();
    return users;
}

void getDataFromAddressBookFileForLoggedInUser(vector<Contact> &loggedInUserContactList, int userId) {
    Contact person;
    string line;
    int lineNumber=1;
    int contactsAmount=0;

    fstream inputFile;
    inputFile.open("Adresaci.txt",ios::in);
    if(inputFile.good()==true) {
        while(getline(inputFile,line,'|')) {
            switch(lineNumber) {
            case 1:
                person.contactId=(atoi(line.c_str()));
                break;
            case 2:
                person.userId=(atoi(line.c_str()));
                break;
            case 3:
                person.firstName=(line);
                break;
            case 4:
                person.lastName=(line);
                break;
            case 5:
                person.phoneNumber=(line);
                break;
            case 6:
                person.email=(line);
                break;
            case 7:
                person.adress=(line);
                break;
            }
            if (lineNumber==7) {
                contactsAmount++;
                lineNumber=0;
                if (person.userId == userId) {
                    loggedInUserContactList.push_back(person);
                }
            }
            lineNumber++;
        }
    }
    inputFile.close();
}

void getWholeDataFromAddressBookFile(vector<Contact> &wholeContactList) {
    Contact tempContactList;
    string line;
    int lineNumber=1;
    int contactsAmount=0;

    fstream inputFile;
    inputFile.open("Adresaci.txt",ios::in);
    if(inputFile.good()==true) {
        while(getline(inputFile,line,'|')) {
            switch(lineNumber) {
            case 1:
                tempContactList.contactId=(atoi(line.c_str()));
                break;
            case 2:
                tempContactList.userId=(atoi(line.c_str()));
                break;
            case 3:
                tempContactList.firstName=(line);
                break;
            case 4:
                tempContactList.lastName=(line);
                break;
            case 5:
                tempContactList.phoneNumber=(line);
                break;
            case 6:
                tempContactList.email=(line);
                break;
            case 7:
                tempContactList.adress=(line);
                break;
            }
            if (lineNumber==7) {
                contactsAmount++;
                lineNumber=0;
                wholeContactList.push_back(tempContactList);
            }
            lineNumber++;
        }
    }
    inputFile.close();
}

void fixFiles () {
    remove ("Adresaci.txt");
    rename("Adresaci_temp.txt","Adresaci.txt");
}

int User::logging () {
    int id=0;
    string login, password;
    cout << "Podaj nazwe: ";
    cin >> login;

    auto iter=find_if(users.begin(), users.end(),
    [&](User const & users) {
        return (users.login==login);
    });

    if (iter==users.end()) {
        cout << "Nie ma takiego kontaktu w bazie!" << endl;
        Sleep(1000);
        return id;
    } else {
        for (int chances=0; chances<3; chances++) {
            cout << "Podaj haslo. Pozostalo prob " << 3-chances << ": ";
            cin >> password;
            if (iter->password==password) {
                cout << "Zalogowales sie poprawnie!" << endl;
                Sleep(1000);
                return iter->userId;
            }
        }
        cout << "Podales 3 razy bledne haslo. Za chwile wrocisz do Menu logowania";
        Sleep (700);
        cout << ".";
        Sleep (700);
        cout << ".";
        Sleep (700);
        cout << ".";
        return id;
    }
}

void User::saveNewUserToFile() {
    fstream outputFile;
    outputFile.open("Uzytkownicy.txt",ios::out | ios::app);

    if (outputFile.good()==true) {
        outputFile << users[users.size()-1].userId << '|';
        outputFile << users[users.size()-1].login << '|';
        outputFile << users[users.size()-1].password << '|' << endl;

        cout << "Poprawnie dodano nowy kontakt.";
        Sleep(1000);
    } else {
        cout << "Wystapil problem z plikiem. Blad zapisu danych.";
        getchar();
        getchar();
    }
    outputFile.close();
}

void User::registration () {
    User saveNewUser;

    int newUserId=users.size()+1;
    string login, password;

        cout << "Podaj nazwe uzytkownika: ";
        cin >> login;

        auto iter = find_if(users.begin(), users.end(),
        [&](User const & users) {
            return users.login==login;
        });
        if (iter==users.end()) {
            cout << "Podaj haslo: ";
            cin >> password;

            saveNewUser.login=login;
            saveNewUser.password=password;
            saveNewUser.userId=newUserId;
            users.push_back(saveNewUser);
            User::saveNewUserToFile();
        } else {
            cout << "Uzytkownik o takiej nazwie juz istnieje.\n\nNacisnij dowolny klawisz aby wrocic do glownego menu.\n";
            getchar();
            getchar();
            newUserId=0;
        }
}

void User::changeUserPassword (int userId) {
    string oldPassword, newPassword;

    cout << "Podaj stare haslo: ";
    cin >> oldPassword;

    if (users[userId-1].password==oldPassword) {
        cout << "Podaj nowe haslo: ";
        cin >> newPassword;
        users[userId-1].password=newPassword;

    fstream inputFile;
    inputFile.open("Uzytkownicy.txt",ios::out);
    if (inputFile.good()==true) {
        for (auto it: users) {
            inputFile << it.userId << "|" << it.login << "|" << it.password << "|" << endl;
        }
    }
    inputFile.close();
    cout << "Haslo zostalo pomyslnie zmienione" << endl;
    Sleep(1000);
    return;
    }
    else {
        cout << "Podano nieprawidlowe haslo.";
    }
}

void saveNewContactToFile (vector<Contact> &loggedInUserContactList) {
    fstream outputFile;
    outputFile.open("Adresaci.txt",ios::out | ios::app);

    if (outputFile.good()==true) {
        outputFile << loggedInUserContactList[loggedInUserContactList.size()-1].contactId << '|';
        outputFile << loggedInUserContactList[loggedInUserContactList.size()-1].userId << '|';
        outputFile << loggedInUserContactList[loggedInUserContactList.size()-1].firstName << '|';
        outputFile << loggedInUserContactList[loggedInUserContactList.size()-1].lastName << '|';
        outputFile << loggedInUserContactList[loggedInUserContactList.size()-1].phoneNumber << '|';
        outputFile << loggedInUserContactList[loggedInUserContactList.size()-1].email << '|';
        outputFile << loggedInUserContactList[loggedInUserContactList.size()-1].adress << '|' << endl;

        cout << "Poprawnie dodano nowy kontakt.";
        Sleep(1000);
    } else {
        cout << "Wystapil problem z plikiem. Blad zapisu danych.";
        getchar();
        getchar();
    }
    outputFile.close();
}

int addNewContact(vector<Contact> &loggedInUserContactList, int userId) {
    system("cls");
    getAddressBookFileInfo();
    system("cls");
    vector <Contact> wholeContactList;
    int nextId;
    getWholeDataFromAddressBookFile(wholeContactList);

    if (wholeContactList.size()!=0) {
        nextId=wholeContactList.back().contactId+1;
    } else {
        nextId=1;
    }
    string firstName, lastName, phoneNumber, email, adress;
    Contact person;

    cout << "Id nowego kontaktu = " << nextId << endl;
    cout << "Podaj imie: ";
    firstName = getStringLine();
    cout << "Podaj nazwisko: ";
    lastName = getStringLine();
    cout << "Podaj numer telefonu: ";
    phoneNumber = getStringLine();
    cout << "Podaj adres email: ";
    email = getStringLine();
    cout << "Podaj adres zamieszkania: ";
    adress = getStringLine();

    person.contactId=(nextId);  // sprobowac zamiast nowej struktury person -> loggedInUserContactList.push_back(Contact(nextId, userId, firstName, lastName, phoneNumber, email, address));
    person.userId=(userId);
    person.firstName=(firstName);
    person.lastName=(lastName);
    person.phoneNumber=(phoneNumber);
    person.email=(email);
    person.adress=(adress);
    loggedInUserContactList.push_back(person);

    saveNewContactToFile(loggedInUserContactList);
}

void showContacts (vector<Contact> &loggedInUserContactList) {
    system("cls");

    for (auto& iter: loggedInUserContactList) {
        cout << "Id: \t\t\t"                << iter.contactId << endl;
        cout << "Imie: \t\t\t"              << iter.firstName << endl;
        cout << "Nazwisko: \t\t"            << iter.lastName << endl;
        cout << "Nr telefonu: \t\t"         << iter.phoneNumber << endl;
        cout << "Adres email: \t\t"         << iter.email << endl;
        cout << "Adres zamieszkania: \t"    << iter.adress << endl << endl;
    }
    cout << "Wcisnij klawisz, jesli chcesz wrocic do glownego menu.";
    getchar();
    getchar();
}

void searchByFirstName (vector<Contact> &loggedInUserContactList) {
    string firstName;
    int itemsFound=0;

    system("cls");
    cout << "Podaj imie, ktorego szukasz: ";
    firstName = getStringLine();

    for (auto& iter: loggedInUserContactList) {
        if (iter.firstName==firstName) {
            cout << "Id: \t\t\t"                << iter.contactId << endl;
            cout << "Imie: \t\t\t"              << iter.firstName << endl;
            cout << "Nazwisko: \t\t"            << iter.lastName << endl;
            cout << "Nr telefonu: \t\t"         << iter.phoneNumber << endl;
            cout << "Adres email: \t\t"         << iter.email << endl;
            cout << "Adres zamieszkania: \t"    << iter.adress << endl << endl;
            itemsFound++;
        }
    }
    if (itemsFound==0) {
        cout << "Niestety, nie posiadasz w kontaktach nikogo o imieniu: " << firstName << endl << endl;
    }
    cout << "Aby kontynuowac, nacisnij dowolny klawisz.";
    getchar();
}

void searchByLastName (vector<Contact> &loggedInUserContactList) {
    string lastName;
    int itemsFound=0;

    system("cls");
    cout << "Podaj nazwisko, ktorego szukasz: ";
    lastName = getStringLine();

    for (auto& iter: loggedInUserContactList) {
        if (iter.lastName==lastName) {
            cout << "Id: \t\t\t"                << iter.contactId << endl;
            cout << "Imie: \t\t\t"              << iter.firstName << endl;
            cout << "Nazwisko: \t\t"            << iter.lastName << endl;
            cout << "Nr telefonu: \t\t"         << iter.phoneNumber << endl;
            cout << "Adres email: \t\t"         << iter.email << endl;
            cout << "Adres zamieszkania: \t"    << iter.adress << endl << endl;
            itemsFound++;
        }
    }
    if (itemsFound==0) {
        cout << "Niestety, nie posiadasz w kontaktach nikogo o nazwisku: " << lastName << endl << endl;;
    }
    cout << "Aby kontynuowac, nacisnij dowolny klawisz.";
    getchar();
}

void removeContact (vector<Contact> &loggedInUserContactList) {
    vector <Contact> wholeContactList;
    int id;
    cout << "Podaj numer indeksu do usuniecia: ";
    cin >> id;

    auto iter = find_if(loggedInUserContactList.begin(), loggedInUserContactList.end(),
    [&](Contact const & loggedInUserContactList) {
        return loggedInUserContactList.contactId == id;
    });

    if (iter == loggedInUserContactList.end()) {
        cout << "Nie ma takiego kontaktu w bazie!" << endl;
        cout << "Aby kontynuowac, nacisnij dowolny klawisz.";
        getchar();
        getchar();
    } else {
        cout << "Aby potwierdzic usuniecie kontaktu o indeksie = " << id << ", nacisnij t" << endl;
        cin.sync();
        if (getch()=='t') {
            loggedInUserContactList.erase(
                remove_if(loggedInUserContactList.begin(), loggedInUserContactList.end(),
            [&](Contact const & loggedInUserContactList) {
                return loggedInUserContactList.contactId == id;
            }),
            loggedInUserContactList.end());
            cout << "Kontakt zostal pomyslnie usuniety" << endl;
            Sleep(1000);

            fstream inputFile;
            inputFile.open("Adresaci.txt",ios::in);
            if(inputFile.good()==true) {
                getWholeDataFromAddressBookFile(wholeContactList);
            }
            inputFile.close();

            ofstream outputFile;
            outputFile.open("Adresaci_temp.txt",ios::out);

            if (outputFile.good()==true) {
                for (auto it: wholeContactList) {
                    if (it.contactId!=id) {
                        outputFile << it.contactId << "|" << it.userId << "|" << it.firstName << "|" << it.lastName << "|" << it.phoneNumber << "|" << it.email << "|" << it.adress << "|" << endl;
                    }
                }
            }
            outputFile.close();
            fixFiles();
        } else system("pause");
    }
}

void editContact (vector<Contact> &loggedInUserContactList) {
    vector <Contact> wholeContactList;
    int id;
    string newFirstName, newLastName, newPhoneNumber, newEmail, newAdress;

    cout << "Podaj numer indesku osoby, ktorej dane chcesz edytowac: ";
    cin >> id;

    auto iter = find_if(loggedInUserContactList.begin(), loggedInUserContactList.end(),
    [&](Contact const & loggedInUserContactList) {
        return loggedInUserContactList.contactId == id;
    });

    if (iter == loggedInUserContactList.end()) {
        cout << "Nie ma takiego kontaktu w bazie!" << endl;
        cout << "Aby kontynuowac, nacisnij dowolny klawisz.";
        getchar();getchar();
        return;
    }

    char chooseMenu;
    while(true) {
        system("cls");
        cout << "Wybierz pole, ktore chcesz edytowac:" << endl;
        cout << "1.Imie\t\t\t"              << iter->firstName << endl;
        cout << "2.Nazwisko\t\t"            << iter->lastName << endl;
        cout << "3.Numer telefonu\t"        << iter->phoneNumber << endl;
        cout << "4.Email\t\t\t"             << iter->email << endl;
        cout << "5.Adres\t\t\t"             << iter->adress << endl;
        cout << "6.Wroc do glownego menu"   << endl;
        cin >> chooseMenu;
        switch(chooseMenu) {
        case '1':
            cout << "Podaj nowe imie: ";
            newFirstName=getStringLine();
            iter->firstName=newFirstName;
            break;
        case '2':
            cout << "Podaj nowe nazwisko: ";
            newLastName=getStringLine();
            iter->lastName=newLastName;
            break;
        case '3':
            cout << "Podaj nowy numer telefonu: ";
            newPhoneNumber=getStringLine();
            iter->phoneNumber=newPhoneNumber;
            break;
        case '4':
            cout << "Podaj nowy adres email: ";
            newEmail=getStringLine();
            iter->email=newEmail;
            break;
        case '5':
            cout << "Podaj nowy adres zamieszkania: ";
            newAdress=getStringLine();
            iter->adress=newAdress;
            break;
        case '6':
            return;
        default:
            break;
        }

        fstream inputFile;
        inputFile.open("Adresaci.txt",ios::in);
        if(inputFile.good()==true) {
            getWholeDataFromAddressBookFile(wholeContactList);
        }
        inputFile.close();

        ofstream outputFile;
        outputFile.open("Adresaci_temp.txt",ios::out);

        if (outputFile.good()==true) {
            for (auto it: wholeContactList) {
                if (it.contactId!=id) {
                    outputFile << it.contactId << "|" << it.userId << "|" << it.firstName << "|" << it.lastName << "|" << it.phoneNumber << "|" << it.email << "|" << it.adress << "|" << endl;
                } else {
                    outputFile << iter->contactId << "|" << iter->userId << "|" << iter->firstName << "|" << iter->lastName << "|" << iter->phoneNumber << "|" << iter->email << "|" << iter->adress << "|" << endl;
                }
            }
        }

        outputFile.close();

        fixFiles();
        cout << "Kontakt zostal pomyslnie zaktualizowany" << endl;
        Sleep(1000);
        return;
    }
}

int main() {
    User user;
    user.getDataFromLoginFile();
    char chooseLoginMenu;
    int userId=0;

    while(true) {
        mainMenuLogin();
        cin >> chooseLoginMenu;
        switch(chooseLoginMenu) {
        case '1':
            userId=user.logging();
            if(userId!=0) {
                vector <Contact> loggedInUserContactList;
                getDataFromAddressBookFileForLoggedInUser(loggedInUserContactList, userId);
                char chooseAddressBookMenu;
                bool flag=true;
                do {
                    mainMenuAddressBook();
                    cin >> chooseAddressBookMenu;
                    switch(chooseAddressBookMenu) {
                    case '1':
                        addNewContact(loggedInUserContactList, userId);
                        break;
                    case '2':
                        searchByFirstName(loggedInUserContactList);
                        break;
                    case '3':
                        searchByLastName(loggedInUserContactList);
                        break;
                    case '4':
                        showContacts(loggedInUserContactList);
                        break;
                    case '5':
                        removeContact(loggedInUserContactList);
                        break;
                    case '6':
                        editContact(loggedInUserContactList);
                        break;
                    case '7':
                        user.changeUserPassword(userId);
                        break;
                    case '8':
                        flag=false;
                        break;
                    default:
                        break;
                    }
                } while(flag==true);
                break;
            } else
                break;
        case '2':
            user.registration();
            break;
        case '9':
            return 0;
        default:
            break;
        }
    }
    return 0;
}
