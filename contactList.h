/*
Group Members (S2G2)
1. CHONG WAN XIAN CASEY D032310439
2. AUNI NADHIRAH BINTI ZAINAL D032310297
3. NURAIN BATRISYA BINTI MOHD NOR AZWAN D032310348
*/

// contactList.h File (Header file)

#ifndef CONTACTLIST_H
#define CONTACTLIST_H
#include <string>
using namespace std;

// Class ContactList
class ContactList {

	// Class Node to keep tract on contact
	// Linkedlist
	class contact {

	// Data inside the linkedlist
	public:
		int noPhone;
		char name[30];
		char phone[5][12];
		char email[50];
		char ringtone[50];
		char birthday[12];
		contact* prev;
		contact* link;

		// Constructor of the contact class (Linkedlist)
		contact();
	};

// Private variable for class contactList
private:
	int index;
	int noContact;
	int noAlphabet;
	char trackAlphabet[26];
	char alphabetCapitalLetter[27];
	contact* pCurr, * pHead, * pTail;

// Public methods for class contactList
public:

	// Constructor and destructor
	ContactList();
	~ContactList();

	// Getter Methods
	int getNoContact();
	void getContactName(int, char[]);
	void getPhoneNum(int, char[]);
	int getNumOfPhone(int);

	// All the relevant methods and operations
	void insertContactFromFile(); // Input File
	void insertContactPhone(int indexLocation, int noPhone, char phone[][12]); // Add a new phone for a contact
	void insertContact(char name[], int noPhone, char phone[][12], char email[], char ringtone[], char birthday[]); // Add a new contact
	void deleteContactPhone(int, char phone[]); // Delete a phone in a contact
	void deleteContact(char name[]); // Delete a contact
	void updateContactPhone(int, char[], char phoneUpdate[]); // Update a phone in a contact
	void updateContact(char type[], char contact[], char contactUpdate[]); // Update one of the details in a contact
	bool traverse(int& indexLocation, char contactSearch[]); // Search and show the location/ index of the contact
	void bubbleSort(char choice[]); // ASC/ DESC of contacts
	void displaySpecificContactList(char[]); // Specific details of that person (Include birthday and ringtone)
	void displayAllContactList(); // Table form (All contacts but takde ringtone and birthday)
	void displayContactListFollowAlphabet(); // Ikut alphabet
	void filterAndDisplayContactList(char filterType[], char thingFilter[]); // Filter and display relavent contact
	void updateContactIntoFile(); // Output File

};
#endif
