/*
Group Members (S2G2)
1. CHONG WAN XIAN CASEY D032310439
2. AUNI NADHIRAH BINTI ZAINAL D032310297
3. NURAIN BATRISYA BINTI MOHD NOR AZWAN D032310348
*/

// contactList.cpp File (Implementation file)

#include <iostream>
#include <cstring>
#include <cctype>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include <sstream>
#include "contactList.h"
using namespace std;

// Constuctor for Node
ContactList::contact::contact() {

    noPhone = 0;

    strcpy_s(name, "\0");
    for (int x = 0; x < 5; x++) {
        phone[x][0] = '\0';
    }
    strcpy_s(email, "\0");
    strcpy_s(ringtone, "\0");
    strcpy_s(birthday, "\0");

    prev = link = NULL;
}

// Constructor for ContactList
ContactList::ContactList() {
    index = 0;
    noContact = 0;
    noAlphabet = 0;

    for (int x = 0; x < 26; x++) {
        trackAlphabet[x] = 0;
        alphabetCapitalLetter[x] = 'A' + x;
    }

    strcpy_s(trackAlphabet, "\0");
    pCurr = pHead = pTail = NULL;
}

ContactList::~ContactList() {}

int ContactList::getNoContact() {

    return noContact;

}

// Getter method
// Get the number of phone that a contact has
int ContactList::getNumOfPhone(int indexLocation) {

    pCurr = pHead;

    // Check if the indexLocation of the contact is the last one
    // pCurr will point to the last contact (pTail)
    if (indexLocation == noContact - 1) {
        pCurr = pTail;
    }
    // If the indexLocation of the contact is not the first one
    // Which the contact is located in the middle of the contact list
    else if (indexLocation != 0) {

        // Using looping to find the contact based on the indexLocation
        for (int x = 0; x < indexLocation && pCurr->link != NULL; x++) {
            pCurr = pCurr->link;
        }

    }

    // Return the num of phone if found
    return pCurr->noPhone;

}

// Getter method
// Get the name of the contact
void ContactList::getContactName(int indexLocation, char targetContactName[]) {

    pCurr = pHead;

    // Check if the indexLocation of the contact is the last one
    // pCurr will point to the last contact (pTail)
    if (indexLocation == noContact - 1) {
        pCurr = pTail;
    }
    // If the indexLocation of the contact is not the first one
    // Which the contact is located in the middle of the contact list
    else if (indexLocation != 0) {

        // Using looping to find the contact based on the indexLocation
        for (int x = 0; x < indexLocation && pCurr->link != NULL; x++) {
            pCurr = pCurr->link;
        }

    }

    // Copy the contact name into the variable targetCotactName (If the contact found)
    strcpy_s(targetContactName, 30, pCurr->name);

}

// Getter method
// Get the target phone number of a contact
// Not same as getNumOfPhone(), as that one is to get the number/ total phone that a contact has
// This one get the specific phone number only
void ContactList::getPhoneNum(int indexLocation, char targetPhoneNum[]) {

    pCurr = pHead;

    // Check if the indexLocation of the contact is the last one
    // pCurr will point to the last contact (pTail)
    if (indexLocation == noContact - 1) {
        pCurr = pTail;
    }
    // If the indexLocation of the contact is not the first one
    // Which the contact is located in the middle of the contact list
    else if (indexLocation != 0) {

        // Using looping to find the contact based on the indexLocation
        for (int x = 1; x <= indexLocation && pCurr->link != NULL; x++) {
            pCurr = pCurr->link;
        }

    }

    // Get the number of length/ digit for the phone
    int phoneLength = strlen(targetPhoneNum);

    // If phoneLength = 1 means if the phone user input is not the proper/ whole number
    // They just input the range between 1 and 5
    // So the phoneLength will be 1
    if (phoneLength == 1) {

        // Get the range choose from user (Between 1 to 5)
        int numRange = atoi(targetPhoneNum);

        // If user choose 0 means they do nothing to their phone number
        if (numRange == 0) {
            cout << "\nSince you input 0, so we assume that you do not want to did anything to your phone number!" << endl;
        }
        // If not zero means they may either want to update/ delete the target phone
        else {

            // -1 for the numRange cuz user input in the range of 1 to 5, but array start from 0 to 4
            numRange -= 1;

            // Since they input range just now, so I will have to get the proper phone num based on the range
            // And copy the proper phone number into the variale targetPhoneNum
            strcpy_s(targetPhoneNum, 12, pCurr->phone[numRange]);

        }

    }

}

// Input file
// Input all the exist contacts into the system from the file
void ContactList::insertContactFromFile() {

    // Declare and open the file
    ifstream contactRecordFile;
    contactRecordFile.open("contactRecordFile.txt");

    char line[100] = "\0";
    char getContactLine[100][100] = { "\0" };

    // If the file does not exist in user pc/ folder
    if (!contactRecordFile) {
        
        // A new file will be auto created to store their contact lists
        ofstream createContactListFile;
        createContactListFile.open("contactRecordFile.txt");
    }
    
    // Read line by line from the file and store each line into cstring variable 'line'
    // The variable 'line' just for temporary save each line
    // x used to keep track on the line of the file (Stop when reach null/ empty line)
    int x = 0;
    while (contactRecordFile.getline(line, 100)) {

        // Another cstring array to store all the line from file into 'getContactLine[]'
        strcpy_s(getContactLine[x], line);
        x++;

    }

    // Close the input file
    contactRecordFile.close();

    // Since x store the total line into file, and each contact will have 6 lines for their info
    // So x divided by 6 to get total number of contact in the list
    x = floor(x / 6);

    // Looping to get details from each contact
    // i+=6 cuz each contact have 5 info plus 1 empty line
    for (int i = 0; x > 0; x--, i+=6) {

        contact* pNew = new contact;
        pNew->link = NULL;
        pNew->prev = NULL;

        // Add the name into linkedlist
        strcpy_s(pNew->name, getContactLine[i + 1]);

        // Since each contact may has 5 phones
        // Therefore istrinfStream is used to reach how many phone number does a contact has
        istringstream getWordbyWordInRow(getContactLine[i + 2]);

        // Loop to get the number of phone that a contact has
        while (getWordbyWordInRow >> pNew->phone[pNew->noPhone]) {
            pNew->noPhone++;
        }

        // Add email into linkedlist
        strcpy_s(pNew->email, getContactLine[i + 3]);

        // Add ringtone into linkedlist
        strcpy_s(pNew->ringtone, getContactLine[i + 4]);

        // Add birthday into linkedlist
        strcpy_s(pNew->birthday, getContactLine[i + 5]);

        // If noItem == 0 means this contact is the first contact in the list
        // So pHead == pNew
        if (noContact == 0) {
            pHead = pNew;
        }
        // If the contact is in the middle
        else if (noContact != 0) {
            pNew->prev = pCurr;
            pCurr->link = pNew;
        }

        // Each contact added will +1 to the noItem to keep track on the total num of contacts
        noContact++;

        // pTail to keep track on each new contact come
        pTail = pNew;

        pCurr = pNew;

    }

}

