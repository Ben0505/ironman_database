// 22C_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

#include "BinarySearchTree.h"
#include "Hash.h"
#include "List.h"

using namespace std;

// Type of BST
typedef BinarySearchTree TreeType;

// FUNCTIONS PROTOTYPE

/* Hash functions */
void insertHashManager(Hash& H);
void deleteHashManager(Hash& H);
void searchHashManager(Hash& H, void visit(Armors*));
void inputValid(string& returnItem);
void hashInput(string filename, Hash& H);
void printTree(TreeType& bstp, TreeType& bsts);

/* reading file and building BST */
void fileInput(string filename, TreeType& bstp, TreeType& bsts);	// read data from txt file and insert to tree

/* menus & sub-menus */
void menu();
void searchSubmenu(TreeType& bstp, TreeType& bsts);		// show search sub-menu when user choose to search
void listSubmenu(TreeType& bstp, TreeType& bst);		// show list sub-menu when user choose to print list
void processChoice(TreeType& bstp, TreeType& bsts);		// this will execute which menu options that the user choose
string inputKey();	// prompt user to enter key for menu & submenu

/* insert and delete data from tree */
void insertToTree(TreeType& bstp, TreeType& bsts);	// ADD data
void delData(TreeType& bstp, TreeType& bsts);		// DELETE data

/* SEARCH data */
void searchBSTp(TreeType& bstp, TreeType& bsts);	// by primary key
void searchBSTs(TreeType& bstp, TreeType& bsts);	// by secondary key

/* print LIST functions */
void listUnsorted(TreeType& bstp, TreeType& bsts);			// print unsorted list
void listByPriKey(TreeType& bstp, TreeType& bsts);			// print list, sorted by primary key
//void listBySec(TreeType& bstp, TreeType& bsts);			// print list, sorted by secondary key
void breadthTraversal(TreeType& bstp, TreeType& bsts);		// print all armors codename with its type by breadth order
void preOrderTraversal(TreeType& bstp, TreeType& bsts);		// print all armors codename with its type by pre-order
void inOrderTraversal(TreeType& bstp, TreeType& bsts);		// print all armors codename with its type by in-order
void postOrderTraversal(TreeType& bstp, TreeType& bsts);	// print all armors codename with its type by post-order


/* display function to pass to BST print function */

//void display(Armors* item)
//{
//	cout << item << endl;
//}

void display(Armors* a) {
	cout << "I am in display func\n";
	cout << a->getCodename() << " " << a->getYear() << endl;
	cout << "--------------------------------------------------------------------------" << endl;
	cout << a->getCodename() << ":" << a->getArmorType() << "\nMade by: " << a->getCreator() << " in " << a->getYear()
		<< "\nUsers: " << a->getUser() << ", appeared in: " << a->getMovie() << "\nCurrent Status: " << a->getStatus()
		<< "\nArmor Capabilities: " << a->getCap() << "\nWeapons: " << a->getWeapon()
		<< "\nPrecede: " << a->getPre() << "\tSucceed: " << a->getSuc();
	cout << "\n--------------------------------------------------------------------------" << endl;
}

/*****************************************************************
void displayCodenames(Armors* item):
	display the armor codenames with its type
*****************************************************************/
void displayCodenames(Armors* item)
{
	cout << right << setw(20) << item->getCodename() << " -" << item->getArmorType() << endl ;
}

/*****************************************************************
void displayTree(Armors* item, int level):
	print tree with indent depending on the level
*****************************************************************/
void displayTree(Armors* item, int level)
{
	// print 'level'  TABs to make indention
	for (int i = 0; i < level; ++i)
	{
		cout << "\t";
	}
	cout << "Level " << level + 1 << ". " << item << endl;
}

int main()
{
	const char inputFileName[] = "armors.txt";

	TreeType bstP;
	TreeType bstS;
	fileInput(inputFileName, bstP, bstS);

	menu();
	processChoice(bstP, bstS);

	Hash H(79);
	hashInput(inputFileName, H);
	H.stat();
	insertHashManager(H);
	searchHashManager(H, display);
	deleteHashManager(H);
	H.printHash(display);
	
}

void insertHashManager(Hash& H) {
	string targetName = "";
	Armors* A = new Armors;
	Armors* A2 = new Armors;
	A2->setCodename("");

	cout << "\n Insert\n";
	cout << "=======\n";

	while (A2->getCodename() != "Q")
	{
		cout << endl << "Enter an armor name to insert (or Q for stop inserting):";
		getline(cin, targetName);
		A2->setCodename(targetName);
		cout << endl;
		if (A2->getCodename() != "Q")
		{
			if (H.searchHash(A2, A))
				cout << "Armor " << targetName << " is already in this Hash Table.";
			else {
				cout << "Enter the information of the Armor" << endl;
				A->setCodename(targetName);
				getline(cin, A);
				if (H.insertItem(A))
					cout << "\nInserted" << endl;
			}
		}
	}
	cout << endl;
	cout << "___________________END INSERT SECTION _____\n";
}

