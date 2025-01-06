#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <cctype>
#include "contactList.h"
using namespace std;

void confirmationDisplayContact();
void addContact();
void deleteContact();
void searchContact();
void updateContact();
void sortContact();

ContactList contact;

void addContact() {

	system("cls");

	int num = 0;
	char answer[10] = { "\0" };
	int numContact = 0;
	bool error = false;

	cout << "\nHow many contacts do you want to add?" << endl;
	cout << "Amount: ";
	cin.getline(answer, 10);

	do {

		error = false;

		numContact = atoi(answer);

		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "\n\tAnswer Invalid!";
			error = true;
		}
		else if (numContact < 0) {
			cout << "\n\tInvalid! The number you input CANNOT be NEGATIVE!";
			error = true;
		}
		else if (!isdigit(answer[0])) {
			cout << "\n\tInvalid! The input CANNOT be NON-NUMBER value!";
			error = true;
		}

		if (error == true) {
			cout << "\n\tPlaase try again";
			cout << "\n\tAmount: ";
			cin.getline(answer, 10);
		}

	} while (error == true);


	if (numContact == 0) {
		cout << "\nWe assume that you do not want to add any contact...";
		return;
	}
	else {

		for (int x = 0; x < numContact; x++) {

			char name[30] = { "\0" }, phone[5][12] = { "\0" }, birthday[12] = { "\0" };
			char email[50] = { "\0" }, ringtoneOption[50][100] = { "\0" }, ringtone[50] = { "\0" };

			cout << "\n\n----------- Contact " << x + 1 << " -----------" << endl;
			cout << "\nName: ";
			cin.getline(name, 30);

			while (name[0] == '\0') {
				cout << "\n\tThe contact name should not be NULL!";
				cout << "\n\tPlaase try again";
				cout << "\n\tName: ";
				cin.getline(name, 30);
			}


			cout << "\nHow many phone number you wanna input? (MUST at least 1 and not more than 5)" << endl;
			cout << "Amount: ";
			cin.getline(answer, 10);

			do {

				error = false;
				num = atoi(answer);

				if (cin.fail()) {
					cin.clear();
					cin.ignore();
					cout << "\n\tAnswer Invalid!";
					error = true;
				}
				else if (num < 0) {
					cout << "\n\tInvalid! The number you input CANNOT be NEGATIVE!";
					error = true;
				}
				else if (!isdigit(answer[0])) {
					cout << "\n\tInvalid! The input CANNOT be NON-NUMBER value!";
					error = true;
				}
				else if (num < 1 || num > 5) {
					cout << "\n\tInvalid! The number you input should in between 1 - 5 only!";
					error = true;
				}

				if (error == true) {
					cout << "\n\tPlaase try again";
					cout << "\n\tAmount: ";
					cin.getline(answer, 10);
				}

			} while (error == true);

			cout << endl;
			for (int i = 0; i < num; i++) {

				cout << "Phone " << i + 1 << ": ";
				cin.getline(phone[i], 12);

				do {

					error = false;
					int phoneLength = strlen(phone[i]);

					for (int a = 0; a < phoneLength; a++) {
						if (!isdigit(phone[i][a])) {
							cout << "\n\tInvalid! The input CANNOT contain any NON-NUMBER value!";
							error = true;
							break;
						}
					}

					if (error == false) {

						if (cin.fail()) {
							cin.clear();
							cin.ignore();
							cout << "\n\tAnswer Invalid!";
							error = true;
						}
						else if (phoneLength != 10 && phoneLength != 11) {
							cout << "\n\tPlease enter a phone number with 10 or 11 character ! ";
							error = true;
						}

					}

					if (error == true) {
						cout << "\n\tPhone number : ";
						cin.getline(phone[i], 12);
						cout << endl;
					}

				} while (error == true);

			}


			cout << "\nEmail: ";
			cin.getline(email, 50);

			if (email[0] == '\0') {
				strcpy_s(email, "XXX");
			}


			ifstream inputRingtone;
			inputRingtone.open("ringtoneFile.txt");

			if (!inputRingtone) {
				cout << "\n\tRingtone File failed to open!" << endl;
				return;
			}

			cout << "\nRingtone Options: ";

			int i = 0;
			char line[100] = { "\0" };
			while (inputRingtone.getline(line, 100)) {
				cout << endl << i + 1 << ". " << line;
				strcpy_s(ringtoneOption[i], line);
				i++;
			}

			inputRingtone.close();

			cout << "\n\nChoose a ringtone (In between 1 to " << i << "): ";
			cin.getline(answer, 10);

			do {

				error = false;
				num = atoi(answer);

				if (cin.fail()) {
					cin.clear();
					cin.ignore();
					cout << "\n\tAnswer Invalid!";
					error = true;
				}
				else if (num < 0) {
					cout << "\n\tInvalid! The number you input CANNOT be NEGATIVE!";
					error = true;
				}
				else if (!isdigit(answer[0])) {
					cout << "\n\tInvalid! The input CANNOT be NON-NUMBER value!";
					error = true;
				}
				else if (num < 1 || num > i) {
					cout << "\n\tInvalid! The number you input should in between 1 to " << i << " only!";
					error = true;
				}

				if (error == true) {
					cout << "\n\tPlaase try again";
					cout << "\n\tChoice: ";
					cin.getline(answer, 10);
					cout << endl;
				}

			} while (error == true);

			strcpy_s(ringtone, ringtoneOption[num - 1]);
			cout << "\nRingtone \"" << ringtone << "\" is choose!" << endl;
	

			int dayInt = 0; string dayString = ""; char day[8] = { "\0" };
			int monthInt = 0; char month[7] = { "\0" };
			char year[5] = { "\0" };
			int yearLength = 0;

			cout << "\nBirthday Details: " << endl;
			cout << "\nEnter your birth's day (1 - 31): ";
			cin.getline(answer, 10);

			do {

				error = false;
				dayInt = atoi(answer);

				if (cin.fail()) {
					cin.clear();
					cin.ignore();
					cout << "\n\tAnswer Invalid!";
					error = true;
				}
				else if (dayInt < 0) {
					cout << "\n\tInvalid! The number you input CANNOT be NEGATIVE!";
					error = true;
				}
				else if (!isdigit(answer[0])) {
					cout << "\n\tInvalid! The input CANNOT be NON-NUMBER value!";
					error = true;
				}
				else if (dayInt < 1 || dayInt > 31) {
					cout << "\n\tInvalid! The birth's day you input should in between 1 to 31 only!";
					error = true;
				}

				if (error == true) {
					cout << "\n\tPlaase try again";
					cout << "\n\tBirth's day (1-31): ";
					cin.getline(answer, 10);
					cout << endl;
				}

			} while (error == true);

			dayString = to_string(dayInt);
			strcpy_s(day, dayString.c_str());

			cout << "\nEnter your birth's month (1-12): ";
			cin.getline(answer, 10);

			do {

				error = false;
				monthInt = atoi(answer);

				if (cin.fail()) {
					cin.clear();
					cin.ignore();
					cout << "\n\tAnswer Invalid!";
					error = true;
				}
				else if (monthInt < 0) {
					cout << "\n\tInvalid! The number you input CANNOT be NEGATIVE!";
					error = true;
				}
				else if (!isdigit(answer[0])) {
					cout << "\n\tInvalid! The input CANNOT be NON-NUMBER value!";
					error = true;
				}
				else if (monthInt < 1 || monthInt > 12) {
					cout << "\n\tInvalid! The month you input should in between 1 to 12 only!";
					error = true;
				}

				if (error == true) {
					cout << "\n\tPlaase try again";
					cout << "\n\tBirth's month (1-12): ";
					cin.getline(answer, 10);
					cout << endl;
				}

			} while (error == true);

			switch (monthInt) {
			case 1:
				strcpy_s(month, "-JAN-");
				break;
			case 2:
				strcpy_s(month, "-FEB-");
				break;
			case 3:
				strcpy_s(month, "-MAR-");
				break;
			case 4:
				strcpy_s(month, "-APR-");
				break;
			case 5:
				strcpy_s(month, "-MAY-");
				break;
			case 6:
				strcpy_s(month, "-JUN-");
				break;
			case 7:
				strcpy_s(month, "-JUL-");
				break;
			case 8:
				strcpy_s(month, "-AUG-");
				break;
			case 9:
				strcpy_s(month, "-SEP-");
				break;
			case 10:
				strcpy_s(month, "-OCT-");
				break;
			case 11:
				strcpy_s(month, "-NOV-");
				break;
			case 12:
				strcpy_s(month, "-DEC-");
				break;
			}

			cout << "\nEnter your birth's year in 4-digit : ";
			cin.getline(year, 5);

			do {

				error = false;

				if (cin.fail()) {
					cin.clear();
					cin.ignore();
					cout << "\n\tAnswer Invalid!";
					error = true;
				}
				else if (strlen(year) != 4 || !isdigit(year[0]) || !isdigit(year[1]) || !isdigit(year[2]) || !isdigit(year[3])) {
					cout << "\n\tPlease enter a valid 4-digit birth's year ! " << endl;
					error = true;
				}

				if (error == true) {
					cout << "\tBirth's year : ";
					cin.getline(year, 5);
				}

			} while (error == true);

			strncat_s(birthday, day, 2);
			strncat_s(birthday, month, 5);
			strncat_s(birthday, year, 4);

			contact.insertContact(name, phone, email, ringtone, birthday);

		}

		cout << "\n\nContact Details: " << endl;;
		contact.displayContactList();

	}

}

