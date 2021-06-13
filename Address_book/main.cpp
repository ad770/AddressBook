#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <string>
#include <conio.h>

using namespace std;

void mainMenu() {
    system("cls");
    cout << "KSIAZKA ADRESOWA"                  << endl;
    cout << "1.Dodaj adresata"                  << endl;
    cout << "2.Wyszukaj po imieniu"             << endl;
    cout << "3.Wyszukaj po nazwisku"            << endl;
    cout << "4.Wyswietl wszystkich adresatow"   << endl;
    cout << "5.Usun adresata"                   << endl;
    cout << "6.Edytuj adresata"                 << endl;
    cout << "9.Zakoncz program"                 << endl;
}

struct Contact {
    int id;
    string firstName, lastName, phoneNumber, email, adress;
};

string getStringLine() {
    string inputLine = "";
    cin.sync();
    getline(cin, inputLine);
    return inputLine;
}

void getFileInfo() {
    fstream inputFile;
    inputFile.open("ksiazkaAdresowa.txt",ios::in);
    if(inputFile.good()==false) {
        cout << "Ups! Niezbedny plik nie istnieje!" << endl;
        Sleep(1000);
        cout <<"Ale nie przejmuj sie! Pracuje wlasnie nad jego utworzeniem..." << endl << endl;
        Sleep(1000);
        ofstream inputFile("ksiazkaAdresowa.txt");
        cout << "Pomyslnie utworzono nowy, pusty plik." << endl;
        cout << "Aby kontynuowac, nacisnij dowolny klawisz.";
        getchar();
        getchar();
    }
    inputFile.close();
}