void deleteHashManager(Hash& H) {
	string targetName = "";
	int n = 0;

	cout << "\n Delete\n";
	cout << "=======\n";

	while (targetName != "Q")
	{
		cout << endl << "Enter an armor name for delete (or Q for stop searching): ";
		getline(cin, targetName);

		if (targetName != "Q")
		{
			if (H.deleteItem(targetName))
				cout << "Deleted\n";
			else
				cout << "Armor " << targetName << " was not found in this Hash Table." << endl;
		}
	}
	cout << "___________________END DELETE SECTION_____\n";
}

void searchHashManager(Hash& H, void visit(Armors*)) {
	string key = "";
	string sKey = "";
	Armors* A;
	Armors* A2;
	A = new Armors;
	A2 = new Armors;
	cout << "\n Search\n";
	cout << "=======\n";
	do
	{
		cout << "\nEnter a primary key for search (or Q for stop searching): ";
		getline(cin, key);
		if (!cin.good())
			inputValid(key);
		A2->setCodename(key);
		cout << endl;
		if (A2->getCodename() != "Q") {
			if (!H.searchHash(A2, A))
				cout << "Armor " << key << " was not found in this Hash Table.\n";
			else
				visit(A);
		}
	} while (key != "Q");

	cout << endl;
	cout << "___________________END SEARCH SECTION _____\n";

}

void inputValid(string& returnItem) {
	string val;
	do {
		cout << "Your input is invalid\n" << "Please input integer to search\n";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		getline(cin, val);
	} while (!cin.good());
	returnItem = val;
}

void hashInput(string filename, Hash& H)
{
	ifstream infile(filename);

	string codename, type, creator, movie, curstat, precede, succeed, users, capbl, weap, space;
	int year = 0;

	if (!infile) {
		cout << "Error happened to open the input file!" << endl;
		exit(EXIT_FAILURE);
	}

	// READING THE FILE AND DECLARE TO RESPECTICE VARIABLE 
	//======================================================

	while (getline(infile, codename, ';'))
	{
		getline(infile, type, ';');
		getline(infile, creator, ';');
		infile >> year;
		infile.ignore();
		getline(infile, users, ';');
		getline(infile, movie, ';');
		getline(infile, curstat, ';');
		getline(infile, capbl, ';');
		getline(infile, weap, ';');
		getline(infile, precede, ';');
		getline(infile, succeed, ';');


		Armors* armors;
		armors = new Armors(codename, type, creator, year, users, movie, curstat, capbl, weap, precede, succeed);
		H.insertItem(armors);
		cout << "Inserted\n";
		getline(infile, space);
	}
	infile.close();
}

/**********************************************************************
BUILD BST
void fileInput(string filename, TreeType& bstp, TreeType& bsts):
	this function will read data from txt file and insert the data
	into the 2 BST (primary key & secondary key)

	Input Parameter: the 2 BST to build BST
**********************************************************************/
void fileInput(string filename, TreeType& bstp, TreeType& bsts)
{
	ifstream infile(filename);

	string codename, type, creator, movie, curstat, precede, succeed, users, capbl, weap;
	int year = 0;

	if (!infile) {
		cout << "Error happened to open the input file!" << endl;
		exit(EXIT_FAILURE);
	}
	
	// READING THE FILE AND DECLARE TO RESPECTICE VARIABLE
	while (getline(infile, codename, ';'))
	{
		getline(infile, type, ';');
		getline(infile, creator, ';');
		infile >> year;
		infile.ignore();
		getline(infile, users, ';');
		getline(infile, movie, ';');
		getline(infile, curstat, ';');
		getline(infile, capbl, ';');
		getline(infile, weap, ';');
		getline(infile, precede, ';');
		getline(infile, succeed, ';');
		infile.ignore();

		// TEST IF FILE IS READ PROPERLY
		/*
		cout << "======================================================" << endl;
		cout << "codename: " << codename << endl;
		cout << "type: " << type << endl;
		cout << "creator: " << creator << endl;
		cout << "year: " << year << endl;
		cout << "users: " << users << endl;
		cout << "movie: " << movie << endl;
		cout << "status: " << curstat << endl;
		cout << "capabilities: " << capbl << endl;
		cout << "weapons: " << weap << endl;
		cout << "precede: " << precede << endl;
		cout << "succeed: " << succeed << endl;
		cout << "======================================================" << endl << endl;
		*/
		
		// Building BST
		Armors* armors;
		armors = new Armors(codename, type, creator, year, users, movie, curstat, capbl, weap, precede, succeed);
		bstp.insert(armors);
		bsts.insertSec(armors);


	}
	infile.close();
}

