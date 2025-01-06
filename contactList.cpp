#include <iostream>
#include <cstring>
#include <cctype>
#include <iomanip>
#include <fstream>
#include <string>
#include "contactList.h"
using namespace std;

ContactList::Node::Node() {
    strcpy_s(name, "\0");
    for (int x = 0; x < 5; x++) {
        phone[x][0] = '\0';
    }
    strcpy_s(email, "\0");
    strcpy_s(ringtone, "\0");
    strcpy_s(birthday, "\0");

    prev = link = NULL;
}

ContactList::ContactList() {
    index = 0;
    noItem = 0;
    pCurr = pHead = pTail = NULL;
}

ContactList::~ContactList() {}

void ContactList::insertContactFromFile() {

    ifstream contactFile;
    contactFile.open("contactFile.txt");
    char line[100] = "\0";
    char getContactLine[100][100] = { "\0" };

    if (!contactFile) {
        cout << "Contact file falied to open!" << endl;
        return;
    }

    int x = 0;
    while (contactFile.getline(line, 100)) {
        strcpy_s(getContactLine[x], line);
        x++;
    }

    contactFile.close();

    for (int i = x - 1; i >= 0; i -= 6) {

        Node* pNew = new Node;
        pNew->link = NULL;
        pNew->prev = NULL;

        strcpy_s(pNew->birthday, getContactLine[i]);

        strcpy_s(pNew->ringtone, getContactLine[i - 1]);
        strcpy_s(pNew->email, getContactLine[i - 2]);

        int lengthPhone = strlen(getContactLine[i - 3]);
        int numPhone = lengthPhone / 12;
        int z = 0; // z used to get characters (phone) one by one from file
        for (int a = 0; a <= numPhone; a++) {
            int phoneIndex = 0;

            for (int y = z; y < lengthPhone; y++, phoneIndex++) {
                if (getContactLine[i - 3][y] != ' ') {
                    pNew->phone[a][phoneIndex] = getContactLine[i - 3][y];
                }
                else {
                    break;
                }
                z++;
            }
            z++; // z + 1 again to avoid ' '
        }

        strcpy_s(pNew->name, getContactLine[i - 4]);

        if (noItem == 0) {
            pTail = pNew;
        }
        else if (noItem != 0) {
            pCurr->prev = pNew;
            pNew->link = pCurr;
        }

        noItem++;

        pHead = pNew;
        pCurr = pNew;

    }

}

void ContactList::insertContact(char name[], char phone[][12], char email[], char ringtone[], char birthday[]) {

    Node* pNew = new Node;
    pNew->link = NULL;
    pNew->prev = NULL;

    strcpy_s(pNew->name, name);
    for (int x = 0; x < 5; x++) {
        if (phone[x][0] != '\0')
        strcpy_s(pNew->phone[x], phone[x]);
    }
    strcpy_s(pNew->email, email);
    strcpy_s(pNew->ringtone, ringtone);
    strcpy_s(pNew->birthday, birthday);
    pNew->link = NULL;

    // link to the next
    if (noItem == 0) {
        pHead = pNew;
    }
    else {
        pNew->prev = pTail;
        pTail->link = pNew;
    }

    noItem++;

    cout << "\nNew Contact " << pNew->name << " Inserted Successfully!";

    pTail = pNew;

}


void ContactList::deleteContact(char contactDelete[]) {

    int indexLocation = 0;
    Node* pTemp = pHead;

    if (traverse(indexLocation, contactDelete) == true) {

        if (indexLocation == 0) {
            pTemp = pHead;
            pHead = pHead->link;
            cout << endl << pTemp->name << " Delete Successfully!" << endl;
            delete pTemp;
            noItem--;
            return;
        }
        else if (indexLocation == noItem - 1) {
            pTemp = pTail;
            pTail = pTail->prev;
            pTail->link = NULL;
            cout << endl << pTemp->name << " Delete Successfully!" << endl;
            delete pTemp;
            noItem--;
            return;
        }
        else {

            for (int x = 0; x < indexLocation && pTemp->link != NULL; x++) {
                pCurr = pTemp;
                pTemp = pTemp->link;
            }

            if (strcmp(pTemp->name, contactDelete) == 0) {
                pCurr->link = pTemp->link;
                cout << endl << pTemp->name << " Delete Successfully!" << endl;
                delete pTemp;
                noItem--;
                return;
            }
            else if (strcmp(pTemp->phone[0], contactDelete) == 0) {
                pCurr->link = pTemp->link;
                cout << endl << pTemp->name << " Delete Successfully!" << endl;
                delete pTemp;
                noItem--;
                return;
            }
            else if (strcmp(pTemp->email, contactDelete) == 0) {
                pCurr->link = pTemp->link;
                cout << endl << pTemp->name << " Delete Successfully!" << endl;
                delete pTemp;
                noItem--;
                return;
            }
        }

    }
    else {
        cout << "\nUnable to delete because contact not found" << endl;
    }

    return;

}

