// Binary Search Tree ADT

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"
#include "Hash.h"
#include "Armors.h"


template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);

	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool& success);

	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);

	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType& successor);

	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType& target) const;
	BinaryNode<ItemType>* findNode1(BinaryNode<ItemType>* treePtr, const string* target) const;

	// search for the smallest node
	BinaryNode<ItemType>* findSmallest(BinaryNode<ItemType>* treePtr) const;

	// search for the largest node
	BinaryNode<ItemType>* findLargest(BinaryNode<ItemType>* treePtr) const;

public:
	// insert a node at the correct location
	bool insert(const ItemType* newEntry);
	// remove a node if found
	bool remove(const ItemType& anEntry);
	// find a target node
	bool getEntry(const ItemType& target, ItemType& returnedItem) const;
	bool getEntry1(string item, ItemType returnedItem) ;

	// find the smallest node
	bool getSmallest(ItemType& returnedItem) const;
	// find the largest node
	bool getLargest(ItemType& returnedItem) const;

};


///////////////////////// public function definitions ///////////////////////////
//Inserting items within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType* newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	this->rootPtr = _insert(this->rootPtr, newNodePtr);
	return true;
}

//Removing items within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& target)
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
	return isSuccessful;
}

//Finding entries within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType& returnedItem) const
{
	BinaryNode<ItemType>* newNodePtr = findNode(this->rootPtr, anEntry);

	if (newNodePtr)
	{
		returnedItem = newNodePtr->getItem();
		return true;
	}
	return false;
}

//Finding entries within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry1(string item, ItemType returnedItem)
{
	BinaryNode<ItemType>* newNodePtr = findNode1(this->rootPtr, item);

	if (newNodePtr)
	{
		returnedItem = newNodePtr->getItem();
		return true;
	}
	return false;
}

// Finding the smallest entry
template<class ItemType>
bool BinarySearchTree<ItemType>::getSmallest(ItemType& returnedItem) const
{
	BinaryNode<ItemType>* newNodePtr = findSmallest(this->rootPtr);
	if (newNodePtr)
	{
		returnedItem = newNodePtr->getItem();
		return true;
	}
	return false;
}

// Finding the largest entry
template<class ItemType>
bool BinarySearchTree<ItemType>::getLargest(ItemType& returnedItem) const
{
	BinaryNode<ItemType>* newNodePtr = findLargest(this->rootPtr);
	if (newNodePtr)
	{
		returnedItem = newNodePtr->getItem();
		return true;
	}
	return false;
}



//////////////////////////// private functions ////////////////////////////////////////////
//Implementation of the insert operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
	BinaryNode<ItemType>* newNodePtr)
{
	if (nodePtr == NULL)
	{
		nodePtr = newNodePtr;
	}
	else {
		if (newNodePtr->getItem() < nodePtr->getItem())
		{
			nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
		}
		else {
			nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));
		}
	}
	return nodePtr;
}

//Implementation of the remove operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
	const ItemType target,
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
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}
}

//Implementation to remove the left leaf
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
	ItemType& successor)
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
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
	const ItemType& target) const
{
	while (nodePtr)
	{
		if (target < nodePtr->getItem())
		{
			nodePtr = nodePtr->getLeftPtr();
		}
		else {
			if (target > nodePtr->getItem())
			{
				nodePtr = nodePtr->getRightPtr();
			}
			else {
				return nodePtr;
			}
		}
	}
	return 0;
}

//Implementation for the search operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode1(BinaryNode<ItemType>* nodePtr,
	const string* target) const
{
	while (nodePtr)
	{
		if (target < nodePtr->getItem())
		{
			nodePtr = nodePtr->getLeftPtr();
		}
		else {
			if (target > nodePtr->getItem())
			{
				nodePtr = nodePtr->getRightPtr();
			}
			else {
				return nodePtr;
			}
		}
	}
	return 0;
}


//Implementation for the search the smallest operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findSmallest(BinaryNode<ItemType>* nodePtr) const
{
	// The smallest entry is the leftmost node
	if (nodePtr)
	{
		if (nodePtr->getLeftPtr())
		{
			return findSmallest(nodePtr->getLeftPtr());
		}
		else
		{
			return nodePtr;
		}
	}
	return 0;
}

//Implementation for the search the largest operation
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findLargest(BinaryNode<ItemType>* nodePtr) const
{
	// The largest entry is the rightmost node
	if (nodePtr)
	{
		if (nodePtr->getRightPtr())
		{
			return findLargest(nodePtr->getRightPtr());
		}
		else
		{
			return nodePtr;
		}
	}
	return 0;
}


#endif

