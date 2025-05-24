/*
Group Members (S2G2)
1. CHONG WAN XIAN CASEY D032310439
2. AUNI NADHIRAH BINTI ZAINAL D032310297
3. NURAIN BATRISYA BINTI MOHD NOR AZWAN D032310348
*/

// Main.cpp File

#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <cctype>
#include <iomanip>
#include "contactList.h"
using namespace std;

// Function prototypes
void showCertainDetails();
bool confirmationDisplayContact(int);
void addPhoneContact(int);
void addContact();
void deleteContact();
void searchContact();
void updateContact();
void sortContact();
void filterContact();

// Call the contactList class with object name 'contact'
ContactList contact;

// Add a new contact function
void addContact() {

	system("cls");

	// Declaration of variables
	int num = 0, phoneNum = 0;;
	char answer[10] = { "\0" };
	char phone[5][12] = { "\0" };
	int numContact = 0;
	bool error = false;

	// Ask user input the number of contact that they want to add
	cout << "\nHow many contacts do you want to add?" << endl;
	cout << "Amount: ";
	cin.getline(answer, 10);

	// Validate the input (Accept only number and non-negative)
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

	// If number of contact input == 0 means user does not want to add any contact
	// Stop running this function
	if (numContact == 0) {
		cout << "\nWe assume that you do not want to add any contact...";
		return;
	}
	// If the number of contact input is not 0
	else {

		// Loop based on the number
		for (int x = 0; x < numContact; x++) {

			char name[30] = { "\0" }, birthday[12] = { "\0" };
			char email[50] = { "\0" }, ringtoneOption[50][100] = { "\0" }, ringtone[50] = { "\0" };

			// Ask user to input the name of contact
			cout << "\n\n----------- Contact " << x + 1 << " -----------" << endl;
			cout << "\nName: ";
			cin.getline(name, 30);

			// Validate the input (Empty name is not allowed)
			while (name[0] == '\0') {
				cout << "\n\tThe contact name should not be NULL!";
				cout << "\n\tPlaase try again";
				cout << "\n\tName: ";
				cin.getline(name, 30);
			}

			// Ask user to input number of phone that they want to add
			cout << "\nHow many phone number you wanna input? (MUST at least 1 and not more than 5)" << endl;
			cout << "Amount: ";
			cin.getline(answer, 10);

			// Validate the input (Accept only number and in the range of 1 to 5 only)
			do {

				error = false;
				phoneNum = atoi(answer);

				if (cin.fail()) {
					cin.clear();
					cin.ignore();
					cout << "\n\tAnswer Invalid!";
					error = true;
				}
				else if (phoneNum < 0) {
					cout << "\n\tInvalid! The number you input CANNOT be NEGATIVE!";
					error = true;
				}
				else if (!isdigit(answer[0])) {
					cout << "\n\tInvalid! The input CANNOT be NON-NUMBER value!";
					error = true;
				}
				else if (phoneNum < 1 || phoneNum > 5) {
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
			// Loop based on the number
			for (int i = 0; i < phoneNum; i++) {

				// Ask user to input the phone number
				cout << "Phone " << i + 1 << ": ";
				cin.getline(phone[i], 12);

				// Validate the input (Accept only number and only in 10 or 11 digits)
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

			// Ask user to input the email for new contact
			cout << "\nEmail: ";
			cin.getline(email, 50);

			if (email[0] == '\0') {
				strcpy_s(email, "XXX");
			}

			// Input ringtone from input file
			ifstream inputRingtone;
			inputRingtone.open("ringtoneFile.txt");

			// Check if the input exist in user computer/ folder
			if (!inputRingtone) {
				cout << "\n\tRingtone File failed to open!" << endl;
				return;
			}

			cout << "\nRingtone Options: ";

			// Display all the option available from the file
			int i = 0;
			char line[100] = { "\0" };
			while (inputRingtone.getline(line, 100)) {
				cout << endl << i + 1 << ". " << line;
				strcpy_s(ringtoneOption[i], line);
				i++;
			}

			// Close the file
			inputRingtone.close();

			// Ask user to input a ringtone that they want to filter
			cout << "\n\nChoose a ringtone (In between 1 to " << i << "): ";
			cin.getline(answer, 10);

			// Validate the input (Accept only in the range of 1 to Max ringtone in the file)
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

			// Copy the ringtone that the user choose into the proper variable that store ringtone
			strcpy_s(ringtone, ringtoneOption[num - 1]);
			cout << "\nRingtone \"" << ringtone << "\" is choose!" << endl;
	

			int dayInt = 0; string dayString = ""; char day[8] = { "\0" };
			int monthInt = 0; char month[7] = { "\0" };
			char year[5] = { "\0" };
			int yearLength = 0;

			// Ask user to input the day of birth
			cout << "\nBirthday Details: " << endl;
			cout << "\nEnter your birth's day (1 - 31): ";
			cin.getline(answer, 10);

			// Validate the input (Accept only in the range of 1 to 31)
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

			// Ask user to input the month of birth
			cout << "\nEnter your birth's month (1-12): ";
			cin.getline(answer, 10);

			// Validate the input (Accept only in the range of 1 to 12)
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

			// Based on the month that user input in integer format
			// Set the corresponding word format into variable month
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

			// Ask user to input the year of birth
			cout << "\nEnter your birth's year in 4-digit : ";
			cin.getline(year, 5);

			// Validate the input (Accept only number and must be 4 digits)
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

			// Combine day, month, and year together into a variable
			strncat_s(birthday, day, 2);
			strncat_s(birthday, month, 5);
			strncat_s(birthday, year, 4);

			contact.insertContact(name, phoneNum, phone, email, ringtone, birthday);

		}

		// Call the displayAllContactList() method to add the contact and their details
		cout << "\n\nContact Details: " << endl;;
		contact.displayAllContactList();

	}

}

// Function to ask user whether they want to view a certain specific contact or not
void showCertainDetails() {

	// Declaration of variables
	char choice[10] = { "\0" };
	bool error = false;
	char contactChoose[50] = { "\0" };

	// Ask user whether they want to view the specific contact in the contact list or not
	cout << "\nDo you want to choose a contact to view their details? (Y/N)" << endl;
	cout << "Choice: ";
	cin.getline(choice, 10); _strupr_s(choice);

	// Validate the input (Accept only either yes/ y/ no/ n)
	do {

		error = false;

		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "\n\tInvalid!";
			error = true;
		}
		else if (strcmp(choice, "YES") != 0 && strcmp(choice, "NO") != 0 && strcmp(choice, "Y") != 0 && strcmp(choice, "N") != 0) {
			cout << "\n\tInvalid ! The answer should be either YES or NO!";
			error = true;
		}


		if (error == true) {
			cout << "\n\tPlease try again! ";
			cout << "\n\n\tChoice : ";
			cin.getline(choice, 10); _strupr_s(choice);
		}
	} while (error == true);

	// If user want to view
	if (strcmp(choice, "YES") == 0 || strcmp(choice, "Y") == 0) {

		do {

			// Ask user to input a contact that they want to view
			// Either by their name/ phone/ email
			cout << "\n\nEnter a contact that you want to view his/ her details? (By his/ her Name or Phone or Email)" << endl;
			cout << "Contact: ";
			cin.getline(contactChoose, 50);

			// Validate the input (The input cannot exceed the cstring array size)
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
					cin.getline(contactChoose, 50);
				}

			} while (error == true);

			// Display the target contact
			cout << endl;
			contact.displaySpecificContactList(contactChoose);

			// Ask user if they want to view another contact or not
			cout << "\nDo you want to view another contact details? (Y/N)" << endl;
			cout << "Choice: ";

			cin.getline(choice, 10); _strupr_s(choice);

			// Validate the input (Accept only either yes/ y/ no/ n)
			do {

				error = false;

				if (cin.fail()) {
					cin.clear();
					cin.ignore();
					cout << "\n\tInvalid!";
					error = true;
				}
				else if (strcmp(choice, "YES") != 0 && strcmp(choice, "NO") != 0 && strcmp(choice, "Y") != 0 && strcmp(choice, "N") != 0) {
					cout << "\n\tInvalid ! The answer should be either YES or NO!";
					error = true;
				}

				if (error == true) {
					cout << "\n\tPlease try again! ";
					cout << "\n\n\tChoice : ";
					cin.getline(choice, 10); _strupr_s(choice);
				}

			} while (error == true);

			// Repeat the loop if yes
		} while (strcmp(choice, "YES") == 0 || strcmp(choice, "Y") == 0);

		cout << endl;
	}
	else {
		cout << endl;
	}

}

