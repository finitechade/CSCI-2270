#include "poly.h"
using namespace std;

namespace main_savitch_5
{
	polynomial::polynomial(double c, unsigned int exponent)
	{
		// store machine epsilon
		EPSILON = std::numeric_limits<double>::epsilon();
		// write the rest
		if(fabs(c) > EPSILON){
			head_ptr = new polynode();
			tail_ptr = new polynode(c,exponent);
			head_ptr->set_fore(tail_ptr);
			tail_ptr->set_back(head_ptr);
			recent_ptr = tail_ptr;

		}else{
			head_ptr = new polynode();
			tail_ptr = head_ptr;
		}
	}

	polynomial& polynomial::operator=(const polynomial& source)
	{
		if(this != &source){
			// store machine epsilon
			EPSILON = std::numeric_limits<double>::epsilon();
			// write the rest
			
			while(tail_ptr != head_ptr){
				recent_ptr = tail_ptr;
				tail_ptr = tail_ptr->back();
				delete recent_ptr;
			}
			recent_ptr = head_ptr;
			delete recent_ptr;
			tail_ptr->set_fore(nullptr);
			head_ptr = new polynode(source.head_ptr->coef(),source.head_ptr->exponent());
			head_ptr->set_back(nullptr);

			polynode * thisTmp = head_ptr;		
			recent_ptr= source.head_ptr;

			while(recent_ptr->fore() != nullptr){
				recent_ptr = recent_ptr->fore();	
				thisTmp->set_fore(new polynode(recent_ptr->coef(), recent_ptr->exponent()));
				thisTmp->fore()->set_back(thisTmp);
				thisTmp = thisTmp->fore();
			}
			thisTmp->set_fore(nullptr);
			tail_ptr = thisTmp;
			delete thisTmp;
			delete recent_ptr;
		}
		return *this;
	}

	polynomial::polynomial(const polynomial& source)
	{

		// store machine epsilon
		EPSILON = std::numeric_limits<double>::epsilon();
		// write the rest
		this->head_ptr = new polynode(source.head_ptr->coef(), source.head_ptr->exponent());
		this->head_ptr->set_back(nullptr);

		polynode * tmp = source.head_ptr;
		polynode * thisTmp = this->head_ptr;
		while(tmp->fore() != nullptr){
			tmp = tmp->fore();	
			thisTmp->set_fore(new polynode(tmp->coef(), tmp->exponent()));
			thisTmp->fore()->set_back(thisTmp);
			thisTmp = thisTmp->fore();
		}
		thisTmp->set_fore(nullptr);
		tail_ptr = thisTmp;
		delete thisTmp;
		delete tmp;
		recent_ptr = tail_ptr;

	}

	polynomial::~polynomial()
	{
		clear();
		delete head_ptr;
	}

	void polynomial::clear()
	{
		while(tail_ptr->back() != nullptr){
			recent_ptr = tail_ptr;
			tail_ptr = tail_ptr->back();
			delete recent_ptr;
		}
		head_ptr = new polynode();
	}

	double polynomial::coefficient(unsigned int exponent) const
	{
		set_recent(exponent);
		return recent_ptr->coef();
	}

	void polynomial::add_to_coef(double amount, unsigned int exponent)
	{
		set_recent(exponent);
		assign_coef(amount + recent_ptr->coef(), exponent);
	}

	void polynomial::remove_node(polynode * to_delete){
		if(head_ptr == to_delete){
			head_ptr = to_delete->fore();
		}
		if(tail_ptr == to_delete){
			tail_ptr = to_delete->back();
		}
		to_delete->back()->set_fore(to_delete->fore());
		to_delete->fore()->set_back(to_delete->back());
		delete to_delete;

	}

	void polynomial::assign_coef(double coefficient, unsigned int exponent)
	{
		set_recent(exponent);
		if(coefficient == 0){
			remove_node(recent_ptr);
		}else{
			recent_ptr->set_coef(coefficient);
		}
	}

	unsigned int polynomial::next_term(unsigned int exponent) const
	{
		set_recent(exponent);
		if(recent_ptr->fore() != nullptr){
			if(recent_ptr->fore()->coef() != 0){
				return recent_ptr->fore()->exponent();
			}
		}
		return 0;
	}

	unsigned int polynomial::previous_term(unsigned int exponent) const
	{
		set_recent(exponent);
		if(recent_ptr->back() != nullptr){
			if(recent_ptr->back()->coef() != 0){
				return recent_ptr->back()->exponent();
			}
		}

		return UINT_MAX;
	}

	void polynomial::set_recent(unsigned int exponent) const
	{

		//if the exponent location is maybe closer to the the end or beginning
		if((tail_ptr->exponent()+ head_ptr->exponent())/2 < exponent){
			recent_ptr = tail_ptr;
			while(recent_ptr->back() != nullptr && recent_ptr->exponent() > exponent){
				recent_ptr = recent_ptr->back();
			}
			if(exponent > recent_ptr->exponent()){
				recent_ptr = recent_ptr->fore();
			}
		}else{
			recent_ptr = head_ptr;
			while(recent_ptr->fore() != nullptr && recent_ptr->exponent() > exponent){
				recent_ptr = recent_ptr->fore();
			}
			if(exponent < recent_ptr->exponent()){
				recent_ptr = recent_ptr->back();
			}
		}
	}

	double polynomial::eval(double x) const
	{
		double total = 0;
		return total;
	}

	polynomial polynomial::derivative() const
	{
		polynomial p_prime;
		return p_prime;
	}

	polynomial operator+(const polynomial& p1, const polynomial& p2)
	{
		polynomial p;
		return p;
	}

	polynomial operator-(const polynomial& p1, const polynomial& p2)
	{
		polynomial p;
		return p;
	}

	polynomial operator*(const polynomial& p1, const polynomial& p2)
	{		
		polynomial p;
		return p;
	}

	ostream& operator << (ostream& out, const polynomial& p)
	{
		unsigned int expo = 0;
		do{
			out << p.coefficient(expo)<< "*x^" << expo;
			expo = p.next_term(expo);
			if(expo != 0){
				out << " + ";
			}
		}while(expo != 0);
		return out;
	}

	void polynomial::find_root(
		double& answer,
		bool& success,
		unsigned int& iterations,
		double guess,
		unsigned int maximum_iterations,
		double epsilon) const
	{
	}
}