// Insert new phone number to a certain contact
// For update/ delete (When no phone inside the specific contact)
void ContactList::insertContactPhone(int indexLocation, int noPhone, char phone[][12]) {

    pCurr = pHead;

    // Check if the indexLocation of the contact is the last one
    // pCurr will point to the last contact (pTail)
    if (indexLocation == noContact - 1) {
        pCurr = pTail;
    }
    // If the indexLocation of the contact is not the first one
    // Which the contact is located in the middle of the contact list
    else if (indexLocation != 0) {

        // Using looping to find the contact based on the indexLocation
        for (int x = 1; x <= indexLocation && pCurr->link != NULL; x++) {
            pCurr = pCurr->link;
        }

    }

    string phoneAddSuccess = "";

    // noPhone get from user, if they want to add 3 new phone, then noPhone = 3
    for (int x = 0; x < noPhone; x++) {

        // Add the phone into linkedlist
        strcpy_s(pCurr->phone[x], phone[x]);

        // For output use
        if (x == noPhone - 1) {
            phoneAddSuccess += "\'" + string(pCurr->phone[x]) + "\'";
        }
        else {
            phoneAddSuccess += "\'" + string(pCurr->phone[x]) + "'\, ";
        }
        pCurr->noPhone++;
    }

    cout << endl << noPhone << " new phone numbers " << phoneAddSuccess << " added successfully!" << endl << endl;

}

// Insert new contact into the list
void ContactList::insertContact(char name[], int noPhone, char phone[][12], char email[], char ringtone[], char birthday[]) {

    // Declare new node
    contact* pNew = new contact;

    // Setup each pointer, which all of them initially point to NULL
    pNew->link = NULL;
    pNew->prev = NULL;

    // Add name into linkedlist
    strcpy_s(pNew->name, name);
    
    // Add phone into the linkedlist
    for (int x = 0; x < noPhone; x++) {
        strcpy_s(pNew->phone[pNew->noPhone], phone[x]);
        pNew->noPhone++;
    }

    // Add email into the linkedlist
    strcpy_s(pNew->email, email);

    // Add ringtone into the linkedlist
    strcpy_s(pNew->ringtone, ringtone);

    // Add birthday into the linkedlist
    strcpy_s(pNew->birthday, birthday);

    // If noItem == 0 means the contact is the first one in the list
    // So pHead = pNew
    if (noContact == 0) {
        pHead = pNew;
    }
    // If not the keep track to next
    else {
        pNew->prev = pTail;
        pTail->link = pNew;
    }

    // Num of contact +1 everytime a new contact added
    noContact++;

    cout << "\nNew Contact " << pNew->name << " Inserted Successfully!" << endl << endl;

    // Each new contact always located as the last one, so pTail = pNew
    pTail = pNew;

}

// Delete specific phone number from a contact
void ContactList::deleteContactPhone(int indexLocation, char phone[]) {

    pCurr = pHead;

    // Check if the indexLocation of the contact is the first one
    // pCurr will point to the first contact (pHead)
	if (indexLocation == 0) {
        pCurr = pHead;
	}
    // If the indexLocation of the contact is the last one
    // pCurr will point to pTail
	else if (indexLocation == noContact - 1) {
        pCurr = pTail;
	}
    // If the indexLocation of the contact is not the first one or last one
    // Which the contact is located in the middle of the contact list
	else {

        // Using looping to find the contact based on the indexLocation
		for (int x = 0; x < indexLocation && pCurr->link != NULL; x++) {
            pCurr = pCurr->link;
		}

	}

    // Track the phone number that the user want to delete
    // Delete perform if the phone found
	for (int x = 0; x < pCurr->noPhone; x++) {

        // If noPhone == 1 means there is only 1 phone save inside the contact
        // So no need to search anymore
        if (pCurr->noPhone == 1) {

            // Set the first contact into null (Delete it)
            strcpy_s(pCurr->phone[0], "\0");
            cout << endl << "Phone Number " << phone << " Delete Successfully!" << endl << endl;

            // Number of phone - 1
            pCurr->noPhone--;

            // Stop the loop
            break;
        }
        // If there is more than 1 phone inside the contact, the loop will traverse for each phone
        else {

            // True if one of the phone same as the phone that the user input to delete, then target phone found
            if (strcmp(pCurr->phone[x], phone) == 0) {

                // Also, if target phone found, means all the phone after target should move forward for 1 cuz it is array
                for (int i = x; i < pCurr->noPhone - 1; i++) {
                    strcpy_s(pCurr->phone[i], pCurr->phone[i + 1]);
                }

                // Set the null to the last empty phone place
                strcpy_s(pCurr->phone[pCurr->noPhone - 1], "\0");

                cout << endl << "Phone Number " << phone << " Delete Successfully!" << endl << endl;

                // Number of phone - 1 if delete success
                pCurr->noPhone--;

                // Stop the loop
                break;

            }

        }

	}

    return;

}

