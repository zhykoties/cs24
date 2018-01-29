// poly0.cxx - implements polynomial class as defined in poly0.h
// Yunkai Zhang, 5/8/2017

#include <cassert>
#include "poly0.h"
#include <cmath>
#include <climits>

using namespace std;
namespace main_savitch_3{
  polynomial::polynomial(double c, unsigned int exponent){
    assert(exponent <= MAX_EX);
    coef[exponent] = c;
    current_degree = exponent;
    if(c == 0){
      current_degree = 0;
    }
  }

  void polynomial::add_to_coef(double amount, unsigned int exponent){
    assert(exponent <= MAX_EX);
    coef[exponent] += amount;
    if(exponent > current_degree){
      current_degree = exponent;
    }
    if(exponent == current_degree && coef[exponent] == 0){
      current_degree = previous_term(exponent);
    }
  }

  void polynomial::assign_coef(double coefficient, unsigned int exponent){
    assert(exponent <= MAX_EX);
    coef[exponent] = coefficient;
    if(exponent > current_degree){
      current_degree = exponent;
    }
    if(exponent == current_degree && coef[exponent] == 0){
      current_degree = previous_term(exponent);
    }
  }

  void polynomial::clear(){
    for(int i = degree(); i >= 0; i--){
      coef[i] = 0;
    }
    current_degree = 0;
  }

  double polynomial::coefficient(unsigned int exponent)const{
    if(exponent > MAX_EX){
      return 0;
    }
    return coef[exponent];
  }

  polynomial polynomial::derivative()const{
    polynomial temp = polynomial(1,degree()-1);
    for(int i = degree()-1; i >= 0; i--){
      temp.assign_coef((i+1)*coef[i+1],i);
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

  unsigned int polynomial::next_term(unsigned int e)const{
    int temp = e+1;
    while(temp <= degree()){
      if(coef[temp]!=0)
	return temp;
      temp++;
    }
    return 0;
  }

  unsigned int polynomial::previous_term(unsigned int e)const{
    int temp = e-1;
    while(temp >= 0){
      if(abs(coef[temp])>0.0000000001)
	return temp;
      temp--;
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
    assert(p1.degree()+p2.degree() <= polynomial::MAX_EX);
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
