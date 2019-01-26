//
// BST.hpp
// CSE 100 Project 1
//
// Last modified by Victor Alonso on 01/18/2019
// A12981873

#ifndef BST_HPP
#define BST_HPP

#include <iostream>

#include "BSTIterator.hpp"
#include "BSTNode.hpp"

using namespace std;

template <typename Data>
class BST {
protected:
    // Pointer to the root of this BST, or 0 if the BST is empty.
    BSTNode<Data> *root;

    // Number of elements stored in this BST.
    unsigned int isize;

    // Height of this BST.
    unsigned int iheight;
	//Added this 
    unsigned int currH;

public:
    // Define iterator as an aliased typename for BSTIterator<Data>.
    typedef BSTIterator<Data> iterator;

    /** 
     * Default constructor. Initializes an empty BST.
     */
    BST() : root(0), isize(0), iheight(0) {}

    /** 
     * Default destructor. Frees all memory allocated by this BST.
     */
    // TODO: DONE
    virtual ~BST() {
	deleteAll(root);
	}

    /** 
     * Inserts the given item into this BST.
     *
     * This function should use only the '<' operator when comparing
     * Data items. (do not use ==, >, <=, >=). For the reasoning
     * behind this, see the assignment writeup.
     *
     * Parameters:
     *     item Data item to insert into this BST
     *
     * Returns:
     *     true if the item was inserted as a consequence of calling
     *     this function, false otherwise (e.g. item is a duplicate).
     */
    // TODO: DONE, except for implementation fo height
    virtual bool insert(const Data &item) {
	int currH = 0;
	//first check if BST/root is empty and inserts it as the root if so
	if(empty()){
		root = new BSTNode<Data>(item);
		isize = isize + 1;
		iheight = iheight + 1;
		return true;
	}
	//NOTE: may need to take into account for when item is equal to current->data
	//NOTE: these also use a custom constructor I built
	else if(find(item) != nullptr)
		return false;

	else {
		BSTNode<Data>* current = root;
		currH = currH + 1;
		while(current != nullptr){
			if(item < current->data)
			{
				if(current->left == nullptr){
					current->left = new BSTNode<Data>(item);
					current->left->parent = current;
					isize = isize + 1;
					currH = currH + 1;
					if(currH > iheight)
						iheight = currH;
					return true;
					}
				else {
					currH = currH + 1;
					current = current->left; 
				}
			}
			//case where item is larger than current->data
			else if (current->data < item) {
				if(current->right == nullptr){
					current->right = new BSTNode<Data>(item);
					current->right->parent = current;
					isize = isize + 1;
					currH = currH + 1;
					if(currH > iheight)
						iheight = currH;
					return true;
				}
				else {
					currH = currH + 1;
					current = current->right;
				}
			}
			//case where item equals the data ie: a duplicate
			else
				return false;
		} 
	}
}

    /**
     * Searches for the given item in this BST.
     *
     * This function should use only the '<' operator when comparing
     * Data items. (should not use ==, >, <=, >=). For the reasoning
     * behind this, see the assignment writeup.
     *
     * Parameters:
     *     item Data item to search for in this BST.
     *
     * Returns:
     *     An iterator pointing to the item if found, or pointing 
     *     past the last node in this BST if item is not found.
     */
    // TODO: DONE
    // don't use iterator, just return one
    virtual iterator find(const Data &item) const {
		BSTNode<Data>* current = root;
		while(current != nullptr){
			if(item < current->data)
			{
				if(current->left == nullptr){
					return end();
				}
				else
					current = current->left; 
			}
			//case where item is larger than current->data
			else if (current->data < item) {
				if(current->right == nullptr){
					return end();
				}
				else
					current = current->right;
			}
			else
				return typename BST<Data>::iterator(current); 
		}
		return end(); 
}

    /** 
     * Returns the number of items currently in the BST.
     */
    // TODO:DONE
    unsigned int size() const {
	return isize;
	}

    /** 
     * Returns the height of this BST.
     */
    // TODO
    // idea: change to count the nodes and  find logbase 2 of that.
    unsigned int height() const {
	return iheight;
	}
	

    /** 
     * Returns true if this BST is empty, false otherwise.
     */
    // TODO: DONE
    bool empty() const {
	if(isize == 0)
		return true;
	else
		return false;
	}

    /** 
     * Returns an iterator pointing to the first item in the BST (not the root).
     */
    // TODO: DONE
    iterator begin() const {
	//traverse to the leftmost node...
	BSTNode<Data>* current = root;
	while(current->left != nullptr)
		current = current->left;
	return typename BST<Data>::iterator(current);	
	}

    /** 
     * Returns an iterator pointing past the last item in the BST.
     */
    iterator end() const { 
        return typename BST<Data>::iterator(0); 
    }

    /** 
     * Prints the elements in this BST in ascending order.
     */
    void inorder() const { 
        inorder(root); 
    }

private:
    /*
     * Find the first node in the given subtree with root curr.
     */
    static BSTNode<Data>* first(BSTNode<Data> *curr) {
        if (!curr) return 0;
        while (curr->left) {
            curr = curr->left;
        }
        return curr;
    }

    /* 
     * Do an inorder traversal, printing the data in ascending order.
     *
     * You can achieve an inorder traversal recursively by following 
     * the order below.
     *
     *     recurse left - print node data - recurse right
     */
    // TODO: DONE
    // USING ITERATOR, works!
    static void inorder(BSTNode<Data> *n) {
	BSTNode<Data>* current = n;
	while(current->left != nullptr)
		current = current->left;
	while(current != nullptr) {
		cout << current->data <<endl;
		current = current->successor();
	}
}

    /* 
     * Do a postorder traversal, deleting nodes.
     *
     * You can achieve a postorder traversal recursively by following 
     * the order below.
     *
     *     recurse left - recurse right - delete node
     */
    // TODO: DONE
    static void deleteAll(BSTNode<Data> *n) {
	BSTNode<Data>* current = n;
	if(n == nullptr)
		return;
	if(current->left == nullptr){
		if(current->right == nullptr){
			delete current;
		}
		else
			deleteAll(current->right);
	}	
	else
		deleteAll(current->left);
}
};

#endif  // BST_HPP