void confirmationDisplayContact() {

	bool error = false;
	char value[50] = { "\0" };

	cout << "\nDo you want to display the contact details? (YES<y> or NO<n>)" << endl;
	cout << "Answer: ";
	cin.getline(value, 50); _strupr_s(value);

	do {

		error = false;

		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "\n\tAnswer Invalid!";
			error = true;
		}
		else if (strcmp(value, "YES") != 0 && strcmp(value, "NO") != 0 && strcmp(value, "Y") != 0 && strcmp(value, "N") != 0) {
			cout << "\n\tInvalid ! The answer should be either YES or NO!";
			error = true;
		}

		if (error == true) {
			cout << "\n\tPlease try again! ";
			cout << "\n\n\tAnswer : ";
			cin.getline(value, 50); _strupr_s(value);
		}

	} while (error == true);

	if (strcmp(value, "YES") == 0 || strcmp(value, "Y") == 0) {
		cout << "\nContact Details: " << endl;
		contact.displayContactList();
	}

	return;

}

void deleteContact() {

	system("cls");

	bool error = false;
	char value[50] = { "\0" };

	confirmationDisplayContact();

	cout << "\nPlease enter a contact you want to delete (By name/ phone/ email): " << endl;
	cout << "Contact: ";
	cin.getline(value, 50);

	do {

		error = false;

		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "\n\tAnswer Invalid!";
			error = true;
		}

		if (error == true) {
			cout << "\n\tPlease try again! ";
			cout << "\n\n\tAnswer : ";
			cin.getline(value, 50);
		}

	} while (error == true);

	contact.deleteContact(value);

	return;

}

