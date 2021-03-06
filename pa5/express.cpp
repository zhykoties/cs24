// express.cpp
// Implements class express
// Charlie Wei, Yunkai Zhang 5/30/2017

#include "express.h"

#include <iostream>
using std::cout;

// constructor sets up an expression tree with one node
ExpressionTree::ExpressionTree(double value){
  data = value;
  left = right = NULL;
}

// constructor copies an expression tree
ExpressionTree::ExpressionTree(const ExpressionTree& source){
  data = source.data;
  operation = source.operation;
  left = source.left;
  right = source.right;  
}

// deconstructor
ExpressionTree::~ExpressionTree(){
  if(left){delete left;}
  if(right){delete right;}
  left = NULL;
  right = NULL;
}

ExpressionTree& ExpressionTree::operator =(const ExpressionTree& source){
  if(this == &source){
    return *this;
  }
  delete this;
  data = source.data;
  operation = source.operation;
  left = source.left;
  right = source.right;
  return *this;
}

double ExpressionTree::evaluate() const{
  if(left == NULL && right == NULL){
    return data;
  }else{
    if(operation == '+'){
      return left->evaluate() + right->evaluate();
    }else if(operation == '*'){
      return left->evaluate() * right->evaluate();
    }
    else{
      return 0;
    }
  }
}

void ExpressionTree::printPre() const{
  
}

void ExpressionTree::printPost() const{

}

void ExpressionTree::printIn() const{
  
}

ExpressionTree operator +(const ExpressionTree& e1, const ExpressionTree& e2){
  ExpressionTree result;
  //std::cout << "success 1.5" << std::endl;  
  result.left = new ExpressionTree(e1); 
  // std::cout << result->left->data << std::endl;
  result.right = new ExpressionTree(e2); 
  //std::cout << result->right->data << std::endl;
  result.operation = '+';
  return result;
}

ExpressionTree operator *(const ExpressionTree& e1, const ExpressionTree& e2){
  ExpressionTree* result = new ExpressionTree();
  //std::cout << "success 1.5" << std::endl;  
  result->left = new ExpressionTree(e1); 
  //std::cout << result->left->data << std::endl;
  result->right = new ExpressionTree(e2); 
  //std::cout << result->right->data << std::endl;
  result->operation = '*';
  return *result;
}


/*This is a variation of Programming Project 1, pp. 534-535 of the textbook. Read the instructions (and hints) presented there. This variation adds three print methods to the problem presented in the text.
* Implement each of the member functions (including both constructors, the destructor and the assignment operator) of class ExpressionTest.
* Be sure to #include "express.h" and remember to type your name(s) and the date in the comment at the start.
* The print functions must show the expression parts (numbers and operators and parentheses) separated by one space from each other, and there must be one blank space at the end of each printed expression. Print to cout.
* Function printPre must print the expression in prefix notation, and printPost must print it in postfix notation. Function printIn must print parentheses surrounding each addition operation, but multiplication operations must not be parenthesized, and of course this function must print the expression in infix notation.*/

