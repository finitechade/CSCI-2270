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
			head_ptr = new polynode(0,0);
			head_ptr->set_fore(new polynode(c,exponent));
			head_ptr->fore()->set_back(head_ptr) ;
			current_degree = exponent;
			tail_ptr = head_ptr->fore();
			recent_ptr = tail_ptr;



		}else{
			head_ptr = new polynode();
			tail_ptr = head_ptr;
			current_degree = 0;
		}
	}

	polynomial& polynomial::operator=(const polynomial& source)
	{
		if(this != &source){
			// store machine epsilon
			EPSILON = std::numeric_limits<double>::epsilon();
			// write the rest
			this->clear();

			recent_ptr = head_ptr;
			head_ptr =  new polynode(source.head_ptr->coef(), source.head_ptr->exponent());
			head_ptr->set_back(nullptr);
			delete recent_ptr;
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
			recent_ptr = tail_ptr;
			current_degree = source.degree();
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
		//	delete thisTmp;
		//	delete tmp;
		recent_ptr = tail_ptr;
		current_degree = source.degree();

	}

	polynomial::~polynomial()
	{
		clear();
		delete head_ptr;
	}

	void polynomial::clear()
	{
		while(head_ptr != nullptr){
			recent_ptr = head_ptr;
			head_ptr = head_ptr->fore();
			delete recent_ptr;
		}
		head_ptr = new polynode();
		current_degree = 0;
	}

	double polynomial::coefficient(unsigned int exponent) const
	{
		set_recent(exponent);
		if(recent_ptr->exponent() == exponent){


			return recent_ptr->coef();
		}
		return 0.0;
	}

	void polynomial::add_to_coef(double amount, unsigned int exponent)
	{
		set_recent(exponent);
		if(recent_ptr->exponent() == exponent){
			assign_coef(amount + recent_ptr->coef(), exponent);
		}else{
			assign_coef(amount,exponent);
		}
	}


	void polynomial::assign_coef(double coefficient, unsigned int exponent)
	{
		set_recent(exponent);
		EPSILON = std::numeric_limits<double>::epsilon();
		if(fabs(coefficient) >= EPSILON){
			if(recent_ptr->exponent() == exponent){
				recent_ptr->set_coef(coefficient);
			}else{

				if(recent_ptr->fore() != nullptr){
					polynode * tmp = new polynode(coefficient,exponent, recent_ptr->fore(), recent_ptr);
					recent_ptr->fore()->set_back(tmp);
					recent_ptr->set_fore(tmp);
				}else{
					polynode * tmp = new polynode(coefficient,exponent, nullptr, recent_ptr);
					recent_ptr->set_fore(tmp);
					tail_ptr = tmp;
				} 
			}
		}else{
			if(recent_ptr->exponent() == exponent){
				if(recent_ptr != head_ptr){
					if(recent_ptr->fore() != nullptr){
						recent_ptr->back()->set_fore(recent_ptr->fore());
						recent_ptr->fore()->set_back(recent_ptr->back());		
						delete recent_ptr;
					}else{
						tail_ptr = recent_ptr->back();
						tail_ptr->set_fore(nullptr);
						delete recent_ptr;
					}
				}else{
					head_ptr->set_coef(0.0);
				}

			}


		}
		current_degree = tail_ptr->exponent();
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
		if(recent_ptr->exponent() == exponent){
			if(recent_ptr->back() != nullptr){
				if(recent_ptr->back()->coef() != 0){
					return recent_ptr->back()->exponent();
				}
			}
		}else if(recent_ptr->exponent() < exponent){
			if(recent_ptr->exponent() == 0){
				return UINT_MAX;
			}
			return recent_ptr->exponent();
		}
		return UINT_MAX;
	}

	void polynomial::set_recent(unsigned int exponent) const
	{

		recent_ptr = head_ptr;
		while(recent_ptr->fore() != nullptr && recent_ptr->exponent() < exponent){
			recent_ptr = recent_ptr->fore();
		}
		if(exponent < recent_ptr->exponent() && recent_ptr->back() != nullptr ){
			recent_ptr = recent_ptr->back();
		}
	}

	double polynomial::eval(double x) const
	{
		double total = 0;
		recent_ptr = head_ptr;
		while(recent_ptr != nullptr){
			total += pow(x,recent_ptr->exponent()) * recent_ptr->coef();
			recent_ptr = recent_ptr->fore();
		}
		return total;
	}

	polynomial polynomial::derivative() const
	{
		polynomial p_prime;
		recent_ptr = head_ptr;
		while(recent_ptr != nullptr){
			if(recent_ptr->exponent() != 0){
				p_prime.assign_coef(recent_ptr->coef() * recent_ptr->exponent(), recent_ptr->exponent()-1);
			}
			recent_ptr = recent_ptr->fore();
		}
		return p_prime;
	}

	polynomial operator+(const polynomial& p1, const polynomial& p2)
	{
		polynomial p;
		unsigned int term = 0;
		p.assign_coef(p1.coefficient(0),0);
		term = p1.next_term(0);
		while(term != 0){
			p.assign_coef(p1.coefficient(term),term);
			term = p1.next_term(term);
		}	
		term = 0;
		p.add_to_coef(p2.coefficient(0),0);
		term = p2.next_term(0);
		while(term != 0){
			p.add_to_coef(p2.coefficient(term),term);
			term = p2.next_term(term);

		}

		return p;
	}

	polynomial operator-(const polynomial& p1, const polynomial& p2)
	{
		polynomial p;
		int term = 0;
		p.assign_coef(p1.coefficient(term),term);
		term = p1.next_term(term);
		while(term != 0){
			p.assign_coef(p1.coefficient(term),term);
			term = p1.next_term(term);
		}	
		term = 0;
		p.add_to_coef(-1 * p2.coefficient(term),term);
		term = p2.next_term(term);
		while(term != 0){
			p.add_to_coef(-1 * p2.coefficient(term),term);
			term = p2.next_term(term);

		}

		return p;
	}

	polynomial operator*(const polynomial& p1, const polynomial& p2)
	{		
		polynomial p;
		unsigned int p1Term = 0;
		unsigned int p2Term = 0;


		// iterate though p1 when p1Term = 0
		while(p2Term != 0){
			p.add_to_coef(p1.coefficient(0)*p2.coefficient(p2Term), p2Term);
			p2Term = p2.next_term(p2Term);
		}	
		p2Term = 0; 
		p1Term = p1.next_term(p1Term);
		p2Term = p2.next_term(p2Term);
		while(p1Term != 0){
			p.add_to_coef(p1.coefficient(p1Term)*p2.coefficient(0), p1Term);
			while(p2Term != 0){
				p.add_to_coef(p1.coefficient(p1Term)*p2.coefficient(p2Term),p2Term+p1Term);
				p2Term = p2.next_term(p2Term);
			}
			p1Term = p1.next_term(p1Term);
			p2Term = p2.next_term(0);

		}
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

	void polynomial::find_root( double& answer, bool& success, unsigned int& iterations, double guess, unsigned int maximum_iterations, double epsilon) const {

			
	}
}