/**********************************************************************
void menu():
	this will print the menu. layout of menu:
	
	1 : (A) ADD
	2 : (D) DELETE
	3 : (S) SEARCH :
		1 : (P)SEARCH by PRIMARY Key
		2 : (S)SEARCH by SECONDARY Key
		0 : Back to main menu
	4 : (L) LIST :
		1 : (U)LIST - Unsorted
		2 : (P)LIST - Sorted by PRIMARY Key
		3 : (S)LIST - Sorted by SECONDARY Key
		4 : (T)LIST - as a TREE
		5 : (0) LIST - Print LEVEL-ORDER
		6 : (1) LIST - Print PRE-ORDER
		7 : (2) LIST - Print IN-ORDER
		8 : (3) LIST - Print POST-ORDER
		0 : Basck to main menu
	0 : Quit

**********************************************************************/
void menu()
{
	cout << "                        MENU                        \n";
	cout << "======================================================" << endl;
	cout << "1 : Add armor" << endl;
	cout << "2 : Delete armor" << endl;
	cout << "3 : Search" << endl;
	cout << "4 : Show list" << endl;
	cout << "0 : Quit" << endl;
	cout << "------------------------------------------------------" << endl;
}

/**********************************************************************
void searchSubmenu(TreeType& bstp, TreeType& bsts):
	when the user choose to search, a sub-menu will be printed so
	the user can choose how they want to search it.
	It will keep prompting user for the choice if input is invalid

	Input Parameter: the 2 BST for recursion
**********************************************************************/
void searchSubmenu(TreeType& bstp, TreeType& bsts)
{
	int y = -1;
	cout << "Search by:" << endl;
	cout << "------------" << endl;
	cout << "1 : Primary Key " << endl;
	cout << "2 : Secondary Key " << endl;
	cout << "0 : Back to main menu " << endl;
	cout << "User choice: ";
	cin >> y;
	cin.ignore();
	cout << endl;

	switch (y)
	{
	case 1: // search by primary key function
		searchBSTp(bstp, bsts);
		break;
	case 2: // search by secondary key function
		searchBSTs(bstp, bsts);
		break;
	case 0: menu();
		processChoice(bstp, bsts);
		break;
	default: 
		cout << "--------------------" << endl;
		cout << "   INPUT INVALID.   " << endl;
		cout << "--------------------" << endl;
		searchSubmenu(bstp, bsts);
	}
}

/**********************************************************************
void listSubmenu(TreeType& bstp, TreeType& bsts):
	when the user choose to print list, a sub-menu will be printed so
	the user can choose which order they want to see
	It will keep prompting user for the choice if input is invalid

	Input Parameter: the 2 BST for recursion
**********************************************************************/
void listSubmenu(TreeType& bstp, TreeType& bsts)
{
	int y = -1;
	cout << "List as:" << endl;
	cout << "------------" << endl;
	cout << "1 : Unsorted " << endl;
	cout << "2 : Primary Key " << endl;
	cout << "3 : Secondary Key " << endl;
	cout << "4 : Tree " << endl;
	cout << "5 : Level-order " << endl;
	cout << "6 : Pre-order " << endl;
	cout << "7 : In-order " << endl;
	cout << "8 : Post-order " << endl;
	cout << "0 : Back to main menu " << endl;
	cout << "User choice: ";
	cin >> y;
	cin.ignore();
	cout << endl;

	switch (y)
	{
	case 1: // unsorted list
		break;
	case 2: // lsit sorted by primary key
		listByPriKey(bstp, bsts);
		break;
	case 3: // list sorted by secondary key
		// listBySec(bstp, bsts); // not working yet
		break;
	case 4: // list printed as tree
		//printTree(bst);
		break;
	case 5: // list printed as level-order
		breadthTraversal(bstp, bsts);
		break;
	case 6: // list printed as pre-order
		preOrderTraversal(bstp, bsts);
		break;
	case 7: // list printed as in-order
		inOrderTraversal(bstp, bsts);
		break;
	case 8: // list printed as post-order
		postOrderTraversal(bstp, bsts);
		break;
	case 0: menu();
		processChoice(bstp, bsts);
		break;
	default: 
		cout << "--------------------" << endl;
		cout << "   INPUT INVALID.   " << endl;
		cout << "--------------------" << endl;
		listSubmenu(bstp, bsts);
	}

}