// Function to ask user whether they want to have a look on the contact list or not
// Also ask user that they want to continue perform the operation they choose or not
// Before they perform operation
bool confirmationDisplayContact(int x) {

	bool error = false;
	char value[50] = { "\0" };
	char choice[10] = { "\0" };

	// Ask user if they want to display the contact lists or not
	cout << "\nDo you want to display the contact details? (YES<y> or NO<n>)" << endl;
	cout << "Answer: ";
	cin.getline(value, 50); _strupr_s(value);

	// Validate the input (Accept only yes/ y/ no/ n)
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

	// Get the total number of contact in the contact list
	// If contact list equal to zero meanas empty
	if (contact.getNoContact() == 0) {

		// Ask user whether they want to add new contact or not
		cout << "\nThere are empty record in the contact list." << endl;
		cout << "\nDo you wanna add new contact first? (Y/N)" << endl;
		cout << "Choice: ";
		cin.getline(choice, 10); _strupr_s(choice);

		// Validate the input (Accept only yes/ y/ no/ n)
		do {

			error = false;

			if (cin.fail()) {
				cin.clear();
				cin.ignore();
				cout << "\n\tInvalid!";
				error = true;
			}
			else if (strcmp(choice, "YES") != 0 && strcmp(choice, "NO") != 0 && strcmp(choice, "Y") != 0 && strcmp(choice, "N") != 0) {
				cout << "\n\tInvalid ! The answer should be either YES or NO!";
				error = true;
			}


			if (error == true) {
				cout << "\n\tPlease try again! ";
				cout << "\n\n\tChoice : ";
				cin.getline(choice, 10); _strupr_s(choice);
			}
		} while (error == true);

		// Run relevant method and commands if yes
		if (strcmp(choice, "YES") == 0 || strcmp(choice, "Y") == 0) {
			system("cls");
			cout << "\n[1] Add a contact selected." << endl;
			cout << "\nRedirecting...... Please wait........";
			this_thread::sleep_for(chrono::seconds(3));

			addContact();
		}
		
	}
	// If user decide to have a look on the contact list
	// And the contact list is not empty
	else if (strcmp(value, "YES") == 0 || strcmp(value, "Y") == 0) {

		// Display the contact lists by calling the displayAllContactList() method
		cout << "\nContact Details: " << endl;
		contact.displayAllContactList();

		// Ask user if they want to see a specific contact or not
		// By running the showCertainDetails() method
		if (x == 1) {
			showCertainDetails();
		}

	}
	// If user do not want to display the contact list
	else {
		cout << endl;
	}

	// Ask user if they want to continue perform the operation that they choose or not
	cout << "\nDo you still want to perform your operation? (Y/N)" << endl;
	cout << "Choice: ";
	cin.getline(choice, 10); _strupr_s(choice);

	// Validate the input (Accept only either yes/ y/ no/ n)
	do {

		error = false;

		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "\n\tInvalid!";
			error = true;
		}
		else if (strcmp(choice, "YES") != 0 && strcmp(choice, "NO") != 0 && strcmp(choice, "Y") != 0 && strcmp(choice, "N") != 0) {
			cout << "\n\tInvalid ! The answer should be either YES or NO!";
			error = true;
		}


		if (error == true) {
			cout << "\n\tPlease try again! ";
			cout << "\n\n\tChoice : ";
			cin.getline(choice, 10); _strupr_s(choice);
		}
		
	} while (error == true);

	// Return true if they want to perform
	if (strcmp(choice, "YES") == 0 || strcmp(choice, "Y") == 0) {
		return true;
	}
	// Return false if they do not want to continue perform
	else {
		cout << endl;
		return false;
	}

}

