// 22C_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "BinarySearchTree.h"

using namespace std;

// Type of BST
typedef BinarySearchTree TreeType;

// FUNCTIONS PROTOTYPE
// menus
void menu();
void searchSubmenu(TreeType& bst);
void listSubmenu(TreeType& bst);
void processChoice(TreeType& bst);

string inputKey();
void insertToTree(TreeType& bst);	// ADD
void delData(TreeType& bst);

// search
void searchBST(TreeType& bst);

// print list
//void preOrderTraversal(TreeType& bst);
//void inOrderTraversal(TreeType& bst);
//void postOrderTraversal(TreeType& bst);
//void breadthTraversal(TreeType& bst);
//void printTree(TreeType& bst);

void fileInput(string filename, TreeType& bst);


void screenOutput();

// display function to pass to BST print function
void display(Armors* item)
{
	cout << item << endl;
}
//void displayTree(Armors* item, int level)
//{
//	// print 'level'  TABs to make indention
//	for (int i = 0; i < level; ++i)
//	{
//		cout << "\t";
//	}
//	cout << "Level " << level + 1 << ". " << item << endl;
//}


int main()
{
	const char inputFileName[] = "armors.txt";

	//TreeType* bstP = 0;
	TreeType bstP;
	TreeType bstS;
	fileInput(inputFileName, bstP);
	fileInput(inputFileName, bstS);

	menu();
	processChoice(bstP);

	/*Hash H(1);
	H.insertItem(A);
	string del = "Sneaky";
	H.deleteItem(del);
	H.searchByP("Sneaky");
	H.stat();*/
	
}

void fileInput(string filename, TreeType& bst)
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
		bst.insert(armors);

	}
	infile.close();
}

void menu()
{
	/*
	1 : (A) ADD
	2 : (D) DELETE
	3 : (S) SEARCH :
		1 : (P)SEARCH by PRIMARY Key
		2 : (S)SEARCH by SECONDARY Key
	4 : (L) LIST :
		1 : (U)LIST - Unsorted
		2 : (P)LIST - Sorted by PRIMARY Key
		3 : (S)LIST - Sorted by SECONDARY Key
		4 : (T)LIST - as a TREE
		5 : (0) LIST - Print LEVEL-ORDER
		6 : (1) LIST - Print PRE-ORDER
		7 : (2) LIST - Print IN-ORDER
		8 : (3) LIST - Print POST-ORDER
	0 : Quit / Back to main menu
	*/

	cout << "MENU: " << endl;
	cout << "======================================================" << endl;
	cout << "1 : Add menu data" << endl;
	cout << "2 : Delete data" << endl;
	cout << "3 : Search" << endl;
	cout << "4 : Show list" << endl;
	cout << "0 : Quit" << endl;
	cout << "------------------------------------------------------" << endl;
}


void searchSubmenu(TreeType& bst)
{
	int y = -1;
	cout << "Search by:" << endl;
	cout << "------------" << endl;
	cout << "1 : Primary Key " << endl;
	cout << "2 : Secondary Key " << endl;
	cout << "0 : Back to menu " << endl;
	cout << "User choice: ";
	cin >> y;
	cin.ignore();
	cout << endl;

	switch (y)
	{
	case 1: // search by primary key function
		searchBST(bst);
		break;
	case 2: // search by secondary key function
		break;
	case 0: menu();
		processChoice(bst);
		break;
	default: 
		cout << "----------------" << endl;
		cout << " INPUT INVALID. " << endl;
		cout << "----------------" << endl;
		searchSubmenu(bst);
	}

}


void listSubmenu(TreeType& bst)
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
	cout << "0 : Back to menu " << endl;
	cout << "User choice: ";
	cin >> y;
	cin.ignore();
	cout << endl;

	switch (y)
	{
	case 1: // unsorted list
		break;
	case 2: // lsit sorted by primary key
		break;
	case 3: // list sorted by secondary key
		break;
	case 4: // list printed as tree
		//printTree(bst);
		break;
	case 5: // list printed as level-order
		//breadthTraversal(bst);
		break;
	case 6: // list printed as pre-order
		//preOrderTraversal(bst);
		break;
	case 7: // list printed as in-order
		//inOrderTraversal(bst);
		break;
	case 8: // list printed as post-order
		//postOrderTraversal(bst);
		break;
	case 0: menu();
		processChoice(bst);
		break;
	default: 
		cout << "----------------" << endl;
		cout << " INPUT INVALID. " << endl;
		cout << "----------------" << endl;
		listSubmenu(bst);
	}

}


/*****************************************************************
void processChoice(char choice, TreeType& bst):
processing user's choice and execute the function of the choice
*****************************************************************/
void processChoice(TreeType& bst)
{
	int x = 0;
	cout << "User input: ";
	cin >> x;
	cin.ignore();
	cout << endl;

	switch (x)
	{
	case 1: // add function
		insertToTree(bst);
		break;
	case 2: // delete function
		delData(bst);
		break;
	case 3:
		searchSubmenu(bst);
		break;
	case 4:
		listSubmenu(bst);
		break;
	case 0: cout << "Program ended" << endl;
		exit(EXIT_FAILURE);
	default:
		cout << "----------------" << endl;
		cout << " INPUT INVALID. " << endl;
		cout << "----------------" << endl;
		processChoice(bst);
	}
}