// Delete a contact
// Delete by name/ email/ phone
void ContactList::deleteContact(char contactDelete[]) {

    int indexLocation = 0;
    contact* pTemp = pHead;

    // Search for the target contact and get the indexLocation
    // Run if target contact found
    if (traverse(indexLocation, contactDelete) == true) {

        // If indexLocation == 0 means the target contact in the first contact in the list
        if (indexLocation == 0) {

            // Move the second contact to front and delete the first contact
            pTemp = pHead;
            pHead = pHead->link;
            cout << endl << pTemp->name << " Delete Successfully!" << endl << endl;
            delete pTemp;

            // Number of contact - 1 if delete success
            noContact--;

            return;
        }
        // If indexLocation == last contact in the list
        else if (indexLocation == noContact - 1) {

            // Delete the last contact
            pTemp = pTail;
            pTail = pTail->prev;
            pTail->link = NULL;
            cout << endl << pTemp->name << " Delete Successfully!" << endl << endl;
            delete pTemp;

            // Number of contact - 1 if delete success
            noContact--;
            return;
        }
        // If the target contact is in the middle of the contact list
        else {

            // Find the contact based on the indexLocation search just now
            for (int x = 0; x < indexLocation && pTemp->link != NULL; x++) {
                pCurr = pTemp;
                pTemp = pTemp->link;
            }

   
            pCurr->link = pTemp->link;
            cout << endl << "Contact " << contactDelete << " Delete Successfully!" << endl << endl;
            delete pTemp;
            noContact--;
            return;

        }

    }
    // If target contact that user input not found
    else {
        cout << "\nUnable to delete because contact not found" << endl << endl;
    }

    return;

}

// Update the specific phone for a contact
void ContactList::updateContactPhone(int indexLocation, char phoneOld[], char phoneUpdate[]) {

    pCurr = pHead;

    // Check if the indexLocation of the contact is the first one
    // pCurr will point to the first contact (pHead)
	if (indexLocation == 0) {
        pCurr = pHead;
	}
    // If the indexLocation of the contact is the last one
    // pCurr will point to pTail
	else if (indexLocation == noContact - 1) {
        pCurr = pTail;
	}
    // If the indexLocation of the contact is not the first one or last one
    // Which the contact is located in the middle of the contact list
	else {

        // Using looping to find the contact based on the indexLocation
		for (int x = 0; x < indexLocation && pCurr->link != NULL; x++) {
            pCurr = pCurr->link;
		}

	}

    // Track the phone number that the user want to delete
    // Delete perform if the phone found
    for (int x = 0; x < pCurr->noPhone; x++) {

        // If noPhone == 1 means there is only 1 phone save inside the contact
        // So no need to search anymore
        if (pCurr->noPhone == 1) {

            // Update the new phone
            strcpy_s(pCurr->phone[0], phoneUpdate);
            cout << endl << "Phone Number Update Successfully from \'" << phoneOld << "\' to \'" << phoneUpdate << "\'!" << endl << endl;
            
            // Stop the looping
            break;
        }
        // If there is more than 1 phone inside the contact, the loop will traverse for each phone
        else {

            // True if one of the phone same as the phone that the user input to update, then target phone found
            if (strcmp(pCurr->phone[x], phoneOld) == 0) {

                strcpy_s(pCurr->phone[x], phoneUpdate);

                cout << endl << "Phone Number Update Successfully from \'" << phoneOld << "\' to \'" << phoneUpdate << "\'!" << endl << endl;
                
                // Stop the looping
                break;
            }

        }

    }

}

void ContactList::updateContactIntoFile() {

    ofstream contactFile;
    contactFile.open("contactRecordFile.txt");

    pCurr = pHead;

    for (int x = 0; x < noContact; x++) {
        contactFile << endl << pCurr->name << endl;
        for (int i = 0; i < pCurr->noPhone; i++) {
            contactFile << pCurr->phone[i] << " ";
        }
        contactFile << endl << pCurr->email << endl << pCurr->ringtone << endl;
        contactFile << pCurr->birthday << endl;
        if (pCurr->link != NULL) {
            pCurr = pCurr->link;
        }
    }

    contactFile.close();

}

