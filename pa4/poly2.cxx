// poly2.cxx - implements polynomial class as defined in poly2.h
// Yunkai Zhang, Charlie Wei 5/10/17

#include <iostream>
#include <cassert>  // provides assert
#include <cmath>
#include <climits>
#include <cstdlib>  // includes NULL
#include "poly2.h"  // defines what must be implemented

namespace main_savitch_5
{

polynomial::polynomial(double c, unsigned int exponent){
  polynode* temp = new polynode(0, 0, NULL, NULL);
  head_ptr = tail_ptr = temp;
  current_degree = 0;
  assign_coef(c,exponent);
}

polynomial::polynomial(const polynomial &source){
  	current_degree = source.degree();
	polynode* temp = NULL;
	head_ptr = NULL;
	tail_ptr = NULL;
	
        for(polynode* cursor = source.head_ptr; cursor != NULL; cursor = cursor->fore()){
	  temp = new polynode(cursor->coef(), cursor->exponent(), NULL, temp);
	  if(cursor == source.head_ptr){
	    head_ptr = temp;
	  }else{
	    if(cursor->fore() == NULL){
	      tail_ptr = temp;
	    }
	    temp->back()->set_fore(temp);
	  }
	  }
}

polynomial::~polynomial(){
  this->clear();
}

polynomial& polynomial::operator =(const polynomial& source){
  if (this==&source){
		return *this;
	}
  this->clear();
  int i = 0;
  while(i <= source.degree()){
    assign_coef(source.coefficient(i),i);
    i++;
  }
}

void polynomial::add_to_coef(double amount, unsigned int exponent){
  assign_coef(coefficient(exponent)+amount, exponent);	
}

void polynomial::assign_coef(double coefficient, unsigned int exponent){
  set_recent(exponent);
  if(coefficient == 0 && exponent > current_degree){return;}
  else if(recent_ptr->exponent() < exponent){
    recent_ptr->set_fore(new polynode(coefficient, exponent, recent_ptr->fore(),recent_ptr));
    if(recent_ptr->fore()->fore() != NULL){
      recent_ptr->fore()->fore()->set_back(recent_ptr->fore());
    }else{
      current_degree = exponent;
      tail_ptr = recent_ptr->fore();
    }
    set_recent(exponent);
  }else if(coefficient != 0 || exponent == 0){
    recent_ptr->set_coef(coefficient);
  }else if(coefficient == 0 && exponent == current_degree){
    recent_ptr->back()->set_fore(NULL);
    tail_ptr = recent_ptr->back();
    delete recent_ptr;
   recent_ptr = tail_ptr;
   current_degree = recent_ptr->exponent();
  }else{
    recent_ptr->fore()->set_back(recent_ptr->back());
    recent_ptr = recent_ptr->fore();
    delete recent_ptr->back()->fore();
    recent_ptr->back()->set_fore(recent_ptr);
  }
}	

void polynomial::clear(){
  polynode* cursor = head_ptr;
  while (head_ptr->fore() != NULL){
          cursor = head_ptr->fore();
          delete head_ptr;
          head_ptr = cursor;
 }
  head_ptr->set_coef(0);
  head_ptr->set_exponent(0);
  current_degree = 0;
  tail_ptr = head_ptr;
}

double polynomial::coefficient(unsigned int exponent) const {
  set_recent(exponent);
  if(recent_ptr->exponent() != exponent){
    return 0;
  }else{
    return recent_ptr->coef();
  }
}

polynomial polynomial::derivative( ) const {
  polynomial* derivative = new polynomial();
  for (int i = next_term(0); i != 0 && i <= current_degree; i = next_term(i)) {
    derivative->assign_coef(i*coefficient(i),i-1);
  }
  return *derivative;
}

double polynomial::eval(double x) const {
  double value=0;
	for (int i=0; i<=current_degree; i++){
	  value += coefficient(i) * pow(x,i);
	}
	return value;
}

void polynomial::find_root(double &answer, bool &success, unsigned & iterations, double guess, unsigned int maximum_iterations, double epsilon) const {
	assert(epsilon>=0);
	polynomial derivative1;
	derivative1 = derivative();
	answer = guess;
	double f = eval(answer);
	double fprime = derivative1.eval(answer);
	iterations = 0;
	success = false;
	if (fabs(f) < epsilon){
         	success = true;
             	return;
 	} else if (fabs(fprime) < epsilon) {
           	return;
   	}
	for (int i=0; i<maximum_iterations; i++){
		iterations+=1;
		answer = answer - f/fprime;
		f = eval(answer);
		fprime = derivative1.eval(answer);
		if (fabs(f) < epsilon){
                        success = true;
                        return;
                } else if (fabs(fprime) < epsilon) {
                        return;
                }
	}
}

unsigned int polynomial::next_term(unsigned int e) const {
  set_recent(e);
  if(recent_ptr->fore() == NULL){
    return 0;
  }
  return recent_ptr->fore()->exponent();
}

unsigned int polynomial::previous_term(unsigned int e) const{
  if(e <= 0){
    return UINT_MAX;
  }
  set_recent(e-1);
  if(recent_ptr == NULL || recent_ptr->coef() == 0){
    return UINT_MAX;
  }
  return recent_ptr->exponent();
}

void polynomial::set_recent(unsigned int exponent) const{
  if(exponent <= 0){
    recent_ptr = head_ptr;
  }else if(exponent >= current_degree){
    recent_ptr = tail_ptr;
  }else if(exponent < recent_ptr->exponent()){
    do{
      recent_ptr = recent_ptr->back();
    }while(exponent < recent_ptr->exponent());
  }else{
    while(exponent > recent_ptr->exponent()){
      recent_ptr = recent_ptr->fore();
    }
    if(recent_ptr->exponent() != exponent){
      recent_ptr = recent_ptr->back();
    }
  }
}

polynomial operator +(const polynomial& p1, const polynomial& p2){
  int largest = p1.degree();
	if (p2.degree() > p1.degree()){
		largest=p2.degree();
	}
	polynomial sum(0,0);
	for (int i=0; i<=largest;i++){
		sum.assign_coef(p1.coefficient(i) + p2.coefficient(i),i);
	}
	return sum;
}

polynomial operator -(const polynomial& p1, const polynomial& p2){
  int largest = p1.degree();
  if(p2.degree() > p1.degree()){
    largest = p2.degree();
  }
  polynomial difference(0,0);
	for (int i=0; i<=largest;i++){
		difference.assign_coef(p1.coefficient(i) - p2.coefficient(i),i);
        }
	return difference;
}

polynomial operator *(const polynomial& p1, const polynomial& p2){
  polynomial multiply(0,0);
  for(int i = 0; i <= p1.degree(); i++){
		for (int j = 0; j <= p2.degree(); j++){
			multiply.add_to_coef(p1.coefficient(i)*p2.coefficient(j),i+j);
		}
	}
	return multiply;
}	

std::ostream& operator << (std::ostream& out, const polynomial& p){
  if(p.degree() == 0 && p.coefficient(0)==0) {
    out << "0"<<std::endl;
   } else if (p.degree() == 0 && p.coefficient(0)!=0){
    out << p.coefficient(0)<<std::endl;
  } else if (p.degree()==1){
		out << p.coefficient(1) << "x";
		if (p.coefficient(0)>0){
                  out<<" + "<<p.coefficient(0);
                }else if (p.coefficient(0)<0){
                  out<<" - "<<std::abs(p.coefficient(0));
                }
                out<<std::endl;
	} else {
		out << p.coefficient(p.degree()) << "x^" << p.degree();
		for(int i = p.previous_term(p.degree()); i > 1; i = p.previous_term(i)){
		  if(p.coefficient(i) > 0){
		    out <<" + "<<p.coefficient(i)<<"x^"<< i;
		  }else{
		    out <<" - "<<std::abs(p.coefficient(i))<<"x^"<< i;
		  }
		}
		if(p.coefficient(1) > 0){
                        out<<" + "<<p.coefficient(1)<<"x";
		  }else if(p.coefficient(1)<0){
		    out<<" - "<<std::abs(p.coefficient(1))<<"x";
		  }
  if (p.coefficient(0)>0){
		       out<<" + "<<p.coefficient(0);
  } else if (p.coefficient(0)<0){
		  out<<" - "<<std::abs(p.coefficient(0));
		}
		out<<std::endl;
	}
	return out;
}


}