/**********************************************************************
void processChoice(TreeType& bstp, TreeType& bsts):
	Prompt user to choose the menu and execute their choice.
	It will keep prompting user if input is invalid
	
	Input Parameter: the 2 BST for recursion
**********************************************************************/
void processChoice(TreeType& bstp, TreeType& bsts)
{
	int x = 0;
	cout << "User input: ";
	cin >> x;
	cin.ignore();
	cout << endl;

	switch (x)
	{
	case 1: // add function
		insertToTree(bstp, bsts);
		break;
	case 2: // delete function
		delData(bstp, bsts);
		break;
	case 3:
		searchSubmenu(bstp, bsts);
		break;
	case 4:
		listSubmenu(bstp, bsts);
		break;
	case 0: cout << "Program ended" << endl;
		exit(EXIT_FAILURE);
	default:
		cout << "--------------------" << endl;
		cout << "   INPUT INVALID.   " << endl;
		cout << "--------------------" << endl;
		processChoice(bstp, bsts);
	}
}

/**********************************************************************
string inputKey():
	Prompt user to input a string and return the string.
**********************************************************************/
string inputKey()
{
	string key;
	cout << "Input a key ('0' - main menu) : ";
	getline(cin, key);
	return key;
}

/**********************************************************************
ADD
void insertToTree(TreeType& bstp, TreeType& bsts):
	When the user choose to add data, it will prompt the user
	to input all the variable into an object and then insert it into
	the 2 BST.
	If the codename that the user input already exist, it will reject
	the insertion and it will go back to main menu

	Input Parameter: the 2 BST for insertion
**********************************************************************/
void insertToTree(TreeType& bstp, TreeType& bsts)
{
	Armors* A1;
	A1 = new Armors;
	Armors* A2;
	A2 = new Armors;
	A2->setCodename("");

	string codename = "", armorType = "", creator = "", users = "", movieAppeared = "", 
		currStats = "", capabilities = "", weapons = "", precede = "", succeed = "";
	int	yearMade = 0;

	cout << "\n                     INSERT                         \n";
	cout << "======================================================\n";
	cout << "       Codename: ";	getline(cin, codename);


	A2->setCodename(codename);
	if (bstp.getEntry(A2, A1))
	{
		cout << codename << " already in the system." << endl;
		menu();
		processChoice(bstp, bsts);
	}
	else {	
		cout << "      Armor type: ";	getline(cin, armorType);
		cout << "         Creator: ";	getline(cin, creator);
		cout << "       Year made: ";	cin >> yearMade;
		cin.ignore();
		cout << "           Users: ";		getline(cin, users);
		cout << "  Movie appeared: ";	getline(cin, movieAppeared);
		cout << " Currrent Status: ";	getline(cin, currStats);
		cout << "    Capabilities: ";	getline(cin, capabilities);
		cout << "         Weapons: ";	getline(cin, weapons);
		cout << "         Precede: ";	getline(cin, precede);
		cout << "         Succeed: ";	getline(cin, succeed);
		cout << "------------------------------------------------------\n";

		Armors* A;
		A = new Armors(codename, armorType, creator, yearMade, users, movieAppeared, currStats, capabilities, weapons, precede, succeed);
		bstp.insert(A);
		bsts.insertSec(A);

		cout << "                INSERTION COMPLETE                    " << endl;

		// Write to file
		/*
		ofstream outFile;
		outFile.open("armors.txt", ios::app);

		outFile << codename << ';' << armorType << ';' << creator << ';' << yearMade << ";" << users << ';' << movieAppeared << ';' << currStats << ';' << capabilities << ";" << weapons << ";" << precede << ";" << succeed << endl;
		outFile.close();


		while (codename != "Q")
		{
			if (codename != "Q")
			{
				if (bst.getEntry1(codename, A))
				{
					cout << "Armor already exist." << endl;
				}
				else
				{
					getline(cin, A);
					bst.insert(A);
				}
			}
		}*/
	}

	menu();
	processChoice(bstp, bsts);
}

