// Binary Search Tree ADT
// Created by A. Student
// Modified by: <=============================== BENNY TANDIO KUSUMA

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"
#include "Armors.h"

class BinarySearchTree : public BinaryTree
{
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode * _insert(BinaryNode* nodePtr, BinaryNode* newNode);
	BinaryNode* _insertSec(BinaryNode* nodePtr, BinaryNode* newNode);

	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode* _remove(BinaryNode* nodePtr, Armors* target, bool& success);

	// delete target node from tree, called by internal remove node
	BinaryNode* deleteNode(BinaryNode* targetNodePtr);

	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode* removeLeftmostNode(BinaryNode* nodePtr, Armors*& successor);

	// search for target node
	BinaryNode* findNode(BinaryNode* treePtr, Armors* target) const;
	BinaryNode* findNodeSec(BinaryNode* treePtr, Armors* target, void visit(Armors*)) const;


public:
	// insert a node at the correct location
	bool insert(Armors* newEntry);
	bool insertSec(Armors* newEntry);
	// remove a node if found
	bool remove(Armors* anEntry);
	// find a target node
	bool getEntry(Armors* target, Armors*& returnedItem) const;
	bool getEntrySec(Armors* target, Armors *&,void visit(Armors*)) const;
	void deleteRoot();
	void destroyTree(BinaryNode *nptr);

	~BinarySearchTree();


};



///////////////////////// public function definitions ///////////////////////////
//Inserting items within a tree
bool BinarySearchTree::insert(Armors* newentry)
{
	BinaryNode* newnodeptr = new BinaryNode(newentry);
	
	this->rootPtr = _insert(this->rootPtr, newnodeptr);
	
	return true;
}

//Inserting items within a tree
bool BinarySearchTree::insertSec(Armors* newentry)
{
	BinaryNode* newnodeptr = new BinaryNode(newentry);
	
	this->rootPtr = _insertSec(this->rootPtr, newnodeptr);
	
	return true;
}

//Removing items within a tree
bool BinarySearchTree::remove(Armors* target)
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful);

	return isSuccessful;
}


//Finding entries within a tree
bool BinarySearchTree::getEntry(Armors* anEntry, Armors*& returnedItem) const
{
	BinaryNode* newNodePtr = findNode(this->rootPtr, anEntry);

	if (newNodePtr != NULL)
	{
		returnedItem = newNodePtr->getItem();
		return true;
	}
	return false;
}

//Finding entries within a tree
bool BinarySearchTree::getEntrySec(Armors* anEntry, Armors *&returnedItem, void visit(Armors*)) const
{
	BinaryNode* newNodePtr = findNodeSec(this->rootPtr, anEntry, visit);

	if (newNodePtr != NULL)
	{
		returnedItem = newNodePtr->getItem();
		return true;
	}
	return false;
}


//////////////////////////// private functions ////////////////////////////////////////////
//Implementation of the insert operation
BinaryNode* BinarySearchTree::_insert(BinaryNode* nodePtr,
	BinaryNode* newNodePtr)
{
	if (nodePtr == NULL) {
		nodePtr = newNodePtr;
	}
	else {
		Armors* newItem = newNodePtr->getItem();
		Armors* rootItem = nodePtr->getItem();

		if (newItem->getCodename() < rootItem->getCodename()) {
			nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
		}
		else {
			nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));
		}
	}
	return nodePtr;
}

//Implementation of the insert operation
BinaryNode* BinarySearchTree::_insertSec(BinaryNode* nodePtr,
	BinaryNode* newNodePtr)
{
	if (nodePtr == NULL) {
		nodePtr = newNodePtr;
	}
	else {
		Armors* newItem = newNodePtr->getItem();
		Armors* rootItem = nodePtr->getItem();

		if (newItem->getArmorType() < rootItem->getArmorType()) {
			nodePtr->setLeftPtr(_insertSec(nodePtr->getLeftPtr(), newNodePtr));
		}
		else if (newItem->getArmorType() > rootItem->getArmorType()) {
			nodePtr->setRightPtr(_insertSec(nodePtr->getRightPtr(), newNodePtr));
		}
		else if (newItem->getArmorType() == rootItem->getArmorType()) {
			nodePtr->setRightPtr(_insertSec(nodePtr->getRightPtr(), newNodePtr));
		}
	}
	return nodePtr;
}

//Implementation of the remove operation
BinaryNode* BinarySearchTree::_remove(BinaryNode* nodePtr,
	Armors* target,
	bool& success)
{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
	if (nodePtr->getItem()->getCodename() > target->getCodename())
	{
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));

	}
	else if (nodePtr->getItem()->getCodename() < target->getCodename())
	{
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	}
	else
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}
	return nodePtr;
}

//Implementation of the delete operation
BinaryNode* BinarySearchTree::deleteNode(BinaryNode* nodePtr)
{
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)
	{
		BinaryNode* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0)
	{
		BinaryNode* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else
	{
		Armors* newNodeValue;
		newNodeValue = new Armors;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}
}


//Implementation to remove the left leaf
BinaryNode* BinarySearchTree::removeLeftmostNode(BinaryNode* nodePtr,
	Armors*& successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}
}


//Implementation for the search operation
BinaryNode* BinarySearchTree::findNode(BinaryNode* nodePtr,
	Armors* target) const
{
	Armors* rootItem = nodePtr->getItem();
	while (nodePtr != NULL)
	{
		if (target->getCodename() < rootItem->getCodename())
		{

			nodePtr = nodePtr->getLeftPtr();
			if (nodePtr == 0) { break; }
			rootItem = nodePtr->getItem();
		}
		else {
			if (target->getCodename() > rootItem->getCodename())
			{
				nodePtr = nodePtr->getRightPtr();
				if (nodePtr == 0) { break; }
				rootItem = nodePtr->getItem();
			}
			else {
				return nodePtr;
			}
		}
	}
	return 0;
}


//Implementation for the search operation
BinaryNode* BinarySearchTree::findNodeSec(BinaryNode* nodePtr,
	Armors* target, void visit(Armors*)) const
{
	if (nodePtr == NULL)
	{
		return 0;
	}

	if (target->getArmorType().compare(nodePtr->getItem()->getArmorType()) == 0) {
		visit( nodePtr->getItem());
	}

	findNodeSec(nodePtr->getLeftPtr(), target, visit);

	findNodeSec(nodePtr->getRightPtr(), target, visit);

	return 0;
}

void BinarySearchTree::deleteRoot() {
	remove(this->rootPtr->getItem());
	cout << "ROOT DELETED\n";
}

BinarySearchTree::~BinarySearchTree() {
	destroyTree(this->rootPtr);
}

void BinarySearchTree::destroyTree(BinaryNode* nodePtr) {
	if (remove(nodePtr->getItem())) {
		cout << "Destroying a node... \n";
		nodePtr = this->rootPtr;
		if (nodePtr != nullptr)
			destroyTree(nodePtr);
	}
}

#endif