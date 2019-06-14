// Binary tree abstract base class

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Queue.h"

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
	BinaryTree() { rootPtr = 0; count = 0; }
	BinaryTree(const BinaryTree<ItemType>& tree) { }
	virtual ~BinaryTree() { }
	BinaryTree& operator = (const BinaryTree& sourceTree);

	BinaryTree* Left;
	BinaryTree* Right;
	BinaryTree* Parent;

	// common functions for all binary trees
	bool isEmpty() const { return count == 0; }
	int size() const { return count; }
	void clear() { destroyTree(rootPtr); rootPtr = 0; count = 0; }
	void preOrder(void visit(ItemType&)) const { _preorder(visit, rootPtr); }
	void inOrder(void visit(ItemType&)) const { _inorder(visit, rootPtr); }
	void postOrder(void visit(ItemType&)) const { _postorder(visit, rootPtr); }

	void levelOrder(void visit(ItemType&)) const { _levelorder(visit, rootPtr); }
	void printTree(void visit(ItemType&, int)) const { _print(visit, rootPtr, 0); }

	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType* newData) = 0;
	virtual bool remove(const ItemType& data) = 0;
	virtual bool getEntry(const ItemType& anEntry, ItemType& returnedItem) const = 0;

	// finding smallest and largest item
	virtual bool getSmallest(ItemType& returnedItem) const = 0;
	virtual bool getLargest(ItemType& returnedItem) const = 0;

private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType&), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType&), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType&), BinaryNode<ItemType>* nodePtr) const;
	void _levelorder(void visit(ItemType&), BinaryNode<ItemType>* nodePtr) const;
	// internal print
	void _print(void visit(ItemType&, int), BinaryNode<ItemType>* nodePtr, int level) const;

};

//Destroy the entire tree
template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr != NULL)
	{
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		delete(nodePtr);
		if (nodePtr->getLeftPtr() != NULL)
			nodePtr->getLeftPtr() = NULL;
		if (nodePtr->getRightPtr() != NULL)
			nodePtr->getRightPtr() = NULL;
		nodePtr = NULL;
	}

}

//Preorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType&), BinaryNode<ItemType> * nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	}
}

//Inorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType&), BinaryNode<ItemType> * nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_inorder(visit, nodePtr->getLeftPtr());
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}

//Postorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType&), BinaryNode<ItemType> * nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		visit(item);
	}
}


//Level-Order Traversal
template<class ItemType>
void BinaryTree<ItemType>::_levelorder(void visit(ItemType&), BinaryNode<ItemType> * nodePtr) const
{
	if (nodePtr != 0)
    {
        Queue<BinaryNode<ItemType>*> q;
        q.enqueue(nodePtr);
        BinaryNode<ItemType> *ptr;

        while (!q.isEmpty())
        {
            q.dequeue(ptr);

            ItemType item = ptr->getItem();
            visit(item);

            if (ptr->getLeftPtr())
            {
                q.enqueue(ptr->getLeftPtr());
            }
            if (ptr->getRightPtr())
            {
                q.enqueue(ptr->getRightPtr());
            }
        }

    }
}

// Print helper, using pre-order traversal
template<class ItemType>
void BinaryTree<ItemType>::_print(void visit(ItemType&, int), BinaryNode<ItemType> * nodePtr, int level) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item, level);

		_print(visit, nodePtr->getLeftPtr(), level + 1);
		_print(visit, nodePtr->getRightPtr(), level + 1);
	}
}

#endif

