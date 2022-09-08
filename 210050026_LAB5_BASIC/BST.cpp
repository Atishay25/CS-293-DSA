#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::insert(int jrnyCode, int price)
{
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
    if(find(jrnyCode) >= 0) return false;
    TreeNode *newNode = new TreeNode(jrnyCode,price);
    TreeNode *y = nullptr;      // Using 2 pointers x and y to keep track
    TreeNode *x = root;         // of current Node and its parent
    while(x != nullptr){
        y = x;
        if(BSTLessThan(newNode,x)) x = x->left;
        else x = x->right;
    }
    newNode->parent = y;
    if(y == nullptr) root = newNode;
    else if(BSTLessThan(newNode,y)) y->left = newNode;
    else y->right = newNode;

    updateHeights(newNode->parent);

  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.
    TreeNode *x = new TreeNode(0,100);
    TreeNode *y = new TreeNode(jrnyCode,200);
    x = root;
    while(x != nullptr && jrnyCode != x->getJourneyCode()){       
        if(BSTLessThan(y,x)) x = x->left;
        else x = x->right;
    }
    if(x != nullptr) return x->getPrice(); 
    else return -1;

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
}

void BST::updateHeights(TreeNode *father){
	if(father == nullptr) return;
	if(father->right == nullptr && father->left != nullptr){
		father->height = 1 + father->left->height;
	}
  	else if(father->left == nullptr && father->right != nullptr){
		father->height = 1 + father->right->height;
	}
	else {
		father->height = 1 + max(father->left->height,father->right->height);
	}
	updateHeights(father->parent);
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

bool BST::remove(int jrnyCode)
{
  // Implement deletion in BST
  
  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.

  return true;
}