// Update details for specific contact
void ContactList::updateContact(char type[], char targetContact[], char contactUpdate[]) {

    _strlwr_s(type, 20);
    int indexLocation = 0;
    contact* pTemp = new contact;

    // Search for the target contact and get the indexLocation if found
    if (traverse(indexLocation, targetContact) == true) {

        pCurr = pHead;

        // Check if the indexLocation of the contact is the first one
        // pCurr will point to the first contact (pHead)
        if (indexLocation == noContact - 1) {
            pCurr = pTail;
        }
        // If the indexLocation of the contact is not the first one or last one
        // Which the contact is located in the middle of the contact list
        else if (indexLocation != 0) {

            // Using looping to find the contact based on the indexLocation
            for (int x = 0; x < indexLocation && pCurr->link != NULL; x++) {
                pCurr = pCurr->link;
            }

        }

        // Set the first character of type into capital letter (For display use)
        type[0] = toupper(type[0]);

        // If name is choose to update
        if (strcmp(type, "Name") == 0) {

            // Get the old name for display use
            strcpy_s(pTemp->name, pCurr->name);

            // Update the new name into the linkedlist
            strcpy_s(pCurr->name, contactUpdate);

            cout << endl << "Update succesfully!" << endl;
            cout << type << " has update from " << pTemp->name << " to " << pCurr->name << endl << endl;
        }
        // If email is choose to update
		else if (strcmp(type, "Email") == 0) {

            // Get the old email for display use
            strcpy_s(pTemp->email, pCurr->email);

            // Update the new email into the linkedlist
			strcpy_s(pCurr->email, contactUpdate);

            cout << endl << "Update succesfully!" << endl;
            cout << type << " has update from " << pTemp->email << " to " << pCurr->email << endl << endl;
		}
        // If ringtone is choose to update
		else if (strcmp(type, "Ringtone") == 0) {

            // Get the old ringtone for display use
            strcpy_s(pTemp->ringtone, pCurr->ringtone);

            // Update the new ringtone into the linkedlist
			strcpy_s(pCurr->ringtone, contactUpdate);
            cout << endl << "Update succesfully!" << endl;
            cout << type << " has update from " << pTemp->ringtone << " to " << pCurr->ringtone << endl << endl;
		}
        // If birthday is choose to update
        else if (strcmp(type, "Birthday") == 0) {

            // Get the old birthday for display use
            strcpy_s(pTemp->birthday, pCurr->birthday);

            // Update the new birthday into the linkedlist
            strcpy_s(pCurr->birthday, contactUpdate);
            cout << endl << "Update succesfully!" << endl;
            cout << type << " has update from " << pTemp->birthday << " to " << pCurr->birthday << endl << endl;
        }

        // Delete the pTemp (For display use just now)
        delete pTemp;

    }
    // If target contact not found
    else {
        cout << "\nUnable to update because contact not found" << endl << endl;
    }

    return;

}

// Traverse each contact in the list to get the indxLocation
// Search by name/ phone/ email
bool ContactList::traverse(int& indexLocation, char contactSearch[]) {

    indexLocation = 0;
    pCurr = pHead;

    // Search by name
    // Tracking of the contact based on name
    while (strcmp(pCurr->name, contactSearch) != 0 && pCurr->link != NULL) {
        pCurr = pCurr->link;
        indexLocation++;
    }

    // If contact found then stop and return true
    if (strcmp(pCurr->name, contactSearch) == 0) {
        return true;
    }

    //////////////////////////////////

    // Search by phone
    // Tracking of the contact based on phone
    int x = 0;
    int trackContact = 0;
    indexLocation = 0;
    pCurr = pHead;
    while (strcmp(pCurr->phone[x], contactSearch) != 0 && pCurr->link != NULL) {
        x++;

        if (x == pCurr->noPhone) {
            x = 0;
            pCurr = pCurr->link;
            indexLocation++;
            trackContact++;
        }
        else if (trackContact == noContact){
            break;
        }
    }

    // If contact found then stop and return true
    if (strcmp(pCurr->phone[x], contactSearch) == 0) {
        return true;
    }

    ////////////////////////////////////////////////////
    
    // Search by email
    // Tracking of the contact based on email
    indexLocation = 0;
    pCurr = pHead;
    while (strcmp(pCurr->email, contactSearch) != 0 && pCurr->link != NULL) {
        pCurr = pCurr->link;
        indexLocation++;
    }

    // If contact found then stop and return true
    if (strcmp(pCurr->email, contactSearch) == 0) {
        return true;
    }

    // If contact not found then stop and return false
    return false;

}