// Delete a contact function
void deleteContact() {

	system("cls");

	// Declaration of variables
	int indexLocation = 0, num = 0;
	bool error = false;
	char contactChoose[50] = { "\0" };
	char value[30] = { "\0" };

	// Ask user if they want to continue this operation or not
	// Continue if true, stop running this function if false
	if (confirmationDisplayContact(0) == false) return;

	// Ask user to input a contact that they want to delete
	// Either by their name/ phone/ email
	cout << "\n\nPlease enter a contact you want to delete (By name/ phone/ email): " << endl;
	cout << "Contact: ";
	cin.getline(contactChoose, 50);

	// Validate the input (The input cannot exceed the cstring array size)
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
			cout << "\n\tAnswer : ";
			cin.getline(contactChoose, 50);
		}

	} while (error == true);

	// Ask user whether they want to delete for a certain phone number or the whole contact
	cout << "\n\nYou want to delete a certain phone number or the whole contact? (PHONE/ CONTACT)" << endl;
	cout << "Choice: ";
	cin.getline(value, 30); _strupr_s(value);

	// Validate the input (Accept only either phone/ contact)
	do {

		error = false;

		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "\n\tInvalid!";
			error = true;
		}
		else if (strcmp(value, "PHONE") != 0 && strcmp(value, "PHONE NUMBER") != 0 && strcmp(value, "PHONE NUM") != 0 && strcmp(value, "CONTACT") != 0) {
			cout << "\n\tInvalid ! The answer should be either PHONE or CONTACT!";
			error = true;
		}

		if (error == true) {
			cout << "\n\tPlease try again! ";
			cout << "\n\tChoice : ";
			cin.getline(value, 30); _strupr_s(value);
		}

	} while (error == true);

	// If contact is choose
	if (strcmp(value, "CONTACT") == 0) {

		// Delte the whole contact by calling this method
		contact.deleteContact(contactChoose);
	}
	// If phone is choose
	else {
		
		// Check if the contact that the user input is exist in the contact list (Run if exist)
		if (contact.traverse(indexLocation, contactChoose) == true) {

			// Display the details of the contact
			cout << "Here is the details of contact \'" << contactChoose << "\': " << endl;

			contact.displaySpecificContactList(contactChoose);

			// Ask user to input a phone number of the target contact that they want to delete
			cout << "Which phone number you want to delete? Enter the number or the range from 0 to " << contact.getNumOfPhone(indexLocation) << endl;
			cout << "Phone Num/ Range: ";
			cin.getline(value, 30);

			// Validate the input (Accept only the complete phone or the range from 0 to max no phone that the contact has)
			do {

				int phoneLength = strlen(value);
				error = false;
				num = atoi(value);

				if (cin.fail()) {
					cin.clear();
					cin.ignore();
					cout << "\n\tAnswer Invalid!";
					error = true;
				}
				else if (phoneLength == 1) {
					if (num < 0 || num > contact.getNumOfPhone(indexLocation)) {
						cout << "\n\tInvalid! The number you input should in between 0 to " << contact.getNumOfPhone(indexLocation) << " only!";
						error = true;
					}
				}
				else if (num < 0) {
					cout << "\n\tInvalid! The number you input CANNOT be NEGATIVE!";
					error = true;
				}

				if (error == true) {
					cout << "\n\tPlaase try again";
					cout << "\n\tChoice: ";
					cin.getline(value, 30);
					cout << endl;
				}

			} while (error == true);
	
			// Method to get the proper phone number
			// If user input phone in range (1 to 5) instead of complete phone
			contact.getPhoneNum(indexLocation, value);

			// Check if the phone that the user input is exist for the target contact (Run if exist)
			if (contact.traverse(indexLocation, value) == true) {

				// Call method deleteContactPhone() to delete the phone for the target contact
				contact.deleteContactPhone(indexLocation, value);
			}
			// If the phone is not exist in the target contact
			// Display the relevant commands
			else {
				cout << endl << "Delete Failed! Phone Number " << value << " Not Found!" << endl << endl;
			}

		}
		// If the target contact that the user input is not exist in the contact list
		else {

			cout << "\nUnable to delete the phone number " << contactChoose << " because contact NOT FOUND!" << endl << endl;

		}
		
	}

	return;

}

