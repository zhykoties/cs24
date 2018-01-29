// poly1.cxx - implements polynomial class as defined in poly1.h
// Yunkai Zhang, 5/8/2017

#include <cassert>
#include "poly1.h"
#include <cmath>
#include <climits>

using namespace std;
namespace main_savitch_4{
  polynomial::polynomial(double c, unsigned int exponent){
      if(abs(c) < 0.0000001){
    current_degree = 0;
    coef = new double[DEFAULT_CAPACITY];
    size = DEFAULT_CAPACITY;
    for(int i = 0; i < size; i++){
      coef[i] = 0;
    }
      }else{
    if(DEFAULT_CAPACITY > exponent){
      coef = new double[DEFAULT_CAPACITY];
      size = DEFAULT_CAPACITY;
    }else{
      coef = new double[exponent+2];
      size = exponent+1;
    }
    for(int i = 0; i < size; i++){
      coef[i] = 0;
    }
    coef[exponent] = c;
    current_degree = exponent;
      }
  }

  polynomial::polynomial(const polynomial& source){
    current_degree = source.degree();
    size = source.size;
    coef = new double[size];
    for(int i = 0; i <= source.degree(); i++){
      coef[i] = source.coef[i];
    }
  }

  polynomial::~polynomial(){
    delete [] coef;
  }

  polynomial& polynomial::operator =(const polynomial& source){
    try{
    if(this == &source){
      return *this;
    }
    if(size != source.size){
      size = source.size;
      delete [] coef;
      coef = new double[source.size];
    }
    current_degree = source.current_degree;
    for(int i = 0; i <= source.degree(); i++){
      coef[i] = source.coef[i];
    }
    return *this;
    }catch(bad_alloc& ba){}
  }
  
  void polynomial::add_to_coef(double amount, unsigned int exponent){
    double temp = coef[exponent];
    if(exponent < size){
      assign_coef(amount+temp,exponent);
    }else{
      assign_coef(amount,exponent);
    }
  }

  void polynomial::assign_coef(double coefficient, unsigned int exponent){
    if(abs(coefficient) != 0){
      if(exponent > current_degree){
    if(exponent >= size){
      reserve(exponent+1);
    }
    current_degree = exponent;
      }
      coef[exponent] = coefficient;
      if(exponent == current_degree && abs(coef[exponent]) == 0){
    current_degree = previous_term(exponent);
      }
    }else{
      coef[exponent] = 0;
      current_degree = previous_term(exponent);
    }
  }

  void polynomial::clear(){
    for(int i = 0; i < size; i++){
      coef[i] = 0;
    }
    current_degree = 0;
  }

  void polynomial::reserve(unsigned int number){
      int tempSize = size;
      size = max(current_degree+1, number);
      double *temp = new double[size];
      for(int i = 0; i < tempSize; i++){
    temp[i] = coef[i];
      }
      coef = new double[size];
      for(int i = 0; i < tempSize; i++){
    coef[i] = temp[i];
      }
      delete []temp;
  }

  double polynomial::coefficient(unsigned int exponent)const{
    if(exponent > size){
      return 0;
    }
    return coef[exponent];
  }

  polynomial polynomial::derivative()const{
    polynomial temp;
    temp.reserve(size);
    for(int i = 1; i < size; i++){
    temp.assign_coef(coef[i]*i,i-1);
    }
    return temp;
  }

  double polynomial::eval(double x)const{
    double temp = 0;
    for(int i = 0; i <= degree(); i++){
      temp += coef[i]*pow(x,i);
    }
    return temp;
  }

  void polynomial::find_root(double& answer, bool& success, unsigned int& iterations, double guess, unsigned int maximum_iterations, double epsilon) const{
    return;
  }

  unsigned int polynomial::next_term(unsigned int e)const{
    for(unsigned int i = e+1; i < size; i++){
      if(abs(coefficient(i)) > 0.00000001){
    return i;
      }
    }
    return 0;
  }

  unsigned int polynomial::previous_term(unsigned int e)const{
    for(unsigned int i = e-1; i >= 0; i--){
      if(abs(coefficient(i)) > 0.0000001){
    return i;
      }
    }
    return UINT_MAX;
  }

  polynomial operator -(const polynomial& p1, const polynomial& p2){
    polynomial temp = polynomial(1,max(p1.degree(),p2.degree()));
    for(int i = 0; i <= max(p1.degree(),p2.degree()); i++){
      temp.assign_coef(p1.coefficient(i)-p2.coefficient(i),i);
    }    
    return temp;
  }

  polynomial operator +(const polynomial& p1, const polynomial& p2){
    polynomial temp = polynomial(1,max(p1.degree(),p2.degree()));
    for(int i = 0; i <= max(p1.degree(),p2.degree()); i++){
      temp.assign_coef(p1.coefficient(i)+p2.coefficient(i),i);
    }
    return temp;
  }

  polynomial operator *(const polynomial& p1, const polynomial& p2){
    polynomial temp = polynomial(0,p1.degree()+p2.degree());
    for(int i = 0; i <= p1.degree()+p2.degree(); i++){
      for(int j = 0; j <= i; j++){
    temp.add_to_coef(p1.coefficient(j)*p2.coefficient(i-j),i);
      }
    }
    return temp;
  }

  ostream& operator << (ostream& out, const polynomial& p){
    if(p.degree() > 1){
      if(abs(p.coefficient(p.previous_term(p.degree())))>0.0000000000000001){
      if(p.coefficient(p.previous_term(p.degree()))>0){
      out << p.coefficient(p.degree()) << "x^" << p.degree() << " + ";
    }else{
      out << p.coefficient(p.degree()) << "x^" << p.degree() << " - ";
    }
      }else{
    out << p.coefficient(p.degree()) << "x^" << p.degree() << endl;
      }
    }
    for(int i = p.degree()-1; i > 1; i--){
      if(abs(p.coefficient(i))>0.0000000000000001){
    if(p.previous_term(i) == UINT_MAX){
      out << abs(p.coefficient(i)) << "x^" << i << endl;
      return out;
    }else{
      if(p.coefficient(p.previous_term(i))>0){
      out << abs(p.coefficient(i)) << "x^" << i << " + ";
      }else{
      out << abs(p.coefficient(i)) << "x^" << i << " - ";
      }
    }
      }
    }
    if(abs(p.coefficient(1))>0.0000000000000001){
      if(abs(p.coefficient(0))<0.0000000000000001){
    out << abs(p.coefficient(1)) << "x" << endl;
      }else{
    if(p.coefficient(0) > 0){
      out << abs(p.coefficient(1)) << "x + " << p.coefficient(0) << endl;
    }else{
      out << abs(p.coefficient(1)) << "x - " << p.coefficient(0) << endl;
    }
      }
    }
    if(p.degree() == 0){
      out << p.coefficient(0) << endl;
    }
    return out;
  }
}