/**********************************************************************
SEARCH by PRIMARY key
void searchBSTp(TreeType& bstp, TreeType& bsts):
	When user choose to search by primary key, it will prompt
	the user to enter the codename.
	If it exist, it will print out the data.
	if it's not it will show that it's not found.

	When the user choose to add data, it will prompt the user
	to input all the variable into an object and then insert it into
	the 2 BST.
	If the codename that the user input already exist, it will reject
	the insertion and it will go back to main menu

	Input Parameter: the 2 BST for recursion
**********************************************************************/
void searchBSTp(TreeType& bstp, TreeType& bsts)
{
	string key = "";

	Armors* A1;
	A1 = new Armors;
	Armors* A2;
	A2 = new Armors;
	A2->setCodename("");

	
	cout << "Search by PRIMARY key:" << endl;
	key = inputKey();
	A2->setCodename(key);
	if (A2->getCodename() != "0") {
		if (bstp.getEntry(A2, A1))
		{
			display(A1);
			searchBSTp(bstp, bsts);
		}
		else {
			cout << key << " not found." << endl;
			searchBSTp(bstp, bsts);
		}
	}
	else { cout << endl; menu(); processChoice(bstp, bsts); }



}

// Search for secondary key
void searchBSTs(TreeType& bstp, TreeType& bsts)
{
	string key = "";

	Armors* A1;
	A1 = new Armors;
	Armors* A2;
	A2 = new Armors;
	A2->setCodename("");

	
	cout << "Search by SECONDARY key:" << endl;
	key = inputKey();
	A2->setArmorType(key);
	if (A2->getArmorType() != "0") {
		if (bstp.getEntrySec(A2, A1, display))
		{
			// FOUND!
			searchBSTs(bstp, bsts);
		}
		else {
			cout << "NOT FOUND." << endl;
			searchBSTs(bstp, bsts);
		}
	}
	else { menu(); processChoice(bstp, bsts); }


}

///**********************************************************************
// delData: 
//	delete data based on the codename that the user input.
// **********************************************************************/
void delData(TreeType& bstp, TreeType& bsts)
{
	string key = "";

	Armors* A1;
	A1 = new Armors;

	cout << "Delete data: ";
	cout << "\n                             DELETE                                    \n";
	cout << "===========================================================================" << endl;
	bstp.inOrder(displayCodenames);
	cout << "---------------------------------------------------------------------------" << endl;
	
	key = inputKey();
	A1->setCodename(key);

	if (key == "0")
	{
		cout << endl;
		menu();
		processChoice(bstp, bsts);
	}

	if (bstp.remove(A1) == true && bsts.remove(A1) == true)
	{
		cout << key << " removed. \n\n";
		menu();
		processChoice(bstp, bsts);
	}
	else {
		cout << key << " doesn't exists." << endl;
		menu();
		processChoice(bstp, bsts);
	}

}

void listUnsorted(TreeType& bstp, TreeType& bsts)
{
	cout << "UNSORTED:" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	bstp.preOrder(displayCodenames);
	cout << "---------------------------------------------------------------------------" << endl << endl;
	menu(); processChoice(bstp, bsts);
}

void listByPriKey(TreeType& bstp, TreeType& bsts)
{
	cout << "By PRIMARY Key:" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	bstp.inOrder(displayCodenames);
	cout << "---------------------------------------------------------------------------" << endl << endl;
	menu(); processChoice(bstp, bsts);
}

void listBySec(TreeType& bstp, TreeType& bsts)
{
	cout << "By SECONDARY Key:" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	// bsts
	cout << "---------------------------------------------------------------------------" << endl << endl;
	menu(); processChoice(bstp, bsts);
}

void breadthTraversal(TreeType& bstp, TreeType& bsts)
{
	cout << "LEVEL-ORDER:" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	bstp._breadthF(displayCodenames);
	cout << "---------------------------------------------------------------------------" << endl << endl;
	menu(); processChoice(bstp, bsts);
}

void preOrderTraversal(TreeType& bstp, TreeType& bsts)
{
	cout << "PRE-ORDER:" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	bstp.preOrder(displayCodenames);
	cout << "---------------------------------------------------------------------------" << endl << endl;
	menu(); processChoice(bstp, bsts);
}

void inOrderTraversal(TreeType& bstp, TreeType& bsts)
{
	cout << "IN-ORDER:" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	bstp.inOrder(displayCodenames);
	cout << "---------------------------------------------------------------------------" << endl << endl;
	menu(); processChoice(bstp, bsts);
}

void postOrderTraversal(TreeType& bstp, TreeType& bsts)
{
	cout << "POST-ORDER:" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	bstp.postOrder(displayCodenames);
	cout << "---------------------------------------------------------------------------" << endl << endl;
	menu(); processChoice(bstp, bsts);
}

//
//void printTree(TreeType& bst)
//{
//	bst.printTree(displayTree);
//}