// Sort the contact list based on their name (Either ascending or descending)
void ContactList::bubbleSort(char choice[]) {

    bool swapped = false;
    contact* pTemp;
    char currContact[30] = { "\0" };
    char nextContact[30] = { "\0" };

    // If Ascending is choose
	if (strcmp(choice, "ASCENDING") == 0 || strcmp(choice, "ASC") == 0) {

        // Apply bubble sort algorithm
        // This loop control the iteration of contact list
		for (int i = 0; i <= noContact; i++) {

			pCurr = pHead;

			swapped = false;

            // Loop control the index in the contact list
            // Start from 0 to the last contact
			for (int x = 0; x < noContact - 1; x++) {

                // pTemp control the next contact from the current contact
				pTemp = pCurr->link;

                // Takde case sensitive for first letter in the name
                // Exp, Lisa is same level as lisa
				strcpy_s(currContact, pCurr->name);
				strcpy_s(nextContact, pTemp->name);
				currContact[0] = toupper(currContact[0]);
				nextContact[0] = toupper(nextContact[0]);

                // If current contact larger than the next contact
                // Swapped
				if (strcmp(currContact, nextContact) > 0) {

					pTemp = pCurr->link;

                    // If index == 0, meaning now is comparing the first with the second contact
                    // Swapped between first and the second contact
					if (x == 0) {

						pHead = pTemp;

						pTemp->prev = pCurr->prev;

						if (pTemp->link != NULL) {
							pTemp->link->prev = pCurr;
						}

						pCurr->link = pTemp->link;
						pTemp->link = pCurr;
						pCurr->prev = pTemp;

						if (noContact == 2) {
							pTail = pCurr;
							break;
						}

					}
                    // If the index reach the second last contact
                    // Swapped between the second last and the last contact
					else if (x == noContact - 2) {

						pTail = pCurr;

						pCurr->link = pTemp->link;
						pCurr->prev->link = pTemp;
						pTemp->link = pCurr;
						pTemp->prev = pCurr->prev;
						pCurr->prev = pTemp;

					}
                    // If the index is in the middle of the contact list
                    // Swapped occur in the middle of the list
					else {

						pCurr->link = pTemp->link;
						pTemp->link->prev = pCurr;
						pCurr->prev->link = pTemp;
						pTemp->link = pCurr;
						pTemp->prev = pCurr->prev;
						pCurr->prev = pTemp;

					}

					swapped = true;

				}
                // If the current contact is not larger than the next contact
				else {
					pCurr = pTemp;
				}

			}

            // If swapped did not perform in one of the iteration
            // Like from first index to the last of that iteration did not perform at least 1 swapped
            // Then means the list already sorted well
            // Break the looping (Improve efficiency)
			if (swapped == false) {
				break;
			}

		}

	}
    // If descending is choose
    // Steps same as ascending, just the comparison change
	else {

		bool swapped = false;
        contact* pTemp;

        // Apply bubble sort algorithm
        // This loop control the iteration of contact list
		for (int i = 0; i <= noContact; i++) {

			pCurr = pHead;

			swapped = false;

            // Loop control the index in the contact list
            // Start from 0 to the last contact
			for (int x = 0; x < noContact - 1; x++) {

                // pTemp control the next contact from the current contact
				pTemp = pCurr->link;

                // Takde case sensitive for first letter in the name
                // Exp, Lisa is same level as lisa
				strcpy_s(currContact, pCurr->name);
				strcpy_s(nextContact, pTemp->name);
				currContact[0] = toupper(currContact[0]);
				nextContact[0] = toupper(nextContact[0]);

                // If current contact larger than the next contact
                // Swapped
				if (strcmp(currContact, nextContact) < 0) {

					pTemp = pCurr->link;

                    // If index == 0, meaning now is comparing the first with the second contact
                    // Swapped between first and the second contact
					if (x == 0) {

						pHead = pTemp;

						pTemp->prev = pCurr->prev;

						if (pTemp->link != NULL) {
							pTemp->link->prev = pCurr;
						}

						pCurr->link = pTemp->link;
						pTemp->link = pCurr;
						pCurr->prev = pTemp;

						if (noContact == 2) {
							pTail = pCurr;
							break;
						}

					}
                    // If the index reach the second last contact
                    // Swapped between the second last and the last contact
					else if (x == noContact - 2) {

						pTail = pCurr;

						pCurr->link = pTemp->link;
						pCurr->prev->link = pTemp;
						pTemp->link = pCurr;
						pTemp->prev = pCurr->prev;
						pCurr->prev = pTemp;

					}
                    // If the index is in the middle of the contact list
                    // Swapped occur in the middle of the list
					else {

						pCurr->link = pTemp->link;
						pTemp->link->prev = pCurr;
						pCurr->prev->link = pTemp;
						pTemp->link = pCurr;
						pTemp->prev = pCurr->prev;
						pCurr->prev = pTemp;

					}

					swapped = true;

				}
                // If the current contact is not larger than the next contact
				else {
					pCurr = pTemp;
				}

			}

            // If swapped did not perform in one of the iteration
            // Like from first index to the last of that iteration did not perform at least 1 swapped
            // Then means the list already sorted well
            // Break the looping (Improve efficiency)
			if (swapped == false) {
				break;
			}

		}

	}
    
}

// Display specific contact lists (With birthday and ringtone)
void ContactList::displaySpecificContactList(char targetContact[]) {

    int indexLocation = 0;

    // Search for the contact and get the indexLocation
    if (traverse(indexLocation, targetContact) == true) {

        pCurr = pHead;

        // Check if the indexLocation of the contact is the first one
        // pCurr will point to the first contact (pHead)
        if (indexLocation == noContact - 1) {
            pCurr = pTail;
        }
        // Check if the indexLocation of the contact is in the middle of the list
        else if (indexLocation != 0) {

            // Using looping to find the contact based on the indexLocation
            for (int x = 0; x < indexLocation && pCurr->link != NULL; x++) {
                pCurr = pCurr->link;
            }

        }

        // For later display use
        string tempValuesContact[5] = { ": " + string(pCurr->name), ": " + string(pCurr->phone[0]), 
            ": " + string(pCurr->email), ": " + string(pCurr->ringtone), ": " + string(pCurr->birthday) };

        // Display all the details of the specific contact
        // Structure the design using setw and setfill
        cout << setw(120) << setfill('-') << left << "-" << endl << endl;
        cout << setw(30) << setfill(' ') << "Name" << tempValuesContact[0] << endl << endl;
        cout << setw(30) << setfill(' ') << "Phone" << setw(13) << setfill(' ') << tempValuesContact[1] << "   ";
        for (int x = 1; x < pCurr->noPhone; x++) {
            cout << setw(12) << setfill(' ') << pCurr->phone[x] << "  ";
        }
        cout << endl << endl;
        cout << setw(30) << setfill(' ') << "Email" << tempValuesContact[2] << endl << endl;
        cout << setw(30) << setfill(' ') << "Ringtone" << tempValuesContact[3] << endl << endl;
        cout << setw(30) << setfill(' ') << "Birthday" << tempValuesContact[4] << endl << endl;
        cout << setw(120) << setfill('-') << "-" << endl << endl;

    }
    // If target not found
    else {
        cout << "\nUnable to display target " << targetContact << " because contact not found" << endl << endl;
    }

}