void searchContact() {

	system("cls");

	bool error = false;
	char value[50] = { "\0" };
	int indexLocation = 0;

	confirmationDisplayContact();

	cout << "\nPlease enter a contact you want to search (By name/ phone/ email): " << endl;
	cout << "Contact: ";
	cin.getline(value, 50);

	do {

		error = false;

		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "\n\tAnswer Invalid!";
			error = true;
		}

		if (error == true) {
			cout << "\n\tPlease try again! ";
			cout << "\n\n\tAnswer : ";
			cin.getline(value, 50);
		}

	} while (error == true);

	if (contact.traverse(indexLocation, value) == true) {
		cout << "\nContact Found at " << indexLocation + 1 << endl;
	}
	else {
		cout << "\nContact Not Found" << endl;
	}

	return;

}

void updateContact() {

	system("cls");

	bool error = false;
	char type[20] = { "\0" };
	char targetContact[50] = { "\0" };
	char answer[10] = { "\0" };
	char update[100] = { "\0" };
	int indexLocation = 0;

	confirmationDisplayContact();

	cout << "\nPlease enter the type you want update (name/ phone/ email/ ringtone/ birthday): " << endl;
	cout << "Type: ";
	cin.getline(type, 20); _strupr_s(type);

	do {

		error = false;

		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "\n\tAnswer Invalid!";
			error = true;
		}
		else if (strcmp(type, "NAME") != 0 && strcmp(type, "PHONE") != 0 && strcmp(type, "EMAIL") != 0
			&& strcmp(type, "RINGTONE") != 0 && strcmp(type, "BIRTHDAY") != 0) {
			cout << "\n\tInvalid ! The type you input was not in the list above!";
			error = true;
		}

		if (error == true) {
			cout << "\n\tPlease try again! ";
			cout << "\n\n\tType : ";
			cin.getline(type, 20); _strupr_s(type);
		}

	} while (error == true);


	cout << "\nPlease enter a contact you want to search (By name/ phone/ email): " << endl;
	cout << "Contact: ";
	cin.getline(targetContact, 50);

	do {

		error = false;

		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "\n\tAnswer Invalid!";
			error = true;
		}

		if (error == true) {
			cout << "\n\tPlease try again! ";
			cout << "\n\n\tAnswer : ";
			cin.getline(targetContact, 50);
		}

	} while (error == true);

	if (strcmp(type, "PHONE") == 0) {

	}
	else if (strcmp(type, "RINGTONE") == 0) {

		ifstream inputRingtone;
		inputRingtone.open("ringtoneFile.txt");

		char ringtoneOption[50][100] = { "\0" };
		int num = 0;

		if (!inputRingtone) {
			cout << "\n\tRingtone File failed to open!" << endl;
			return;
		}

		cout << "\nRingtone Options: ";

		int i = 0;
		char line[100] = { "\0" };
		while (inputRingtone.getline(line, 100)) {
			cout << endl << i + 1 << ". " << line;
			strcpy_s(ringtoneOption[i], line);
			i++;
		}

		inputRingtone.close();

		cout << "\n\nChoose a ringtone (In between 1 to " << i << "): ";
		cin.getline(answer, 10);

		do {

			error = false;
			num = atoi(answer);

			if (cin.fail()) {
				cin.clear();
				cin.ignore();
				cout << "\n\tAnswer Invalid!";
				error = true;
			}
			else if (num < 0) {
				cout << "\n\tInvalid! The number you input CANNOT be NEGATIVE!";
				error = true;
			}
			else if (!isdigit(answer[0])) {
				cout << "\n\tInvalid! The input CANNOT be NON-NUMBER value!";
				error = true;
			}
			else if (num < 1 || num > i) {
				cout << "\n\tInvalid! The number you input should in between 1 to " << i << " only!";
				error = true;
			}

			if (error == true) {
				cout << "\n\tPlaase try again";
				cout << "\n\tChoice: ";
				cin.getline(answer, 10);
				cout << endl;
			}

		} while (error == true);

		strcpy_s(update, ringtoneOption[num - 1]);
		cout << "\nRingtone \"" << update << "\" is choose!" << endl;

	}
	else if (strcmp(type, "BIRTHDAY") == 0) {

		int dayInt = 0; string dayString = ""; char day[8] = { "\0" };
		int monthInt = 0; char month[7] = { "\0" };
		char year[5] = { "\0" };
		int yearLength = 0;

		cout << "\nBirthday Details: " << endl;
		cout << "\nEnter your birth's day (1 - 31): ";
		cin.getline(answer, 10);

		do {

			error = false;
			dayInt = atoi(answer);

			if (cin.fail()) {
				cin.clear();
				cin.ignore();
				cout << "\n\tAnswer Invalid!";
				error = true;
			}
			else if (dayInt < 0) {
				cout << "\n\tInvalid! The number you input CANNOT be NEGATIVE!";
				error = true;
			}
			else if (!isdigit(answer[0])) {
				cout << "\n\tInvalid! The input CANNOT be NON-NUMBER value!";
				error = true;
			}
			else if (dayInt < 1 || dayInt > 31) {
				cout << "\n\tInvalid! The birth's day you input should in between 1 to 31 only!";
				error = true;
			}

			if (error == true) {
				cout << "\n\tPlaase try again";
				cout << "\n\tBirth's day (1-31): ";
				cin.getline(answer, 10);
				cout << endl;
			}

		} while (error == true);

		dayString = to_string(dayInt);
		strcpy_s(day, dayString.c_str());

		cout << "\nEnter your birth's month (1-12): ";
		cin.getline(answer, 10);

		do {

			error = false;
			monthInt = atoi(answer);

			if (cin.fail()) {
				cin.clear();
				cin.ignore();
				cout << "\n\tAnswer Invalid!";
				error = true;
			}
			else if (monthInt < 0) {
				cout << "\n\tInvalid! The number you input CANNOT be NEGATIVE!";
				error = true;
			}
			else if (!isdigit(answer[0])) {
				cout << "\n\tInvalid! The input CANNOT be NON-NUMBER value!";
				error = true;
			}
			else if (monthInt < 1 || monthInt > 12) {
				cout << "\n\tInvalid! The month you input should in between 1 to 12 only!";
				error = true;
			}

			if (error == true) {
				cout << "\n\tPlaase try again";
				cout << "\n\tBirth's month (1-12): ";
				cin.getline(answer, 10);
				cout << endl;
			}

		} while (error == true);

		switch (monthInt) {
		case 1:
			strcpy_s(month, "-JAN-");
			break;
		case 2:
			strcpy_s(month, "-FEB-");
			break;
		case 3:
			strcpy_s(month, "-MAR-");
			break;
		case 4:
			strcpy_s(month, "-APR-");
			break;
		case 5:
			strcpy_s(month, "-MAY-");
			break;
		case 6:
			strcpy_s(month, "-JUN-");
			break;
		case 7:
			strcpy_s(month, "-JUL-");
			break;
		case 8:
			strcpy_s(month, "-AUG-");
			break;
		case 9:
			strcpy_s(month, "-SEP-");
			break;
		case 10:
			strcpy_s(month, "-OCT-");
			break;
		case 11:
			strcpy_s(month, "-NOV-");
			break;
		case 12:
			strcpy_s(month, "-DEC-");
			break;
		}

		cout << "\nEnter your birth's year in 4-digit : ";
		cin.ignore();
		cin.getline(year, 5);

		while (strlen(year) != 4 || !isdigit(year[0]) || !isdigit(year[1]) || !isdigit(year[2]) || !isdigit(year[3])) {
			cout << "\n\tPlease enter a valid 4-digit birth's year ! " << endl;
			cout << "\tBirth's year : ";
			cin.getline(year, 5);
		}

		strncat_s(update, day, 2);
		strncat_s(update, month, 5);
		strncat_s(update, year, 4);

	}
	else {
		cout << "\nPlease enter the value you to want update based on " << type << endl;
		cout << "Value: ";
		cin.getline(update, 50);
	}

	contact.updateContact(type, targetContact, update);

	return;

}