///**********************************************************************
// Insert manager: insert data of college by the user into the list
// Input Parameter: list
// **********************************************************************/
//void insertToTree(TreeType& bst)
//{
//	/*string codename = "";
//	
//
//	cout << "\n Insert Data \n";
//	cout << "===============\n";
//	cout << "Codename: ";
//
//	getline(cin, codename);
//	cout << endl;
//
//	Armors* A;
//	A = new Armors;
//
//	while (codename != "Q")
//	{
//		if (codename != "Q")
//		{
//			if (bst.getEntry1(codename, A))
//			{
//				cout << "Armor already exist." << endl;
//			}
//			else
//			{
//				getline(cin, A);
//				bst.insert(A);
//			}
//		}
//	}*/
//}
//
// input function
string inputKey()
{
	string key;
	cout << "Input a key: ";
	getline(cin, key);
	return key;
}


///**********************************************************************
// Insert manager: insert data of college by the user into the list
// Input Parameter: list
// **********************************************************************/
void insertToTree(TreeType& bst)
{
	string codename = "";
	string	armorType = "";
	string	creator = "";
	int	yearMade = 0;
	string	users = "";
	string	movieAppeared = "";
	string	currStats = "";
	string	capabilities = "";
	string	weapons = "";
	string	precede = "";
	string	succeed = "";

	cout << "\n Insert Data \n";
	cout << "===============\n";
	cout << "Codename: ";	getline(cin, codename);
	cout << "armorType: ";	getline(cin, armorType);
	cout << "creator: ";	getline(cin, creator);
	cout << "yearMade: ";	cin >> yearMade;
	cin.ignore();
	cout << "users: ";		getline(cin, users);
	cout << "movieAppeared: ";	getline(cin, movieAppeared);
	cout << "currStats: ";	getline(cin, currStats);
	cout << "capabilities: ";	getline(cin, capabilities);
	cout << "weapons: ";	getline(cin, weapons);
	cout << "precede: ";	getline(cin, precede);
	cout << "succeed: ";	getline(cin, succeed);

	Armors* A;
	A = new Armors(codename, armorType, creator, yearMade, users, movieAppeared, currStats, capabilities, weapons, precede, succeed);
	bst.insert(A);

	menu();
	processChoice(bst);
}


void searchBST(TreeType& bst)
{
	string key = "";

	Armors* A1;
	A1 = new Armors;
	Armors* A2;
	A2 = new Armors;
	A2->setCodename("");

	
	cout << "Search by:" << endl;
	key = inputKey();
	A2->setCodename(key);
	if (A2->getCodename() != "Q") {
		if (bst.getEntry(A2, A1))
		{
			// FOUND!
			searchBST(bst);
		}
		else {
			cout << "NOT FOUND." << endl;
			searchBST(bst);
		}
	}
	else { menu(); processChoice(bst); }


}

void delData(TreeType& bst)
{
	string key = "";

	Armors* A1;
	A1 = new Armors;
	A1->setCodename("");

	cout << "Delete data" << endl;
	key = inputKey();
	A1->setCodename(key);

	if (bst.remove(A1))
	{
		cout << key << " removed." << endl;
	}
	else {
		cout << key << " doesn't exists. \n\n";
		delData(bst);
	}

}


//void preOrderTraversal(TreeType* bst)
//{
//	cout << "---------------------------------------------" << endl;
//	cout << "Pre-order:" << endl;
//	bst->preOrder(display);
//	cout << "---------------------------------------------" << endl;
//}
//
//void inOrderTraversal(TreeType* bst)
//{
//	cout << "---------------------------------------------" << endl;
//	cout << "In-order:" << endl;
//	bst->inOrder(display);
//	cout << "---------------------------------------------" << endl;
//}
//
//void postOrderTraversal(TreeType* bst)
//{
//	cout << "---------------------------------------------" << endl;
//	cout << "Post-order:" << endl;
//	bst->postOrder(display);
//	cout << "---------------------------------------------" << endl;
//}
//
//void breadthTraversal(TreeType* bst)
//{
//	cout << "---------------------------------------------" << endl;
//	cout << "Level-order:" << endl;
//	bst->levelOrder(display);
//	cout << "---------------------------------------------" << endl;
//}
//
//void printTree(TreeType* bst)
//{
//	bst->printTree(displayTree);
//}

void screenOutput()
{
	// DOESNT WORK ON FILE INPUT, CAN BE USED FOR SCREEN OUTPUT
	/*
	// read the amor user into armor vector
	getline(infile, item, ',');
	users.push_back(item);
	getline(infile, item, ';');
	users.push_back(item);
	// CAPBILITIES
	// (1) read from the file until the ';' as one whole string,
	// (2) and the split them into pieces of string and then push them into its vector
	getline(infile, item, ';'); // (1)
	size_t comma = item.find_first_of(','); // first comma
	size_t nextComma = item.find_first_of(',', comma + 1); // next comma
	item2 = item.substr(0, comma); // this line onwards is (2)
	capbl.push_back(item2);
	while (comma != string::npos)
	{
		item2 = item.substr(comma + 1, nextComma - comma - 1);
		capbl.push_back(item2);
		comma = nextComma;
		nextComma = item.find_first_of(',', nextComma + 1);
	}
	// WEAPONS
	// (1) read from the file until the ';' as one whole string,
	// (2) and the split them into pieces of string and then push them into its vector
	getline(infile, item, ';'); // (1)
	comma = item.find_first_of(','); // first comma
	nextComma = item.find_first_of(',', comma + 1); // next comma
	item2 = item.substr(0, comma); // this line onwards is (2)
	weap.push_back(item2);
	while (comma != string::npos)
	{
		item2 = item.substr(comma + 1, nextComma - comma - 1);
		weap.push_back(item2);
		comma = nextComma;
		nextComma = item.find_first_of(',', nextComma + 1);
	}
	*/
}

