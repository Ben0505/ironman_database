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
	BinaryNode* _insert(BinaryNode* nodePtr, BinaryNode* newNode);

	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode* _remove(BinaryNode* nodePtr, const Armors* target, bool& success);

	// delete target node from tree, called by internal remove node
	BinaryNode* deleteNode(BinaryNode* targetNodePtr);

	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode* removeLeftmostNode(BinaryNode* nodePtr, Armors* successor);

	// search for target node
	BinaryNode* findNode(BinaryNode* treePtr, Armors* target) const;

	//// search for the smallest node
	//BinaryNode<ItemType>* findSmallest(BinaryNode<ItemType>* treePtr) const;

	//// search for the largest node
	//BinaryNode<ItemType>* findLargest(BinaryNode<ItemType>* treePtr) const;

public:
	// insert a node at the correct location
	bool insert(Armors* newEntry);
	// remove a node if found
	bool remove(const Armors* anEntry);
	// find a target node
	bool getEntry(Armors* target, Armors*& returnedItem) const;

	//// find the smallest node
	//bool getSmallest(ItemType& returnedItem) const;
	//// find the largest node
	//bool getLargest(ItemType& returnedItem) const;

};


///////////////////////// public function definitions ///////////////////////////
//Inserting items within a tree
bool BinarySearchTree::insert(Armors* newentry)
{
	//cout << "in insert func, Armors newentry:" << newentry->getCodename() << endl;
	BinaryNode* newnodeptr = new BinaryNode(newentry);
	//cout << "Now Im calling _insert \n";

	this->rootPtr = _insert(this->rootPtr, newnodeptr);
	//cout << "***********Inserted\n";
	return true;
}

//Removing items within a tree
bool BinarySearchTree::remove(const Armors* target)
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
	return isSuccessful;
}


//Finding entries within a tree
bool BinarySearchTree::getEntry(Armors* anEntry, Armors*& returnedItem) const
{
	BinaryNode* newNodePtr = findNode(this->rootPtr, anEntry);

	//cout << "A2 : " << anEntry->getCodename() << endl;
	//cout << "A1 : " << returnedItem->getCodename() << endl;

	if (newNodePtr != NULL)
	{
		returnedItem = newNodePtr->getItem();
		cout << returnedItem << endl;
		return true;
	}
	return false;
}

//
//// Finding the smallest entry
//template<class ItemType>
//bool BinarySearchTree<ItemType>::getSmallest(ItemType& returnedItem) const
//{
//	BinaryNode<ItemType>* newNodePtr = findSmallest(this->rootPtr);
//	if (newNodePtr)
//	{
//		returnedItem = newNodePtr->getItem();
//		return true;
//	}
//	return false;
//}
//
//// Finding the largest entry
//template<class ItemType>
//bool BinarySearchTree<ItemType>::getLargest(ItemType& returnedItem) const
//{
//	BinaryNode<ItemType>* newNodePtr = findLargest(this->rootPtr);
//	if (newNodePtr)
//	{
//		returnedItem = newNodePtr->getItem();
//		return true;
//	}
//	return false;
//}


//////////////////////////// private functions ////////////////////////////////////////////
//Implementation of the insert operation
BinaryNode* BinarySearchTree::_insert(BinaryNode* nodePtr,
	BinaryNode* newNodePtr)
{
	//cout << "I am in _insert func \n";
	//cout << "nodePtr : " << nodePtr->getItem()->getCodename() << endl;

	if (nodePtr == NULL) {
		//cout << "There is no node in tree \n";
		nodePtr = newNodePtr;
	}
	else {
		Armors* newItem = newNodePtr->getItem();
		Armors* rootItem = nodePtr->getItem();

		//cout << "newItem : " << newItem->getCodename() << endl;
		//cout << "rooItem : " <<rootItem->getCodename() << endl;
		if (newItem->getCodename() < rootItem->getCodename()) {
			//cout << newItem->getCodename() << " going to the leftnode\n";
			nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
		}
		else {
			//cout << newItem->getCodename() << " going to the rightnode\n";
			nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));
		}
	}
	//cout << "I am returning to insert\n";
	return nodePtr;
}