// Searching/ Traverse contact function
void searchContact() {

	system("cls");

	// Declaration of variables
	bool error = false;
	char value[50] = { "\0" };
	int indexLocation = 0;

	// Ask user if they want to continue this operation or not
	// Continue if true, stop running this function if false
	if (confirmationDisplayContact(0) == false) return;

	// Ask user to input contact that they want to search
	// Either by their name/ phone/ email
	cout << "\n\nPlease enter a contact you want to search (By name/ phone/ email): " << endl;
	cout << "Contact: ";
	cin.getline(value, 50);

	// Validate the input (The input cannot exceed the cstring array size)
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

	// Check if the contact that the user input exist
	if (contact.traverse(indexLocation, value) == true) {
		
		// Get the name of the contact by calling this method
		contact.getContactName(indexLocation, value);

		// Display the details of the contact and their index location in the contact list
		cout << "\n\nHere is the details for " << value << ": " << endl;
		contact.displaySpecificContactList(value);
		cout << "Contact " << value << " found at " << indexLocation + 1 << endl << endl;
		cout << setw(120) << setfill('-') << "-" << endl << endl;
	}
	// If the contact is not exist in the contact list
	else {
		cout << "\nContact \'" << value << "\' you input NOT FOUND!" << endl << endl;
	}

	return;

}