// Display all the contacts in table form (Not include birthday and ringtone)
void ContactList::displayAllContactList() {

    pCurr = pHead;

    // Structure the header of the table
    cout << setw(120) << setfill('-') << left << "-" << endl;
    cout << setw(5) << setfill(' ') << "No";
    cout << setw(20) << setfill(' ') << "| Name";
    cout << setw(20) << setfill(' ') << "| email";
    cout << setw(30) << setfill(' ') << "| Phone" << endl;
    cout << setw(120) << setfill('-') << "-" << endl;

    cout << setw(5) << setfill(' ') << " ";
    cout << setw(20) << setfill(' ') << "|";
    cout << setw(20) << setfill(' ') << "|";
    cout << setw(30) << setfill(' ') << "|" << endl;

    // Structure the body of the table and display contact details
    for (int x = 0; x < noContact; x++) {
        string tempValuesContact[3] = { "| " + string(pCurr->name), "| " + string(pCurr->email), "| " + string(pCurr->phone[0]) };

        cout << setw(5) << setfill(' ') << x + 1;
        cout << setw(20) << setfill(' ') << tempValuesContact[0];
        cout << setw(20) << setfill(' ') << tempValuesContact[1];
        cout << setw(13) << setfill(' ') << tempValuesContact[2] << "   ";
        for (int i = 1; i < pCurr->noPhone; i++) {
            cout << setw(12) << setfill(' ') << pCurr->phone[i] << "  ";
        }
        if (pCurr->link != NULL) {
            pCurr = pCurr->link;
        }

        cout << endl << setw(5) << setfill(' ') << " ";
        cout << setw(20) << setfill(' ') << "|";
        cout << setw(20) << setfill(' ') << "|";
        cout << setw(30) << setfill(' ') << "|" << endl;
    }

    cout << setw(120) << setfill('-') << "-" << setfill(' ') << endl << endl;
    cout << "Total Number of Contacts: " << noContact << endl << endl;
    cout << setw(120) << setfill('-') << "-" << setfill(' ') << endl << endl;

}

// Display all the contacts follow the alphabet (Not include birthday and ringtone)
// Display only alphabet that available in the contact list
// Exp: If the list does not contain contact that start with 'c', then 'c' wont show
void ContactList::displayContactListFollowAlphabet() {

    // Before display, the contact will auto sorted to ascending order first
    char type[5] = "ASC";
    bubbleSort(type);

    pCurr = pHead;

    // Get the alphabet from the contact list
    for (int x = 0; x < noContact && pCurr->link != NULL; x++) {

        bool run = true;
        for (int x = 0; x < 26; x++) {

            // Array alphabetCapitalLetter initially storing the 26 alphabet
            // Check if the contact is match with which alphabet
            // Array trackAlphabet use to store all the alphabet that contact has
            if (alphabetCapitalLetter[x] == toupper(pCurr->name[0])) {

                run = true;

                // If there have several contact start with the same alphabet
                // The alphabet save only 1 time into trackAlphabet
                // So, this looping is to check if there is any redunduncy of alphabet stored
                for (int i = 0; i < noAlphabet; i++) {
                    if (trackAlphabet[i] == toupper(pCurr->name[0])) {
                        run = false;
                        break;
                    }
                }

                // If the alphabet of the contact is totally new one, which is not redundant
                // Then it will store in the trackAlphabet
                if (run == true) {
                    trackAlphabet[noAlphabet] = alphabetCapitalLetter[x];

                    // If a new alphabet come in, then noAlphabet will + 1
                    noAlphabet++;
                    break;
                }
            }
        }

        // Point to the next contact
        pCurr = pCurr->link;

    }
        
    // Loop to show the contact list and their details based on alphabet
    for (int x = 0; x < noAlphabet; x++) {

        // Control the header of the display
        int noItemForEachAlphabet = 0;
        pCurr = pHead;

        cout << "\n\n\nShowing Contact List of '" << trackAlphabet[x] << "' alphabet: " << endl << endl;
        cout << setw(120) << setfill('-') << left << "-" << endl;

        cout << setw(5) << setfill(' ') << "No";
        cout << setw(20) << setfill(' ') << "| Name";
        cout << setw(20) << setfill(' ') << "| email";
        cout << setw(30) << setfill(' ') << "| Phone" << endl;
        cout << setw(120) << setfill('-') << "-" << endl;

        cout << setw(5) << setfill(' ') << " ";
        cout << setw(20) << setfill(' ') << "|";
        cout << setw(20) << setfill(' ') << "|";
        cout << setw(30) << setfill(' ') << "|" << endl;

        // Control the details/ contacts of the display
        // Show only contact that match the alphabet
        for (int y = 0, z = 0; y < noContact; y++) {

            if (toupper(pCurr->name[0]) == trackAlphabet[x]) {

                string tempValuesContact[3] = { "| " + string(pCurr->name), "| " + string(pCurr->email), "| " + string(pCurr->phone[0]) };

                cout << setw(5) << setfill(' ') << z + 1;
                cout << setw(20) << setfill(' ') << tempValuesContact[0];
                cout << setw(20) << setfill(' ') << tempValuesContact[1];
                cout << setw(13) << setfill(' ') << tempValuesContact[2] << "   ";
                for (int i = 1; i < pCurr->noPhone; i++) {
                    cout << setw(12) << setfill(' ') << pCurr->phone[i] << "  ";
                }

                cout << endl << setw(5) << setfill(' ') << " ";
                cout << setw(20) << setfill(' ') << "|";
                cout << setw(20) << setfill(' ') << "|";
                cout << setw(30) << setfill(' ') << "|" << endl;

                z++;
                noItemForEachAlphabet++;

            }

            pCurr = pCurr->link;

        }

        cout << setw(120) << setfill('-') << "-" << setfill(' ') << endl << endl;
        cout << "Total Number of Contacts: " << noItemForEachAlphabet << endl << endl;
        cout << setw(120) << setfill('-') << "-" << setfill(' ') << endl << endl;

    }

}

// Private method (For repeat use by filter function)
// Show the header of the table list
void generalShowInFilter() {

    cout << setw(5) << setfill(' ') << "No";
    cout << setw(20) << setfill(' ') << "| Name";
    cout << setw(20) << setfill(' ') << "| email";
    cout << setw(30) << setfill(' ') << "| Phone" << endl;
    cout << setw(120) << setfill('-') << "-" << endl;

    cout << setw(5) << setfill(' ') << " ";
    cout << setw(20) << setfill(' ') << "|";
    cout << setw(20) << setfill(' ') << "|";
    cout << setw(30) << setfill(' ') << "|" << endl;

}