//Implementation of the remove operation
BinaryNode* BinarySearchTree::_remove(BinaryNode* nodePtr,
	const Armors* target,
	bool& success)

{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
	if (nodePtr->getItem() > target)
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getItem() < target)
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
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
	Armors* successor)
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
	//cout << "rooitem : " << rootItem->getCodename() << endl;
	//cout<<endl;
	while (nodePtr)
	{
		if (target->getCodename() < rootItem->getCodename())
		{
			//cout << "1target : " << target->getCodename() << endl;
			//cout << "1rooitem : " << rootItem->getCodename() << endl;
			nodePtr = nodePtr->getLeftPtr();
			rootItem = nodePtr->getItem();
			//cout << "1.1rooitem : " << rootItem->getCodename() << endl;
			//cout<<endl;
		}
		else {
			if (target->getCodename() > rootItem->getCodename())
			{
				//	cout << "2target : " << target->getCodename() << endl;
					//cout << "2rooitem : " << rootItem->getCodename() << endl;
				nodePtr = nodePtr->getRightPtr();
				rootItem = nodePtr->getItem();
				//cout << "2.2rooitem : " << rootItem->getCodename() << endl;
				//cout<<endl;
			}
			else {
				//	cout << "3rooitem : " << rootItem->getCodename() << endl;
				return nodePtr;
			}
		}
	}
	return 0;

	//Armors* rootItem = nodePtr->getItem();
	////cout << "rooitem : " << rootItem->getCodename() << endl;
	//while (nodePtr)
	//{
	//	if (target->getCodename() < rootItem->getCodename())
	//	{
	//		//cout << "target : " << target->getCodename() << endl;
	//		//cout << "rooitem : " << rootItem->getCodename() << endl;
	//		nodePtr = nodePtr->getLeftPtr();
	//	}
	//	else {
	//		if (target->getCodename() > rootItem->getCodename())
	//		{
	//			//cout << "target : " << target->getCodename() << endl;
	//			//cout << "rooitem : " << rootItem->getCodename() << endl;
	//			nodePtr = nodePtr->getRightPtr();
	//		}
	//		else {
	//			//cout << "rooitem : " << rootItem->getCodename() << endl;
	//			return nodePtr;
	//		}
	//	}
	//}
	//return 0;

	/*Armors* rootItem = nodePtr->getItem();

	if (nodePtr == NULL)
	{
		return NULL;
	}

	
	if (target->getCodename() < rootItem->getCodename())
	{
		nodePtr = nodePtr->getLeftPtr();
	}
	else {
		if (target->getCodename() > rootItem->getCodename())
		{
			nodePtr = nodePtr->getRightPtr();
		}
		else { return nodePtr; }
	}*/
	


}
//
//
////Implementation for the search the smallest operation
//template<class ItemType>
//BinaryNode<ItemType>* BinarySearchTree<ItemType>::findSmallest(BinaryNode<ItemType>* nodePtr) const
//{
//	// The smallest entry is the leftmost node
//	if (nodePtr)
//	{
//		if (nodePtr->getLeftPtr())
//		{
//			return findSmallest(nodePtr->getLeftPtr());
//		}
//		else
//		{
//			return nodePtr;
//		}
//	}
//	return 0;
//}
//
////Implementation for the search the largest operation
//template<class ItemType>
//BinaryNode<ItemType>* BinarySearchTree<ItemType>::findLargest(BinaryNode<ItemType>* nodePtr) const
//{
//	// The largest entry is the rightmost node
//	if (nodePtr)
//	{
//		if (nodePtr->getRightPtr())
//		{
//			return findLargest(nodePtr->getRightPtr());
//		}
//		else
//		{
//			return nodePtr;
//		}
//	}
//	return 0;
//}


#endif

