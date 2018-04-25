//
// Address Book
// By: Brandon Pope
// Date: 4/22/18 9:00 P.M.
// Due: 4/22/18 11:59 P.M.
//
// Description:
//  Program allows user to use a file to keep an address book. This address book can be
//  manipulated by the user in different ways. These include: displaying, editing, deleting, and searching the contacts.
//  Program utilizes an array of structures which handles the manipulations. Also, the program heavily employs the use
//  of switches to format the "Menu" style interface. The program also keeps the address book up to date by saving the 
//  contacts to an output file.
//
// Known Problems:
//  The main issues with this program involve exactness in the input from the user. I have attempted to remedy this by 
//  explicity stating formatting in the prompts to the user, but they're still able to input bad data and would need to 
//  use the editing function to fix it.
//
#include "addBook.h"
// Handles File Input, Main Menu Switch, and File Saving
int main(int argc, char **argv)
{
	bool importSuccess;
	int conCount = NUM_CONTACTS;
	Contact contacts[NUM_CONTACTS+100]; // Allows for up to 100 New Contacts to be added through the program +- deleted contacts.
	importSuccess = getContactInfo(contacts);
	if (importSuccess == false) {
		cout << "Error importing contact information. Exiting" << endl;
		exit(0);
	}
	mainMenu(contacts, conCount);
	updateContacts(contacts,conCount);
	return 0;
}
// Handles the Main Switch which acts as a menu for the program.
void mainMenu(Contact contacts[], int &conCount) { 
	int ans, searchType, ID;
	string keyword;
	bool keepGoing = true, isEdit;
	do {
		cout << "*** Address Book Main Menu ***" << endl;
		cout << "(1) Display Current Contacts" << endl;
		cout << "(2) Add New Contact" << endl;
		cout << "(3) Delete Contact" << endl;
		cout << "(4) Edit Contact" << endl;
		cout << "(5) Search Current Contacts" << endl;
		cout << "(6) Exit and Save Contacts" << endl;
		cin >> ans;
		switch(ans) {
			case 1 :
				isEdit = false;
				if (conCount == 0)
					cout << "No contacts currently stored in Address Book." << endl;
				else
					printContacts(contacts, conCount, isEdit);
				break;
			case 2 :
				cin.ignore();
				addContact(contacts, conCount);
				break;
			case 3 :
				if (conCount == 0)
					cout << "No contacts currently stored in Address Book." << endl;
				else
					deleteContact(contacts,ID,conCount);
				break;
			case 4 :
				isEdit = true;
				if (conCount == 0)
					cout << "No contacts currently stored in Address Book." << endl;
				else
					printContacts(contacts, conCount, isEdit);
				break;
			case 5 :
				cin.ignore();
				cout << "(1) First Name" << endl;
				cout << "(2) Last Name" << endl;
				cout << "(3) Address" << endl;
				cout << "(4) Phone Number" << endl;
				cout << "Enter Search Type: ";
				cin >> searchType;
				while (searchType <=0 || searchType > 4) {
					cout << "Invalid Input" << endl;
					cin >> searchType;
				}
				cin.ignore();
				cout << "Enter Keyword: ";
				getline(cin,keyword);
				searchContacts(contacts,keyword,searchType,conCount);
				break;
			case 6 :
				keepGoing = false;
				break;
			default :
				cout << "Invalid Input." << endl;
				break;
		}
	} while(keepGoing == true);
}
// Fills the Array of Structs with information given from file.
// Also sets the ID of each struct to its corresponding array index.
// If fails to open, returns false and closes the program.
bool getContactInfo(Contact contacts[]) {  
	ifstream inFile("contactinfo.dat");   
	if (!inFile.is_open())
		return (false);
	for (int i=0;i<NUM_CONTACTS;i++) {
		contacts[i].ID = i;
		getline(inFile, contacts[i].fName);
		getline(inFile, contacts[i].lName);
		getline(inFile, contacts[i].middle);
		getline(inFile, contacts[i].address1);
		getline(inFile, contacts[i].address2);
		getline(inFile, contacts[i].city);
		getline(inFile, contacts[i].stateName);
		inFile >> contacts[i].zipcode;
		inFile.ignore();
		getline(inFile, contacts[i].pNumber);
		getline(inFile, contacts[i].email);
	}
	inFile.close();
	return(true);
}
// Passed the array index of a selected contact and displays its detailed contact information.
void showContactInfo(Contact contacts[], int ID) {
	cout << endl << "Info for " << contacts[ID].fName << " " 
		 << contacts[ID].middle << " " << contacts[ID].lName << endl;
	cout << "Address 1      : " << contacts[ID].address1 << endl;
	cout << "Address 2      : " << contacts[ID].address2 << endl;
	cout << "City           : " << contacts[ID].city << endl;
	cout << "State          : " << contacts[ID].stateName << endl;
	cout << "ZipCode        : " << contacts[ID].zipcode << endl;
	cout << "Phone number   : " << contacts[ID].pNumber << endl;
	cout << "Email          : " << contacts[ID].email << endl;
	cout << endl;
}
// Prints all current Contacts in a Last, First format
void printContacts(Contact contacts[], int &conCount, bool isEdit) {
	for (int i=0;i<conCount;i++) {
		cout << "(" << i+1 << ") " << contacts[i].lName << ", " << contacts[i].fName
		 << " " << contacts[i].middle << endl;
	}
	contactDetails(contacts, conCount, isEdit);
}
// Calls editContactInfo or showContactInfo based on isEdit value.
void contactDetails(Contact contacts[], int &conCount, bool isEdit) {
	int x;
	if (isEdit == true) {
		cout << "Enter ID Number for Editing: ";
		cin >> x;
		while (x > conCount) {
			cout << "Please Enter Valid ID Number." << endl;
			cin >> x;
		}
		editContactInfo(contacts,x-1);
	}
	else {
		cout << "Enter ID Number for Detailed Information: ";
		cin >> x;
		while (x > conCount) {
		cout << "Please Enter Valid ID Number." << endl;
		cin >> x;
		}
		showContactInfo(contacts,x-1);
	}
}
// Fills the next empty index with information gathererd from the user.
void addContact(Contact contacts[], int &conCount) {
		contacts[conCount].ID = conCount;
		cout << "Enter First Name: ";
		getline(cin, contacts[conCount].fName);
		cout << "Enter Last Name: ";
		getline(cin, contacts[conCount].lName);
		cout << "Enter Middle Initial: ";
		getline(cin, contacts[conCount].middle);
		cout << "Enter Address: ";
		getline(cin, contacts[conCount].address1);
		cout << "Enter Secondary Address (If none enter '----'): ";
		getline(cin, contacts[conCount].address2);
		cout << "Enter City: ";
		getline(cin, contacts[conCount].city);
		cout << "Enter State (Full Name): ";
		getline(cin, contacts[conCount].stateName);
		cout << "Enter Zip Code: ";
		cin >> contacts[conCount].zipcode;
		cin.ignore();
		cout << "Enter Phone Number (Please enter using the format (123)456-7890): ";
		getline(cin, contacts[conCount].pNumber);
		cout << "Enter Email Address: ";
		getline(cin, contacts[conCount].email);
		conCount++;
}
// Called at the end of main. Loops through each index and saves to a file.
void updateContacts(Contact contacts[], int &conCount) {
	ofstream outFile("UpdatedContacts.dat");
	for (int i=0;i<conCount;i++) {
		outFile << contacts[i].fName << endl;
		outFile << contacts[i].lName << endl;
		outFile << contacts[i].middle << endl;
		outFile << contacts[i].address1 << endl;
		outFile << contacts[i].address2 << endl;
		outFile << contacts[i].city << endl;
		outFile << contacts[i].stateName << endl;
		outFile << contacts[i].zipcode << endl;
		outFile << contacts[i].pNumber << endl;
		outFile << contacts[i].email << endl;
	}
	outFile.close();
}
// Displays Selected Contact's Information. Allows user to select fields and edit them until finished.
void editContactInfo(Contact contacts[], int ID) {
	cout << "(1)First Name         : " << contacts[ID].fName << endl;
	cout << "(2)Last Name          : " << contacts[ID].lName << endl;
	cout << "(3)Middle Initial     : " << contacts[ID].middle << endl;
	cout << "(4)Address 1          : " << contacts[ID].address1 << endl;
	cout << "(5)Address 2          : " << contacts[ID].address2 << endl;
	cout << "(6)City               : " << contacts[ID].city << endl;
	cout << "(7)State              : " << contacts[ID].stateName << endl;
	cout << "(8)ZipCode            : " << contacts[ID].zipcode << endl;
	cout << "(9)Phone number       : " << contacts[ID].pNumber << endl;
	cout << "(10)Email             : " << contacts[ID].email << endl;
	int ans;
	bool keepEditing = true;
	do {
		cout << "Enter Field Number to Edit or Enter a 0 to Return to Main Menu: ";
		cin >> ans;
		switch(ans) {
			case 0 :
				keepEditing = false;
				break;
			case 1 :
				cout << "Edit First Name: ";
				cin >> contacts[ID].fName;
				break;
			case 2 :
				cout << "Edit Last Name: ";
				cin >> contacts[ID].lName;
				break;
			case 3 :
				cout << "Edit Middle Initial: ";
				cin >> contacts[ID].middle;
				break;
			case 4 :
				cout << "Edit Address 1: ";
				cin >> contacts[ID].address1;
				break;
			case 5 :
				cout << "Edit Secondary Address: ";
				cin >> contacts[ID].address2;
				break;
			case 6 :
				cout << "Edit City: ";
				cin >> contacts[ID].city;
				break;
			case 7 :
				cout << "Edit State: ";
				cin >> contacts[ID].stateName;
				break;
			case 8 :
				cout << "Edit Zip Code: ";
				cin >> contacts[ID].zipcode;
				break;
			case 9 :
				cout << "Edit Phone Number: ";
				cin >> contacts[ID].pNumber;
				break;
			case 10 :
				cout << "Edit Email: ";
				cin >> contacts[ID].email;
				break;
			default :
				cout << "Invalid Input.";
				break;
		}
	} while(keepEditing == true);
}
// Passed a keyword and a search type(Phone, Address, Last or First Name). 
// Prints out any contacts that match and allows their detailed information to be displayed.
void searchContacts(Contact contacts[], string keyword, int searchType, int conCount) {
	int index = 0;
	cout << "Search result found: " << endl;
	switch (searchType) {
		case 1 :
			for (int i=0; i<conCount;i++) {
				if (keyword == contacts[i].fName) {
					cout << "(" << contacts[i].ID+1 << ") " << contacts[i].lName << ", " << contacts[i].fName
						 << " " << contacts[i].middle << endl;
					index--;
				}
				else
					index++;
			}
			if (index == conCount)
			cout << "No contacts found matching keyword." << endl;
			else {
				cout << "Enter ID Number for Detailed Information: ";
				cin >> index;
				while (index > conCount || index <= 0) {
					cin.ignore();
					cout << "Invalid ID Number. Retry. ";
					cin >> index;
				}
				showContactInfo(contacts,index-1);
			}
		case 2 :
			for (int i=0; i<conCount;i++) {
				if (keyword == contacts[i].lName) {
					cout << "(" << contacts[i].ID+1 << ") " << contacts[i].lName << ", " << contacts[i].fName
						 << " " << contacts[i].middle << endl;
					index--;
				}
				else
					index++;
			}
			if (index == conCount)
			cout << "No contacts found matching keyword." << endl;
			else {
				cout << "Enter ID Number for Detailed Information: ";
				cin >> index;
				while (index > conCount || index <= 0) {
					cin.ignore();
					cout << "Invalid ID Number. Retry. ";
					cin >> index;
				}
				showContactInfo(contacts,index-1);
			}
		case 3 :
			for (int i=0; i<conCount;i++) {
				if (keyword == contacts[i].address1) {
					cout << "(" << contacts[i].ID+1 << ") " << contacts[i].lName << ", " << contacts[i].fName
						 << " " << contacts[i].middle << endl;
					index--;
				}
				else
					index++;
			}
			if (index == conCount)
			cout << "No contacts found matching keyword." << endl;
			else {
				cout << "Enter ID Number for Detailed Information: ";
				cin >> index;
				while (index > conCount || index <= 0) {
					cin.ignore();
					cout << "Invalid ID Number. Retry. ";
					cin >> index;
				}
				showContactInfo(contacts,index-1);
			}
		case 4 :
			for (int i=0; i<conCount;i++) {
				if (keyword == contacts[i].pNumber) {
					cout << "(" << contacts[i].ID+1 << ") " << contacts[i].lName << ", " << contacts[i].fName
						 << " " << contacts[i].middle << endl;
					index--;
				}
				else
					index++;
			}
			if (index == conCount)
			cout << "No contacts found matching keyword." << endl;
			else {
				cout << "Enter ID Number for Detailed Information: ";
				cin >> index;
				while (index > conCount || index <= 0) {
					cin.ignore();
					cout << "Invalid ID Number. Retry. ";
					cin >> index;
				}
				showContactInfo(contacts,index-1);
			}
	}
}
// Deletes a contact based on user input. Calls swap to move down above indexes to replace deleted index.
void deleteContact(Contact contacts[], int ID, int &conCount) {
	for (int i=0;i<conCount;i++) {
		cout << "(" << i+1 << ") " << contacts[i].lName << ", " << contacts[i].fName
		 << " " << contacts[i].middle << endl;
	}
	int x;
	int y;
	cout << "Enter ID Number for Deletion: ";
	cin >> x;
	while (x > conCount) {
		cout << "Please Enter Valid ID Number." << endl;
		cin >> x;
	}
	ID = x-1;
	cout << "Are you sure you want to delete " << contacts[ID].lName << ", " << contacts[ID].fName
		 << " " << contacts[ID].middle << " (1 for Yes, 2 for No)" << endl;
	cin >> y;
	while (y <= 0 || y > 2) {
		cout << "Invalid input. Please answer with 1 for Yes or 2 for No... ";
		cin >> y;
	}
	if (y == 1) {
		swap(contacts,ID,conCount);
	}
}
// Called by deleteContact
void swap(Contact contacts[], int ID, int &conCount) {
	Contact temp[NUM_CONTACTS+10];
	for (int i=0;i<conCount;i++)
		temp[i] = contacts[i];
	for (int i = ID; i < conCount; i++)
		contacts[i] = temp[i+1];
	conCount--;
}