void ContactList::updateContact(char type[], char targetContact[], char contactUpdate[]) {

    _strlwr_s(type, 20);
    int indexLocation = 0;
    Node* pTemp = new Node;
    pCurr = pHead;

    if (traverse(indexLocation, targetContact) == true) {

        if (indexLocation == noItem - 1) {
            pCurr = pTail;
        }
        else if (indexLocation != 0){

            for (int x = 0; x < indexLocation - 2 && pCurr->link != NULL; x++) {
                pCurr = pCurr->link;
            }

        }

        if (strcmp(type, "name") == 0) {
            strcpy_s(pTemp->name, pCurr->name);
			strcpy_s(pCurr->name, contactUpdate);
            type[0] = toupper(type[0]);
            cout << endl << "Update succesfully!" << endl;
            cout << type << " has update from " << pTemp->name << " to " << pCurr->name << endl;
		}
		else if (strcmp(type, "phone") == 0) {
            strcpy_s(pTemp->phone[0], pCurr->phone[0]);
			strcpy_s(pCurr->phone[0], contactUpdate);
            cout << endl << "Update succesfully!" << endl;
            cout << type << " has update from " << pTemp->phone[0] << " to " << pCurr->phone[0] << endl;
		}
		else if (strcmp(type, "email") == 0) {
            strcpy_s(pTemp->email, pCurr->email);
			strcpy_s(pCurr->email, contactUpdate);
            cout << endl << "Update succesfully!" << endl;
            cout << type << " has update from " << pTemp->email << " to " << pCurr->email << endl;
		}
		else if (strcmp(type, "ringtone") == 0) {
            strcpy_s(pTemp->ringtone, pCurr->ringtone);
			strcpy_s(pCurr->ringtone, contactUpdate);
            cout << endl << "Update succesfully!" << endl;
            cout << type << " has update from " << pTemp->ringtone << " to " << pCurr->ringtone << endl;
		}
        else if (strcmp(type, "birthday") == 0) {
            strcpy_s(pTemp->birthday, pCurr->birthday);
            strcpy_s(pCurr->birthday, contactUpdate);
            cout << endl << "Update succesfully!" << endl;
            cout << type << " has update from " << pTemp->birthday << " to " << pCurr->birthday << endl;
        }

        delete pTemp;

    }
    else {
        cout << "\nUnable to update because contact not found" << endl;
    }

    return;

}

bool ContactList::traverse(int& indexLocation, char contactSearch[]) {

    indexLocation = 0;
    pCurr = pHead;
    while (strcmp(pCurr->name, contactSearch) != 0 && pCurr->link != NULL) {
        pCurr = pCurr->link;
        indexLocation++;
    }

    if (strcmp(pCurr->name, contactSearch) == 0) {
        return true;
    }

    indexLocation = 0;
    pCurr = pHead;
    while (strcmp(pCurr->phone[0], contactSearch) != 0 && pCurr->link != NULL) {
        pCurr = pCurr->link;
        indexLocation++;
    }

    if (strcmp(pCurr->phone[0], contactSearch) == 0) {
        return true;
    }

    indexLocation = 0;
    pCurr = pHead;
    while (strcmp(pCurr->email, contactSearch) != 0 && pCurr->link != NULL) {
        pCurr = pCurr->link;
        indexLocation++;
    }

    if (strcmp(pCurr->email, contactSearch) == 0) {
        return true;
    }

    return false;

}

void ContactList::bubbleSort() {

}

void ContactList::displayContactList() {

    pCurr = pHead;

    cout << setw(120) << setfill('-') << left << "-" << endl;
    cout << setw(5) << setfill(' ') << "No";
    cout << setw(20) << setfill(' ') << "Name";
    cout << setw(25) << setfill(' ') << "Email";
    cout << setw(15) << setfill(' ') << "Ringtone";
    cout << setw(15) << setfill(' ') << "Birthday";
    cout << setw(30) << setfill(' ') << "Phone" << endl;
    cout << setw(120) << setfill('-') << "-" << endl << endl;

    for (int x = 0; x < noItem; x++) {
        cout << setw(5) << setfill(' ') << x + 1;
        cout << setw(20) << setfill(' ') << pCurr->name;
        cout << setw(25) << setfill(' ') << pCurr->email;
        cout << setw(15) << setfill(' ') << pCurr->ringtone;
        cout << setw(15) << setfill(' ') << pCurr->birthday;
        for (int i = 0; i < 5; i++) {
            if (pCurr->phone[i][0] != '\0') {
                cout << setw(12) << setfill(' ') << pCurr->phone[i] << " ";
            }
            else {
                break;
            }
        }
        if (pCurr->link != NULL) {
            pCurr = pCurr->link;
        }
        cout << endl;
    }

}

void  ContactList::updateContactIntoFile() {

    ofstream contactFile;
    contactFile.open("contactFile.txt");

    pCurr = pHead;

    for (int x = 0; x < noItem; x++) {
        contactFile << pCurr->name << endl;
        for (int i = 0; i < 5; i++) {
            if (pCurr->phone[i][0] != '\0') {
                contactFile << pCurr->phone[i] << " ";
            }
            else {
                break;
            }
        }
        contactFile << endl << pCurr->email << endl << pCurr->ringtone << endl;
        contactFile << pCurr->birthday;
        if (pCurr->link != NULL) {
            pCurr = pCurr->link;
            contactFile << endl << endl;
        }
    }

    contactFile.close();

}

