#ifndef CONTACTLIST_H
#define CONTACTLIST_H
#include <string>
using namespace std;

class ContactList {

	class Node {
	public:
		char name[30];
		char phone[5][12];
		char email[50];
		char ringtone[50];
		char birthday[12];
		Node* prev;
		Node* link;

		Node();
	};

private:
	int index;
	int noItem;
	Node* pCurr, * pHead, * pTail;

public:
	ContactList();
	~ContactList();
	void insertContactFromFile();
	void insertContact(char name[], char phone[][12], char email[], char ringtone[], char birthday[]);
	void deleteContact(char name[]);
	void updateContact(char type[], char contact[], char contactUpdate[]);
	bool traverse(int& indexLocation, char contactSearch[]);
	void bubbleSort();
	void displayContactList();
	void updateContactIntoFile();


};

#endif