// Display contact details based on filter
// Can be filter by name/ phone/ email/ birthday/ ringtone
void ContactList::filterAndDisplayContactList(char filterType[], char thingFilter[]) {

    // Before display, the contact list auto sorted to ascending order first
    char sortingType[5] = "ASC";
    bubbleSort(sortingType);

    char extractWord[30] = { "\0" };

    // Get the length of the filter that user has input
    int thingFilterLength = strlen(thingFilter);
    
    // If user want to filter with name
    if (strcmp(filterType, "NAME") == 0) {

        cout << "\n\n\nShowing Contact List start with '" << thingFilter << "' from NAME: " << endl << endl;
        cout << setw(120) << setfill('-') << left << "-" << endl;

        int noItemForFilterList = 0;
        pCurr = pHead;

        // Show the header of the table list
        generalShowInFilter();
        
        // Loop the whole list
        for (int y = 0, z = 0; y < noContact; y++) {

            // Based on the filter user input, I get the length of the input just now
            // Now extract the name in the linkedlist follow the length
            // Exp: Chong, if user input filter 'ch' then length = 2, so 'Ch' from Chong will be extracted
            strncpy_s(extractWord, pCurr->name, thingFilterLength);

            // This is case sensitive
            // So, 'ch' is not same as 'Ch'
            if (strcmp(extractWord, thingFilter) == 0) {

                // Output all the details
                string tempValuesContact[3] = { "| " + string(pCurr->name), "| " + string(pCurr->email), "| " + string(pCurr->phone[0]) };

                cout << setw(5) << setfill(' ') << z + 1;
                cout << setw(20) << setfill(' ') << tempValuesContact[0];
                cout << setw(20) << setfill(' ') << tempValuesContact[1];
                cout << setw(13) << setfill(' ') << tempValuesContact[2] << "   ";
                for (int i = 1; i < pCurr->noPhone; i++) {
                    cout << setw(12) << setfill(' ') << pCurr->phone[i] << "  ";
                }

                cout << endl << setw(5) << setfill(' ') << " ";
                cout << setw(20) << setfill(' ') << "|";
                cout << setw(20) << setfill(' ') << "|";
                cout << setw(30) << setfill(' ') << "|" << endl;

                z++;
                noItemForFilterList++;

            }

            pCurr = pCurr->link;

        }

        cout << setw(120) << setfill('-') << "-" << setfill(' ') << endl << endl;
        cout << "Total Number of Contacts: " << noItemForFilterList << endl << endl;
        cout << setw(120) << setfill('-') << "-" << setfill(' ') << endl << endl;

    }
    // If user want to filter with phone
    else if (strcmp(filterType, "PHONE") == 0) {

        cout << "\n\n\nShowing Contact List start with '" << thingFilter << "' from PHONE: " << endl << endl;
        cout << setw(120) << setfill('-') << left << "-" << endl;

        int noItemForFilterList = 0;
        pCurr = pHead;

        // Show the header of the table list
        generalShowInFilter();

        // Loop the whole list
        for (int y = 0, z = 0; y < noContact; y++) {

            bool phoneTrack = false;

            // Looping is needed because each contact may have more than 1 phone number
            // Filter should perform for all the phone number
            for (int x = 0; x < pCurr->noPhone; x++) {

                // Now extract the phone in the linkedlist follow the length
                strncpy_s(extractWord, pCurr->phone[x], thingFilterLength);

                // Check if the extract phone is same as the filter phone
                // Once same, stop the looping
                if (strcmp(extractWord, thingFilter) == 0) {
                    phoneTrack = true;
                    break;
                }

            }

            // If the contact has a phone match with the filter input phone
            // The details of the contact will be display
            if (phoneTrack == true) {

                string tempValuesContact[3] = { "| " + string(pCurr->name), "| " + string(pCurr->email), "| " + string(pCurr->phone[0]) };

                cout << setw(5) << setfill(' ') << z + 1;
                cout << setw(20) << setfill(' ') << tempValuesContact[0];
                cout << setw(20) << setfill(' ') << tempValuesContact[1];
                cout << setw(13) << setfill(' ') << tempValuesContact[2] << "   ";
                for (int i = 1; i < pCurr->noPhone; i++) {
                    cout << setw(12) << setfill(' ') << pCurr->phone[i] << "  ";
                }

                cout << endl << setw(5) << setfill(' ') << " ";
                cout << setw(20) << setfill(' ') << "|";
                cout << setw(20) << setfill(' ') << "|";
                cout << setw(30) << setfill(' ') << "|" << endl;

                z++;
                noItemForFilterList++;

            }

            pCurr = pCurr->link;

        }

        cout << setw(120) << setfill('-') << "-" << setfill(' ') << endl << endl;
        cout << "Total Number of Contacts: " << noItemForFilterList << endl << endl;
        cout << setw(120) << setfill('-') << "-" << setfill(' ') << endl << endl;

    }
    // If user want to filter with email
    else if (strcmp(filterType, "EMAIL") == 0) {

        cout << "\n\n\nShowing Contact List start with '" << thingFilter << "' from EMAIL: " << endl << endl;
        cout << setw(120) << setfill('-') << left << "-" << endl;

        int noItemForFilterList = 0;
        pCurr = pHead;

        // Show the header of the table list
        generalShowInFilter();

        // Loop the whole list
        for (int y = 0, z = 0; y < noContact; y++) {

            // Now extract the email in the linkedlist follow the length
            strncpy_s(extractWord, pCurr->email, thingFilterLength);

            // Check if the extracted email is same as the filter input email by the user
            // Display all the contact that match email as the filter
            if (strcmp(extractWord, thingFilter) == 0) {

                string tempValuesContact[3] = { "| " + string(pCurr->name), "| " + string(pCurr->email), "| " + string(pCurr->phone[0]) };

                cout << setw(5) << setfill(' ') << z + 1;
                cout << setw(20) << setfill(' ') << tempValuesContact[0];
                cout << setw(20) << setfill(' ') << tempValuesContact[1];
                cout << setw(13) << setfill(' ') << tempValuesContact[2] << "   ";
                for (int i = 1; i < pCurr->noPhone; i++) {
                    cout << setw(12) << setfill(' ') << pCurr->phone[i] << "  ";
                }

                cout << endl << setw(5) << setfill(' ') << " ";
                cout << setw(20) << setfill(' ') << "|";
                cout << setw(20) << setfill(' ') << "|";
                cout << setw(30) << setfill(' ') << "|" << endl;

                z++;
                noItemForFilterList++;

            }

            pCurr = pCurr->link;

        }

        cout << setw(120) << setfill('-') << "-" << setfill(' ') << endl << endl;
        cout << "Total Number of Contacts: " << noItemForFilterList << endl << endl;
        cout << setw(120) << setfill('-') << "-" << setfill(' ') << endl << endl;

    }
    // If user want to filter with ringtone
    else if (strcmp(filterType, "RINGTONE") == 0) {

        cout << "\n\n\nShowing Contact List with '" << thingFilter << "' from RINGTONE: " << endl << endl;
        cout << setw(120) << setfill('-') << left << "-" << endl;

        int noItemForFilterList = 0;
        pCurr = pHead;

        // Show the header
        // Cannot use the general function above, because that does not include ringtone
        cout << setw(5) << setfill(' ') << "No";
        cout << setw(20) << setfill(' ') << "| Name";
        cout << setw(20) << setfill(' ') << "| RINGTONE";
        cout << setw(30) << setfill(' ') << "| Phone" << endl;
        cout << setw(120) << setfill('-') << "-" << endl;

        cout << setw(5) << setfill(' ') << " ";
        cout << setw(20) << setfill(' ') << "|";
        cout << setw(20) << setfill(' ') << "|";
        cout << setw(30) << setfill(' ') << "|" << endl;

        // Loop for whole contact list
        for (int y = 0, z = 0; y < noContact; y++) {

            // No need to extract anything because filter input is by number (Range from 1 to 15)
            // Display all the contact that match ringtone as the filter
            if (strcmp(pCurr->ringtone, thingFilter) == 0) {

                string tempValuesContact[3] = { "| " + string(pCurr->name), "| " + string(pCurr->ringtone), "| " + string(pCurr->phone[0]) };

                cout << setw(5) << setfill(' ') << z + 1;
                cout << setw(20) << setfill(' ') << tempValuesContact[0];
                cout << setw(20) << setfill(' ') << tempValuesContact[1];
                cout << setw(13) << setfill(' ') << tempValuesContact[2] << "   ";
                for (int i = 1; i < pCurr->noPhone; i++) {
                    cout << setw(12) << setfill(' ') << pCurr->phone[i] << "  ";
                }

                cout << endl << setw(5) << setfill(' ') << " ";
                cout << setw(20) << setfill(' ') << "|";
                cout << setw(20) << setfill(' ') << "|";
                cout << setw(30) << setfill(' ') << "|" << endl;

                z++;
                noItemForFilterList++;

            }

            pCurr = pCurr->link;

        }

        cout << setw(120) << setfill('-') << "-" << setfill(' ') << endl << endl;
        cout << "Total Number of Contacts: " << noItemForFilterList << endl << endl;
        cout << setw(120) << setfill('-') << "-" << setfill(' ') << endl << endl;

    }
    // If user want to filter with birthday
    else if (strcmp(filterType, "BIRTHDAY") == 0) {


        cout << "\n\n\nShowing Contact List with '" << thingFilter << "' from BIRTHDAY: " << endl << endl;
        cout << setw(120) << setfill('-') << left << "-" << endl;

        int noItemForFilterList = 0;
        pCurr = pHead;

        // Show the header
        // Cannot use the general function above, because that does not include birthday
        cout << setw(5) << setfill(' ') << "No";
        cout << setw(20) << setfill(' ') << "| Name";
        cout << setw(20) << setfill(' ') << "| BIRTHDAY";
        cout << setw(30) << setfill(' ') << "| Phone" << endl;
        cout << setw(120) << setfill('-') << "-" << endl;

        cout << setw(5) << setfill(' ') << " ";
        cout << setw(20) << setfill(' ') << "|";
        cout << setw(20) << setfill(' ') << "|";
        cout << setw(30) << setfill(' ') << "|" << endl;

        // Loop for whole contact list
        for (int y = 0, z = 0; y < noContact; y++) {

            // No need to extract anything because filter input is structured in main (day, month, and year)
            // Display all the contact that match birthday as the filter
            if (strcmp(pCurr->birthday, thingFilter) == 0) {

                string tempValuesContact[3] = { "| " + string(pCurr->name), "| " + string(pCurr->birthday), "| " + string(pCurr->phone[0]) };

                cout << setw(5) << setfill(' ') << z + 1;
                cout << setw(20) << setfill(' ') << tempValuesContact[0];
                cout << setw(20) << setfill(' ') << tempValuesContact[1];
                cout << setw(13) << setfill(' ') << tempValuesContact[2] << "   ";
                for (int i = 1; i < pCurr->noPhone; i++) {
                    cout << setw(12) << setfill(' ') << pCurr->phone[i] << "  ";
                }

                cout << endl << setw(5) << setfill(' ') << " ";
                cout << setw(20) << setfill(' ') << "|";
                cout << setw(20) << setfill(' ') << "|";
                cout << setw(30) << setfill(' ') << "|" << endl;

                z++;
                noItemForFilterList++;

            }

            pCurr = pCurr->link;

        }

        cout << setw(120) << setfill('-') << "-" << setfill(' ') << endl << endl;
        cout << "Total Number of Contacts: " << noItemForFilterList << endl << endl;
        cout << setw(120) << setfill('-') << "-" << setfill(' ') << endl << endl;

    }

}