int main() {

	int choiceNum = 0;
    char repeat = 'n';
	int indexLocation = 0;
	bool error = false;

	contact.insertContactFromFile();
        
    do {

		char choice[10] = { "\0" };
		repeat = 'n';

		system("cls");
        cout << "\n----------------------------------" << endl;
        cout << "   Welcome to Contact Directory" << endl;
        cout << "----------------------------------" << endl;
        cout << "\n  1. Add a contact";
        cout << "\n  2. Delete a contact";
        cout << "\n  3. Search a contact";
        cout << "\n  4. Update a contact ";
        cout << "\n  5. Sorting contact list";
        cout << "\n  6. Display contact list";
        cout << "\n  7. Exit";
        cout << "\n\n--------------------------------";
        cout << "\nEnter your choice (1-7) : ";
		cin.getline(choice, 10);

		do {

			error = false;

			choiceNum = atoi(choice);

			if (cin.fail()) {
				cin.clear();
				cin.ignore();
				cout << "\n\tAnswer Invalid!";
				error = true;
			}
			else if (!isdigit(choice[0]) || (choiceNum < 1 || choiceNum > 7)) {
				cout << "\n\tInvalid choice!";
				error = true;
			}

			if (error == true) {
				cout << "\n\tPlease enter a number between 1 and 7 : ";
				cin.getline(choice, 10);
			}

		} while (error == true);

		system("cls");
		switch (choiceNum) {

		case 1:
			cout << "\n[1] Add a contact selected." << endl;
			cout << "\nRedirecting...... Please wait........";
			this_thread::sleep_for(chrono::seconds(3));

			addContact();
			break;
		case 2:
			cout << "\n[2] Delete a Contact selected." << endl;
			cout << "\nRedirecting...... Please wait........";
			this_thread::sleep_for(chrono::seconds(3));

			deleteContact();
			break;
		case 3:
			cout << "\n[3] Search for a Contact selected." << endl;
			cout << "\nRedirecting...... Please wait........";
			this_thread::sleep_for(chrono::seconds(3));

			searchContact();
			break;
		case 4:
			cout << "\n[4] Update a Contact selected." << endl;
			cout << "\nRedirecting...... Please wait........";
			this_thread::sleep_for(chrono::seconds(3));

			updateContact();
			break;
		case 5:
			cout << "\n[5] Sort Contact List selected." << endl;
			cout << "\nRedirecting...... Please wait........";
			this_thread::sleep_for(chrono::seconds(3));

			// bubble sort function
			break;
		case 6:
			cout << "\n[6] Display All Contacts selected." << endl;
			cout << "\nRedirecting...... Please wait........";
			this_thread::sleep_for(chrono::seconds(3));

			system("cls");
			contact.displayContactList();
			break;
		case 7:
			cout << "\nExiting the program. Thank you for using contact directory system !" << endl;
			exit(0);
		}

		cout << "\nDo you want to choose another option ? (y/n) : ";
		cin >> repeat; repeat = toupper(repeat);
		cin.ignore();

		if ((repeat != 'Y' && repeat != 'N') || cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "\nInvalid answer! The answer was not y or n!";
			cout << "\nTherefore, we assume that you do not want to continue!";

			cout << "\n\nThank you for using contact directory system !!\n";

			contact.updateContactIntoFile();

			exit(0);
		}
            
    } while (repeat == 'Y');
        
	system("cls");
	contact.updateContactIntoFile();
    cout << "\nThank you for using contact directory system !!\n";

	return 0;

}
