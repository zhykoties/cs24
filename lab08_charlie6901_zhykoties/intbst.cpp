// intbst.cpp
// Implements class IntBST
// Charlie Wei, Yunkai Zhang 5/30/2017

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() : root(0) { }

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (n) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    // handle special case of empty tree first
    if (!root) {
        root = new Node(value);
        return true;
    }
    // otherwise use recursive helper
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value == n->info)
        return false;
    if (value < n->info) {
        if (n->left)
            return insert(value, n->left);
        else {
            n->left = new Node(value);
            return true;
        }
    }
    else {
        if (n->right)
            return insert(value, n->right);
        else {
            n->right = new Node(value);
            return true;
        }
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n) {
        cout << n->info << " ";
        printPreOrder(n->left);
        printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
  if(n){
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);    
  }
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}
void IntBST::printPostOrder(Node *n) const {
  if(n){
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
  }
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
  if(n){
    return n->info+sum(n->left)+sum(n->right);
  }
  else{
    return 0;
  }
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
  if(n){
    return 1+count(n->left)+count(n->right);
  }else{
    return 0;
  }
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
  return contains(value, root);
}
  
bool IntBST::contains(int value, Node *n) const {
  if(n){
    if(n->info == value){
      return true;
    }
    return contains(value, n->left)||contains(value, n->right);
  }else{
    return false;
  }
}