// Add a new phone to a contact function
void addPhoneContact(int indexLocation) {

	// Declaration of variables
	char answer[10] = { "\0" };
	bool error = false;
	int phoneNum = 0;
	char phone[5][12] = { "\0" };

	// Ask user to input number of phone that they want to add
	cout << "\n\nHow many phone number you wanna input? (MUST at least 1 and not more than 5)" << endl;
	cout << "Amount: ";
	cin.getline(answer, 10);

	// Validate the input (Accept only in the range of 1 to 5)
	do {

		error = false;
		phoneNum = atoi(answer);

		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "\n\tAnswer Invalid!";
			error = true;
		}
		else if (phoneNum < 0) {
			cout << "\n\tInvalid! The number you input CANNOT be NEGATIVE!";
			error = true;
		}
		else if (!isdigit(answer[0])) {
			cout << "\n\tInvalid! The input CANNOT be NON-NUMBER value!";
			error = true;
		}
		else if (phoneNum < 1 || phoneNum > 5) {
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
	// Based on the number of phone that user input
	// Loop it
	for (int i = 0; i < phoneNum; i++) {

		// Ask user to input the phone number
		cout << "Phone " << i + 1 << ": ";
		cin.getline(phone[i], 12);

		// Validate the phone added (Accept only number and must be either 10 or 11 digits)
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

	// Call the insertContactPhone() method to insert the phone
	contact.insertContactPhone(indexLocation, phoneNum, phone);

}

// Update function
void updateContact() {

	system("cls");

	// Declaration of relevant variables
	bool error = false;
	char type[20] = { "\0" };
	char targetContact[50] = { "\0" };
	char answer[10] = { "\0" };
	char update[100] = { "\0" };
	int indexLocation = 0;

	// Ask user if they want to continue this operation or not
	// Continue if true, stop running this function if false
	if (confirmationDisplayContact(1) == false) return;

	// Ask user to input the type that they want to update
	cout << "\n\nPlease enter the type you want update (name/ phone/ email/ ringtone/ birthday): " << endl;
	cout << "Type: ";
	cin.getline(type, 20); _strupr_s(type);

	// Validate the input (Accept only either name/ phone/ email/ ringtone/ birthday)
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

	// Ask user to input a contact that they want to input
	// They can input contact by their name/ phone/ email
	cout << "\n\nPlease enter a contact you want to update (By name/ phone/ email): " << endl;
	cout << "Contact: ";
	cin.getline(targetContact, 50);

	// Validate the input (The input cannot exceed the cstring array size)
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

	// If type 'name' is choose
	if (strcmp(type, "NAME") == 0) {

		// Ask user to input new name that they want to update
		cout << "\nNew Name: ";
		cin.getline(update, 30);

		// Validate the input (Cannot accept input nothing)
		while (update[0] == '\0') {
			cout << "\n\tThe contact name should not be NULL!";
			cout << "\n\tPlaase try again";
			cout << "\n\tName: ";
			cin.getline(update, 30);
		}

	}
	// If type 'email' is choose
	else if (strcmp(type, "EMAIL") == 0) {

		// Check if the contact that the user input exist
		if (contact.traverse(indexLocation, targetContact) == true) {
			// Ask user to input new email that they want to update
			cout << "\nNew Email: ";
			cin.getline(update, 50);

			// If user input nothing to the email
			// Will auto set 'xxx' to the email by default
			if (update[0] == '\0') {
				strcpy_s(update, "XXX");
			}
		}
		else {
			cout << "\nUnable to update for email because contact \'" << targetContact << "\' not found!" << endl << endl;
		}

	}
	// If type 'phone' is choose
	else if (strcmp(type, "PHONE") == 0) {

		char phoneOld[30] = { "\0" };
		int num = 0;
		int indexLocation = 0;
		char phoneUpdate[30] = { "\0" };

		// Check if the contact that the user input exist
		if (contact.traverse(indexLocation, targetContact) == true) {
			
			// Get how many number of phone that the contact has
			// Check if the phone record is 0 or not (Run if 0)
			if (contact.getNumOfPhone(indexLocation) == 0) {

				// Since phone record is 0, so ask user if they want to add new phone or not
				cout << "\n\nSince the contact \'" << targetContact << "\' does not contain any phone number" << endl;
				cout << "Do you want to add new phone numbers for this contact? (Y/N)" << endl;
				cout << "Choice: ";
				cin.getline(answer, 10); _strupr_s(answer);

				// Validate the input (Accept only either yes/ y/ no/ n)
				do {

					error = false;

					if (cin.fail()) {
						cin.clear();
						cin.ignore();
						cout << "\n\tAnswer Invalid!";
						error = true;
					}
					else if (strcmp(answer, "YES") != 0 && strcmp(answer, "NO") != 0 && strcmp(answer, "Y") != 0 && strcmp(answer, "N") != 0) {
						cout << "\n\tInvalid! The number you input was not YES or NO!";
						error = true;
					}

					if (error == true) {
						cout << "\n\tPlaase try again";
						cout << "\n\tChoice: ";
						cin.getline(answer, 10);  _strupr_s(answer);
						cout << endl;
					}

				} while (error == true);

				// Call function addPhoneContact if yes
				if (strcmp(answer, "YES") == 0 || strcmp(answer, "Y") == 0) {
					addPhoneContact(indexLocation);
				}
				// Display relevant command if no
				else {
					cout << "\n\nNo update made to contact \'" << targetContact << "\'!" << endl << endl;
				}

			}
			// If the phone record of that contact is not 1 (More than 1)
			else {

				cout << "\n\nHere is the datails for contact \'" << targetContact << "\': " << endl;
				contact.displaySpecificContactList(targetContact);

				// Ask user to input the phone that they want to update
				// Either by complete phone number or range (0 to max phone record)
				cout << "\n\nWhich phone number you want to update? Enter the number or the range from 0 to " << contact.getNumOfPhone(indexLocation) << endl;
				cout << "Phone Num/ Range: ";
				cin.getline(phoneOld, 30);

				// Validate the input
				do {

					int phoneLength = strlen(phoneOld);
					error = false;
					num = atoi(phoneOld);

					if (cin.fail()) {
						cin.clear();
						cin.ignore();
						cout << "\n\tAnswer Invalid!";
						error = true;
					}
					else if (phoneLength == 1) {
						if (num < 0 || num > contact.getNumOfPhone(indexLocation)) {
							cout << "\n\tInvalid! The number you input should in between 0 to " << contact.getNumOfPhone(indexLocation) << " only!";
							error = true;
						}
					}
					else if (num < 0) {
						cout << "\n\tInvalid! The number you input CANNOT be NEGATIVE!";
						error = true;
					}

					if (error == true) {
						cout << "\n\tPlaase try again";
						cout << "\n\tChoice: ";
						cin.getline(phoneOld, 30);
						cout << endl;
					}

				} while (error == true);

				// If user input in range, call this method to get the complete phone number
				contact.getPhoneNum(indexLocation, phoneOld);

				// Check if the phone that user input exist in the target contact (Run if exist)
				if (contact.traverse(indexLocation, phoneOld) == true) {

					// Ask user to input new phone that they want to update
					cout << "\n\nNew phone number that you want to update: ";
					cin.getline(phoneUpdate, 30);

					// Validate the input (Accept only number and must be either 10 or 11 digits)
					do {

						error = false;
						int phoneLength = strlen(phoneUpdate);

						if (cin.fail()) {
							cin.clear();
							cin.ignore();
							cout << "\n\tAnswer Invalid!";
							error = true;
						}
						else if (phoneLength != 10 && phoneLength != 11) {
							cout << "\n\tInvalid! The number you input MUST in the range of 10 or 11 ONLY!";
							error = true;
						}

						if (error == true) {
							cout << "\n\tPlaase try again";
							cout << "\n\tChoice: ";
							cin.getline(phoneUpdate, 30);
							cout << endl;
						}

					} while (error == true);

					// Call the updateContactPhone() method to update the phone to the particular contact
					contact.updateContactPhone(indexLocation, phoneOld, phoneUpdate);

				}
				// If the phone that user want to input not found in the target contact
				else {

					cout << "\nUnable to update for phone because phone \'" << phoneOld << "\' not found in contact \'" << targetContact << "\' !" << endl << endl;

				}

			}

		}
		// If the target contact not found
		else {

			cout << "\nUnable to update for phone because contact \'" << targetContact << "\' not found!" << endl << endl;
		}

	}
	// If type 'ringtone' is choose
	else if (strcmp(type, "RINGTONE") == 0) {

		// Input ringtone from input file
		ifstream inputRingtone;
		inputRingtone.open("ringtoneFile.txt");

		char ringtoneOption[50][100] = { "\0" };
		int num = 0;

		// Check if the input exist in user computer/ folder
		if (!inputRingtone) {
			cout << "\n\tRingtone File failed to open!" << endl;
			return;
		}

		cout << "\nRingtone Options: ";

		// Display all the option available from the file
		int i = 0;
		char line[100] = { "\0" };
		while (inputRingtone.getline(line, 100)) {
			cout << endl << i + 1 << ". " << line;
			strcpy_s(ringtoneOption[i], line);
			i++;
		}

		// Close the file
		inputRingtone.close();

		// Ask user to input a ringtone that they want to filter
		cout << "\n\nChoose a ringtone (In between 1 to " << i << "): ";
		cin.getline(answer, 10);

		// Validate the input (Accept only in the range of 1 to Max 
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
	// If birthday is choose
	else if (strcmp(type, "BIRTHDAY") == 0) {

		int dayInt = 0; string dayString = ""; char day[8] = { "\0" };
		int monthInt = 0; char month[7] = { "\0" };
		char year[5] = { "\0" };
		int yearLength = 0;

		// Ask user to input the day of birth
		cout << "\n\nBirthday Details: " << endl;
		cout << "\nEnter your birth's day (1 - 31): ";
		cin.getline(answer, 10);

		// Validate the input (Accept only in the range of 1 to 31)
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

		// Ask user to input the month of birth
		cout << "\nEnter your birth's month (1-12): ";
		cin.getline(answer, 10);

		// Validate the input (Accept only in the range of 1 to 12)
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

		// Based on the month that user input in integer format
		// Set the corresponding word format into variable month
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

		// Ask user to input the year of birth
		cout << "\nEnter your birth's year in 4-digit : ";
		cin.getline(year, 5);

		// Validate the input (Accept only number and must be 4 
		while (strlen(year) != 4 || !isdigit(year[0]) || !isdigit(year[1]) || !isdigit(year[2]) || !isdigit(year[3])) {
			cout << "\n\tPlease enter a valid 4-digit birth's year ! " << endl;
			cout << "\tBirth's year : ";
			cin.getline(year, 5);
		}

		// Combine day, month, and year together into a variable
		strncat_s(update, day, 2);
		strncat_s(update, month, 5);
		strncat_s(update, year, 4);

	}

	// Call the updateContact() method to update the contact details
	contact.updateContact(type, targetContact, update);

	return;

}

// Sorting Function
void sortContact() {

	system("cls");

	// Declaration of variables
	bool error = false;
	char choice[10] = { "\0" };

	// Ask user if they want to continue this operation or not
	// Continue if true, stop running this function if false
	if (confirmationDisplayContact(0) == false) return;

	// Get the total number of contact in the list
	// Check if there is only 1 record in the list or not (Run if yes)
	if (contact.getNoContact() == 1) {

		cout << "\n\nThere only 1 record in your list" << endl;
		cout << "Sorting will not performed in this case." << endl;

		// If record = 1, ask user whether they want to add new contact or not
		cout << "\nDo you want to add a new contact? (Y/N)" << endl;
		cout << "Choice: ";
		cin.getline(choice, 10); _strupr_s(choice);

		// Validate the input (Accept only either yes/ y/ no/ n)
		do {

			error = false;

			if (cin.fail()) {
				cin.clear();
				cin.ignore();
				cout << "\n\tAnswer Invalid!";
				error = true;
			}
			else if (strcmp(choice, "YES") != 0 && strcmp(choice, "NO") != 0 && strcmp(choice, "Y") != 0 && strcmp(choice, "N") != 0) {
				cout << "\n\tInvalid ! The type you input was not YES (Y) or NO (N)!";
				error = true;
			}

			if (error == true) {
				cout << "\n\tPlease try again! ";
				cout << "\n\tType : ";
				cin.getline(choice, 10); _strupr_s(choice);
			}
			system("cls");

		} while (error == true);

		// If user input YES
		// Run relevant methods and commands about 'add contact'
		if (strcmp(choice, "YES") == 0 || strcmp(choice, "Y") == 0) {
			system("cls");
			cout << "\n[1] Add a contact selected." << endl;
			cout << "\nRedirecting...... Please wait........";
			this_thread::sleep_for(chrono::seconds(3));

			addContact();
		}
		// If user input NO
		else {
			contact.displayAllContactList();
		}
		
	}
	// If the record not only 1
	else {

		// Ask user to choose whether they want to sort by ascending or descending order
		cout << "\n\nSorting will be perform using CONTACT NAME!" << endl;
		cout << "\nYou want to sort the name in ascrending (ASC) or descending (DESC) order?" << endl;
		cout << "Choice: ";
		cin.getline(choice, 30); _strupr_s(choice);

		// Validate the input (Accept only either ascending/ asc/ descending/ desc)
		do {

			error = false;

			if (cin.fail()) {
				cin.clear();
				cin.ignore();
				cout << "\n\tInvalid!";
				error = true;

			}
			else if (strcmp(choice, "ASCENDING") != 0 && strcmp(choice, "DESCENDING") != 0 && strcmp(choice, "ASC") != 0 && strcmp(choice, "DESC") != 0) {
				cout << "\n\tInvalid! The answer is not ascending or descending!";
				error = true;
			}

			if (error == true) {
				cout << "\n\tPlaase try again";
				cout << "\n\tChoice: ";
				cin.getline(choice, 30); _strupr_s(choice);
			}

		} while (error == true);

		// Sort the contact lists
		contact.bubbleSort(choice);

		cout << endl;

		// Display the list after sorted
		if (strcmp(choice, "ASC") == 0 || strcmp(choice, "ASCENDING") == 0) {
			cout << "\n\nHere is the list after sorting in ASCENDING order: " << endl;
		}
		else {
			cout << "\n\nHere is the list after sorting in DESCENDING order: " << endl;
		}
		contact.displayAllContactList();

		// Ask user if they want to save the sorted list into output file or not
		cout << "\nDo you want to save the sorted contact list? (Y/N)" << endl;
		cout << "Choice: ";
		cin.getline(choice, 10); _strupr_s(choice);

		// Validate the input (Accept only yes/ y/ no/ n)
		do {

			error = false;

			if (cin.fail()) {
				cin.clear();
				cin.ignore();
				cout << "\n\tAnswer Invalid!";
				error = true;
			}
			else if (strcmp(choice, "YES") != 0 && strcmp(choice, "NO") != 0 && strcmp(choice, "Y") != 0 && strcmp(choice, "N") != 0) {
				cout << "\n\tInvalid ! The type you input was not YES (Y) or NO (N)!";
				error = true;
			}

			if (error == true) {
				cout << "\n\tPlease try again! ";
				cout << "\tChoice: ";
				cin.getline(choice, 10); _strupr_s(choice);
			}

		} while (error == true);

		// Save if yes
		if (strcmp(choice, "YES") == 0 || strcmp(choice, "Y") == 0) {
			contact.updateContactIntoFile();
			cout << "\nSorted contact list update successfully!" << endl << endl;
		}
		// Wont save if no
		else {
			cout << "\nSorted contact list didn't being update into record file!" << endl << endl;
		}
	}

	return;
}

// Filter function
void filterContact() {

	system("cls");

	// Ask user if they want to continue this operation or not
	// Continue if true, stop running this function if false
	if (confirmationDisplayContact(0) == false) return;

	// Declaration of relevant variables
	char type[20] = { "\0" };
	char thingFilter[50] = { "\0" };
	bool error = false;

	// Ask user to input type first before filter
	cout << "\n\nPlease enter the type you want filter (name/ phone/ email/ ringtone/ birthday): " << endl;
	cout << "Type: ";
	cin.getline(type, 20); _strupr_s(type);

	// Validate the input (Input must be either name/ phone/ email/ ringtone/ birthday only)
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

	// If name is choose
	if (strcmp(type, "NAME") == 0) {

		// Ask user to input something that they want to filter about name
		cout << "\n\nPlease enter something that you want to filter" << endl;
		cout << "Filter: ";
		cin.getline(thingFilter, 50);

	}
	// If phone is choose
	else if (strcmp(type, "PHONE") == 0) {

		// Ask user to input 3 digit that they want to filter about phone
		cout << "\n\nPlease enter first 3 digit of the phone that you want to filter (Exp: 012)" << endl;
		cout << "3 Digit: ";
		cin.getline(thingFilter, 50);

		// Validate the input (Only accept 3 digit)
		do {

			int digitLength = strlen(thingFilter);
			error = false;

			if (cin.fail()) {
				cin.clear();
				cin.ignore();
				cout << "\n\tAnswer Invalid!";
				error = true;
			}
			else if (digitLength != 3) {
				cout << "\n\tInvalid ! The digits was not 3!";
				error = true;
			}

			if (error == true) {
				cout << "\n\tPlease try again! ";
				cout << "\n\tChoice: ";
				cin.getline(thingFilter, 50);
			}

		} while (error == true);

	}
	// If email is choose
	else if (strcmp(type, "EMAIL") == 0) {

		// Ask user to input something that they want to filter about email
		cout << "\n\nPlease enter something that you want to filter" << endl;
		cout << "Filter: ";
		cin.getline(thingFilter, 50);

	}
	// If ringtone is choose
	else if (strcmp(type, "RINGTONE") == 0) {

		// Input ringtone from input file
		ifstream inputRingtone;
		inputRingtone.open("ringtoneFile.txt");

		char ringtoneOption[50][100] = { "\0" };
		int num = 0;

		// Check if the input exist in user computer/ folder
		if (!inputRingtone) {
			cout << "\n\tRingtone File failed to open!" << endl;
			return;
		}

		cout << "\nRingtone Options: ";

		// Display all the option available from the file
		int i = 0;
		char line[100] = { "\0" };
		while (inputRingtone.getline(line, 100)) {
			cout << endl << i + 1 << ". " << line;
			strcpy_s(ringtoneOption[i], line);
			i++;
		}

		// Close the file
		inputRingtone.close();

		// Ask user to input a ringtone that they want to filter
		cout << "\n\nChoose a ringtone you want to filter (In between 1 to " << i << "): ";
		cin.getline(thingFilter, 50);

		// Validate the input (Accept only in the range of 1 to Max ringtone in the file)
		do {

			error = false;
			num = atoi(thingFilter);

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
			else if (!isdigit(thingFilter[0])) {
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
				cin.getline(thingFilter, 50);
				cout << endl;
			}

		} while (error == true);

		strcpy_s(thingFilter, ringtoneOption[num - 1]);

	}
	// If birthday is choose
	else if (strcmp(type, "BIRTHDAY") == 0) {

		char answer[10] = { "\0" };
		int dayInt = 0; string dayString = ""; char day[8] = { "\0" };
		int monthInt = 0; char month[7] = { "\0" };
		char year[5] = { "\0" };
		int yearLength = 0;

		// Ask user to input the day of birth
		cout << "\n\nFilter Birthday Details: " << endl;
		cout << "\nEnter the birth's day (1 - 31): ";
		cin.getline(answer, 10);

		// Validate the input (Accept only in the range of 1 to 31)
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

		// Ask user to input the month of birth
		cout << "\nEnter the birth's month (1-12): ";
		cin.getline(answer, 10);

		// Validate the input (Accept only in the range of 1 to 12)
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

		// Based on the month that user input in integer format
		// Set the corresponding word format into variable month
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

		// Ask user to input the year of birth
		cout << "\nEnter the birth's year in 4-digit : ";
		cin.getline(year, 5);

		// Validate the input (Accept only number and must be 4 digits)
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

		// Combine day, month, and year together into a variable
		strncat_s(thingFilter, day, 2);
		strncat_s(thingFilter, month, 5);
		strncat_s(thingFilter, year, 4);

	}

	// Call the filterAndDisplayContactList() method to filter and display the relevant contacts
	contact.filterAndDisplayContactList(type, thingFilter);

}

// Function main
int main() {

	// Declaration of variables
	int choiceNum = 0;
    char repeat = 'n';
	int indexLocation = 0;
	bool error = false;
	
	// Get contact lists from input file
	contact.insertContactFromFile();
        
    do {

		char choice[10] = { "\0" };
		repeat = 'n';

		// Show the main menu
		system("cls");
        cout << "\n-----------------------------------" << endl;
        cout << "   Welcome to Contact Directory" << endl;
        cout << "-----------------------------------" << endl;
        cout << "\n  1. Add a contact";
        cout << "\n  2. Delete a contact";
        cout << "\n  3. Search a contact";
        cout << "\n  4. Update a contact ";
        cout << "\n  5. Sorting contact list";
        cout << "\n  6. Filter contact list";
        cout << "\n  7. Display contact list";
        cout << "\n  8. Exit";
        cout << "\n\n-----------------------------------";
        cout << "\nEnter your choice (1-7) : ";
		cin.getline(choice, 10); // User input their choice

		// Looping to validate the choice
		// Check if the answer is valid
		// Loop until valid
		do {

			error = false;

			choiceNum = atoi(choice);

			if (cin.fail()) {
				cin.clear();
				cin.ignore();
				cout << "\n\tAnswer Invalid!";
				error = true;
			}
			else if (!isdigit(choice[0]) || (choiceNum < 1 || choiceNum > 8)) {
				cout << "\n\tInvalid choice!";
				error = true;
			}

			if (error == true) {
				cout << "\n\tPlease enter a number between 1 and 7 : ";
				cin.getline(choice, 10);
			}

		} while (error == true);

		// See whether which option that the user choose (In between 1 to 7)
		system("cls");
		switch (choiceNum) {

		// If 'Add a Contact' is choose
		// Run relevant methods for 'Add'
		case 1:
			cout << "\n[1] Add a contact selected." << endl;
			cout << "\nRedirecting...... Please wait........";
			this_thread::sleep_for(chrono::seconds(3)); // Act like loading

			addContact();
			contact.updateContactIntoFile();
			break;

		// If 'Delete a Contact' is choose
		// Run relevant methods for 'Delete'
		case 2:
			cout << "\n[2] Delete a Contact selected." << endl;
			cout << "\nRedirecting...... Please wait........";
			this_thread::sleep_for(chrono::seconds(3)); // Act like loading

			deleteContact();
			contact.updateContactIntoFile();
			break;

		// If 'Search a Contact' is choose
		// Run relevant methods for 'Search'
		case 3:
			cout << "\n[3] Search for a Contact selected." << endl;
			cout << "\nRedirecting...... Please wait........";
			this_thread::sleep_for(chrono::seconds(3)); // Act like loading

			searchContact();
			break;

		// If 'Update a Contact' is choose
		// Run relevant methods for 'Update'
		case 4:
			cout << "\n[4] Update a Contact selected." << endl;
			cout << "\nRedirecting...... Please wait........";
			this_thread::sleep_for(chrono::seconds(3)); // Act like loading

			updateContact();
			contact.updateContactIntoFile();
			break;

		// If 'Sort Contact' is choose
		// Run relevant methods for 'Sort'
		case 5:
			cout << "\n[5] Sort Contact List selected." << endl;
			cout << "\nRedirecting...... Please wait........";
			this_thread::sleep_for(chrono::seconds(3)); // Act like loading

			sortContact();
			break;

		// If 'Filter Contact' is choose
		// Run relevant methods for 'Filter'
		case 6:
			cout << "\n[6] Filter Contact List selected." << endl;
			cout << "\nRedirecting...... Please wait........";
			this_thread::sleep_for(chrono::seconds(3)); // Act like loading

			filterContact();
			break;

		// If 'Display Contact' is choose
		// Run relevant methods for 'Display'
		case 7:
			cout << "\n[7] Display All Contacts selected." << endl;
			cout << "\nRedirecting...... Please wait........";
			this_thread::sleep_for(chrono::seconds(3)); // Act like loading

			system("cls");
			cout << "\nContact Lists Follow Alphabet in Ascending Order: " << endl;
			contact.displayContactListFollowAlphabet();
			showCertainDetails();
			break;

		// If 'Exit' is choose
		// Run relevant commands for 'Exit'
		case 8:
			cout << "\nExiting the program..... Please wait.......";
			this_thread::sleep_for(chrono::seconds(3)); // Act like loading

			system("cls");
			cout << "\nThank you for using contact directory system !" << endl;
			exit(0);
		}

		// Ask if user want to choose another operation or not
		// If yes, loop back to top
		cout << "\nDo you want to choose another option ? (Y/N) : ";
		cin >> repeat; repeat = toupper(repeat);
		cin.ignore();

		// Check the validation of the user input
		if ((repeat != 'Y' && repeat != 'N') || cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "\n\nInvalid answer! The answer was not y or n!";
			cout << "\nTherefore, we assume that you do not want to continue!";

			cout << "\n\nThank you for using contact directory system !!\n";

			exit(0);
		}
            
    } while (repeat == 'Y');
        
	// If user dont want to choose option, then system end
	system("cls");
    cout << "\nThank you for using contact directory system !!\n";

	return 0;

}
