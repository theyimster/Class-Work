#include <iostream>
#include <fstream>
#include <cstdlib>
#include <locale>
using namespace std;
#define NUM_CONTACTS 5

struct Contact {
	int ID;
	string fName, lName, middle;
	string address1, address2, city, stateName;
	int zipcode;
	string pNumber, email;
};

void mainMenu(Contact contacts[], int &conCount);
bool getContactInfo(Contact contacts[]);
void showContactInfo(Contact contacts[], int ID);
void printContacts(Contact contacts[], int &conCount, bool isEdit);
void contactDetails(Contact contacts[], int &conCount, bool isEdit);
void addContact(Contact contacts[], int &conCount);
void updateContacts(Contact contacts[], int &conCount);
void editContactInfo(Contact contacts[], int ID);
void searchContacts(Contact contacts[], string keyword, int searchType, int conCount);
void deleteContact(Contact contacts[], int ID, int &conCount);
void swap(Contact contacts[], int ID, int &conCount);