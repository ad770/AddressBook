#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <string>
#include <conio.h>

using namespace std;

struct User {
    int id;
    string login, password;
};

void getFileInfo() {
    fstream inputFile;
    inputFile.open("listaUzytkownikow.txt",ios::in);
    if(inputFile.good()==false) {
        cout << "Ups! Niezbedny plik nie istnieje!" << endl;
        Sleep(1000);
        cout <<"Ale nie przejmuj sie! Pracuje wlasnie nad jego utworzeniem..." << endl << endl;
        Sleep(1000);
        ofstream inputFile("listaUzytkownikow.txt");
        cout << "Pomyslnie utworzono nowy, pusty plik." << endl;
        cout << "Aby kontynuowac, nacisnij dowolny klawisz.";
        getchar();
        getchar();
    }
    inputFile.close();
}

int getDataFromFile(vector<User> &users) {
    User loginList;
    string line;
    int lineNumber=1;
    int contactsAmount=0;

    fstream inputFile;
    inputFile.open("listaUzytkownikow.txt",ios::in);
    if(inputFile.good()==true) {
        while(getline(inputFile,line,'|')) {
            switch(lineNumber) {
            case 1:
                loginList.id=(atoi(line.c_str()));
                break;
            case 2:
                loginList.login=(line);
                break;
            case 3:
                loginList.password=(line);
                break;
            }
            if (lineNumber==3) {
                lineNumber=0;
                contactsAmount++;
                contactList.push_back(person);
            }
            lineNumber++;
        }
    }
    inputFile.close();
    return contactsAmount;
}

int logging (vector <User> &users, int userAmounts) {
    int id;
    string login, password;
    cout << "Podaj nazwe: ";
    cin >> login;

    for (auto& iter: users) {
        if (iter.login == login) {
            for (int chanses=0; chanses<3; chanses++) {
                cout << "Podaj haslo. Pozostalo prob " << 3-chanses << ": ";
                cin >> password;
                if (iter.password == password) {
                    cout << "Zalogowales sie poprawnie!" << endl;
                    Sleep(1000);
                    return iter.id;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba" << endl;
            Sleep (3000);
            return 0;
            cout << "Nie ma takiego kontaktu w bazie!" << endl;
            cout << "Aby kontynuowac, nacisnij dowolny klawisz.";
            getchar();
            getchar();
            return userAmounts;
        }
    }
}

int registration (vector <User> &users, int userAmounts) {
    string login, password;
    User newUser;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> login;

    for (auto& iter: users) {
        while (iter.login == login) {
            cout << "Uzytkownik o takiej nazwie juz istnieje. Podaj inna nazwe uzytkownika: ";
        }
    }
    cout << "Podaj haslo: ";
    cin >> password;

    newUser.login=login;
    newUser.password=password;
    newUser.id=userAmounts+1;
    users.push_back(newUser);

    cout << "Konto zalozone poprawnie!";
    Sleep(1000);
    return newUser.id;
}


int main() {
    vector <User> users;
    int idLoggedUser=0;
    int usersAmount=getDataFromFile(users);

    char choose;

    while(1) {
        system ("cls");
        cout << "1. Logowanie" << endl;
        cout << "2. Rejestracja" << endl;
        cout << "9. Zamknij program" << endl;
        cin >> choose;
        switch(choose){
        case '1':
            idLoggedUser=logging(users,usersAmount);
            break;
        case '2':
            usersAmount=registration(users,usersAmount);
            break;
        case '9':
            exit(0);
            break;
        default:
            break;
        }
    }

    return 0;
}