int getDataFromFile(vector<Contact> &contactList) {
    Contact person;
    string line;
    int lineNumber=1;
    int contactsAmount=0;

    fstream inputFile;
    inputFile.open("ksiazkaAdresowa.txt",ios::in);
    if(inputFile.good()==true) {
        while(getline(inputFile,line,'|')) {
            switch(lineNumber) {
            case 1:
                person.id=(atoi(line.c_str()));
                break;
            case 2:
                person.firstName=(line);
                break;
            case 3:
                person.lastName=(line);
                break;
            case 4:
                person.phoneNumber=(line);
                break;
            case 5:
                person.email=(line);
                break;
            case 6:
                person.adress=(line);
                break;
            }
            if (lineNumber==6) {
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

int addNewContact(vector<Contact> &contactList, int contactsAmount) {
    system("cls");
    getFileInfo();
    system("cls");

    int nextId;
    string firstName, lastName, phoneNumber, email, adress;
    Contact person;

    if (contactsAmount==0) {
        nextId=1;
    } else {
        nextId=contactList[contactsAmount-1].id+1;
    }

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

    person.id=(nextId);
    person.firstName=(firstName);
    person.lastName=(lastName);
    person.phoneNumber=(phoneNumber);
    person.email=(email);
    person.adress=(adress);

    contactList.push_back(person);

    fstream inputFile;
    inputFile.open("ksiazkaAdresowa.txt",ios::out | ios::app);

    if (inputFile.good()==true) {
        inputFile << contactList[contactsAmount].id << '|';
        inputFile << contactList[contactsAmount].firstName << '|';
        inputFile << contactList[contactsAmount].lastName << '|';
        inputFile << contactList[contactsAmount].phoneNumber << '|';
        inputFile << contactList[contactsAmount].email << '|';
        inputFile << contactList[contactsAmount].adress << '|' << endl;

        cout << "Poprawnie dodano nowy kontakt.";
        Sleep(1000);
    } else {
        cout << "Wystapil problem z plikiem. Blad zapisu danych.";
        getchar();
        getchar();
    }
    inputFile.close();
    return contactsAmount+1;
}

void showContacts (vector<Contact> &contactList) {
    system("cls");
    for (auto& iter: contactList) {
        cout << "Id: \t\t\t"                << iter.id << endl;
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

void searchByFirstName (vector<Contact> &contactList) {
    string firstName;
    int itemsFound=0;

    system("cls");
    cout << "Podaj imie, ktorego szukasz: ";
    firstName = getStringLine();

    for (auto& iter: contactList) {
        if (iter.firstName==firstName) {
            cout << "Id: \t\t\t"                << iter.id << endl;
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

void searchByLastName (vector<Contact> &contactList) {
    string lastName;
    int itemsFound=0;

    system("cls");
    cout << "Podaj nazwisko, ktorego szukasz: ";
    lastName = getStringLine();

    for (auto& iter: contactList) {
        if (iter.lastName==lastName) {
            cout << "Id: \t\t\t"                << iter.id << endl;
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

int removeContact (vector<Contact> &contactList, int contactsAmount) {
    int id;
    cout << "Podaj numer indeksu do usuniecia: ";
    cin >> id;

    auto iter = find_if(contactList.begin(), contactList.end(),
    [&](Contact const & contactList) {
        return contactList.id == id;
    });

    if (iter == contactList.end()) {
        cout << "Nie ma takiego kontaktu w bazie!" << endl;
        cout << "Aby kontynuowac, nacisnij dowolny klawisz.";
        getchar();
        getchar();
        return contactsAmount;
    }

    cout << "Aby potwierdzic usuniecie kontaktu o indeksie = " << id << ", nacisnij t" << endl;
    cin.sync();
    if (getch()=='t') {
        contactList.erase(
            remove_if(contactList.begin(), contactList.end(),
                [&](Contact const & contactList) {
            return contactList.id == id;
        }),
        contactList.end());
        cout << "Kontakt zostal pomyslnie usuniety" << endl;
        Sleep(1000);

        fstream inputFile;
        inputFile.open("ksiazkaAdresowa.txt",ios::out);

        if (inputFile.good()==true) {
            for (auto it: contactList) {
                inputFile << it.id << "|" << it.firstName << "|" << it.lastName << "|" << it.phoneNumber << "|" << it.email << "|" << it.adress << "|" << endl;
            }
        }
        inputFile.close();
    } else system("pause");
    return contactsAmount-1;
}

void editContact (vector<Contact> &contactList) {
    int id;
    string newFirstName, newLastName, newPhoneNumber, newEmail, newAdress;
    Contact person;

    cout << "Podaj numer indesku osoby, ktorej dane chcesz edytowac: ";
    cin >> id;

    auto iter = find_if(contactList.begin(), contactList.end(),
    [&](Contact const & contactList) {
        return contactList.id == id;
    });

    if (iter == contactList.end()) {
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
            cout << "Podaj imie: ";
            newFirstName=getStringLine();
            person.firstName=(newFirstName);
            iter->firstName=newFirstName;
            break;
        case '2':
            cout << "Podaj nazwisko: ";
            newLastName=getStringLine();
            person.lastName=(newLastName);
            iter->lastName=newLastName;
            break;
        case '3':
            cout << "Podaj numer telefonu: ";
            newPhoneNumber=getStringLine();
            person.phoneNumber=(newPhoneNumber);
            iter->phoneNumber=newPhoneNumber;
            break;
        case '4':
            cout << "Podaj adres email: ";
            newEmail=getStringLine();
            person.email=(newEmail);
            iter->email=newEmail;
            break;
        case '5':
            cout << "Podaj adres zamieszkania: ";
            newAdress=getStringLine();
            person.adress=(newAdress);
            iter->adress=newAdress;
            break;
        case '6':
            return;
        default:
            break;
        }
        fstream inputFile;
        inputFile.open("ksiazkaAdresowa.txt",ios::out);

        if (inputFile.good()==true) {
            for (auto it: contactList) {
                inputFile << it.id << "|" << it.firstName << "|" << it.lastName << "|" << it.phoneNumber << "|" << it.email << "|" << it.adress << "|" << endl;
            }
        }
        inputFile.close();
        cout << "Kontakt zostal pomyslnie zaktualizowany" << endl;
        Sleep(1000);
        return;
    }
}

int main() {
    vector <Contact> contactList;
    int contactsAmount=getDataFromFile(contactList);

    char chooseMenu;
    while(true) {
        mainMenu();
        cin >> chooseMenu;
        switch(chooseMenu) {
        case '1':
            contactsAmount=addNewContact(contactList, contactsAmount);
            break;
        case '2':
            searchByFirstName(contactList);
            break;
        case '3':
            searchByLastName(contactList);
            break;
        case '4':
            showContacts(contactList);
            break;
        case '5':
            contactsAmount=removeContact(contactList, contactsAmount);
            break;
        case '6':
            editContact(contactList);
            break;
        case '9':
            exit(0);
        default:
            break;
        }
    }
    return 0;
}
