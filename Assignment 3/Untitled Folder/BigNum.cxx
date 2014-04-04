// FILENAME: BigNum.cxx // This is the implementation file of the BigNum class 
#ifndef HW3_BIGNUM_CXX 
#define HW3_BIGNUM_CXX 
#include <algorithm>   // Provides copy function 
#include <cstdlib> 
#include <iostream> 
#include <string>
#include <cstring>
#include <cassert>
#include <exception>
#include "BigNum.h"
using namespace std;

namespace HW3
{
	BigNum::BigNum()
	{ 
		capacity = DEFAULT_CAPACITY;
		digits = new unsigned int[capacity];
		digits[0] = 0;
		positive = true;
		used = 1;

	}    

	BigNum::BigNum(int num)
	{
		capacity = DEFAULT_CAPACITY;
		digits = new unsigned int[capacity];
		used = 0;
		int newNum = num;

		if(num >= 0){
			positive = true;
		}else{
			positive = false;
			newNum *= -1;
		}
		int tmp =0;
		do{
			tmp = newNum%10;
			newNum /= 10;
			digits[used] = tmp;
			used++;
		}while(newNum > 0);



	}

	// Constructor that receives a string; leading 0's will be ignored
	BigNum::BigNum(const string& strin)
	{
		string temp = strin;
		if(temp.substr(0,1) == "-"){
			positive = false;
			temp = temp.substr(1);
		}else{
			if(temp.substr(0,1) == "+"){
				temp = temp.substr(1);
			}
			positive = true;
		}
		capacity = DEFAULT_CAPACITY;
		digits = new unsigned int[capacity];
		used = 0;
		//remove random characters;

		for(int i = 0; i< '0' ; i++){
			char a = i;
			temp.erase (remove(temp.begin(), temp.end(),a ), temp.end());
		}
		for(int j = '9'+1; j < '~'; j ++){
			char a = j; 
			temp.erase (remove(temp.begin(), temp.end(),a ), temp.end());
		}
		//insert digits into digits array		
		do{
			if(used >= capacity){
				(*this).resize(capacity*2);
			}
			digits[used] = stoi(temp.substr(temp.length()-1));
			temp = temp.substr(0,temp.length()-1);

			used++;
		}while(temp != "");
		(*this).trim();

	}

	BigNum::BigNum(const BigNum& anotherBigNum)
	{
		positive = anotherBigNum.positive;
		capacity = anotherBigNum.capacity;
		used = anotherBigNum.used;
		unsigned int* d = new unsigned int[anotherBigNum.capacity];
		copy(anotherBigNum.digits,anotherBigNum.digits+anotherBigNum.capacity, d);
		digits = d;
	}

	BigNum::~BigNum()
	{
		delete [] digits;
	}

	void BigNum::resize(unsigned int n)
	{
		unsigned int* d = new unsigned int[n];
		copy(digits,digits+capacity, d);
		delete [] digits;
		digits = d;
		capacity = n;
	}

	BigNum& BigNum::operator=(const BigNum& anotherBigNum)
	{
		if(this != &anotherBigNum){

			positive = anotherBigNum.positive;
			capacity = anotherBigNum.capacity;
			unsigned int* d = new unsigned int[anotherBigNum.capacity];
			copy(anotherBigNum.digits,anotherBigNum.digits+anotherBigNum.capacity, d);
			if(!(digits == NULL)){
				delete [] digits;
			}
			used = anotherBigNum.used;
			digits = d;

		}

		return *this;

	}


	BigNum& BigNum::operator+=(const BigNum& addend)  
	{

		*this = *this + addend;
		return *this;
	}

	BigNum& BigNum::operator-=(const BigNum& subtractand)
	{

		*this = *this - subtractand;
		return *this;
	}

	BigNum& BigNum::operator*=(const BigNum& multiplicand)
	{

		*this = *this * multiplicand;
		return *this;
	}

	BigNum& BigNum::operator/=(const BigNum& divisor)
	{

		*this = *this / divisor;
		return *this;
	}

	BigNum& BigNum::operator%=(const BigNum& divisor)
	{

		*this = *this % divisor;
		return *this;
	}

	BigNum& BigNum::operator++()
	{
		BigNum tmp = 1;
		(*this) += tmp;
		return *this;
	}

	BigNum& BigNum::operator--()
	{
		BigNum tmp = 1;
		*this = *this - tmp;
		return *this;
	}

	BigNum& BigNum::diff(const BigNum& a, const BigNum& b)
	{
		return *this;
	}


	BigNum& BigNum::mult(const BigNum& a, const BigNum& b)
	{
		return *this;
	}

	BigNum& BigNum::sum(const BigNum& a, const BigNum& b) 
	{
		return *this;
	}

	BigNum operator+(const BigNum& a, const BigNum& b)
	{
		BigNum result;


		if(a.positive && !b.positive){
			BigNum tmp = b;
			tmp.positive = true;
			result = a-tmp;
		}else if(!a.positive && b.positive){
			BigNum tmp1 = a;
			tmp1.positive = true;
			result = b-tmp1;
		}else if(a.positive && b.positive){
			int carry =0;
			BigNum b1 = b;
			BigNum a1 = a;

			if(a>=b){
				result.used = a1.used;
				while(result.used > result.capacity){
					result.resize(result.capacity*2);
				}
				for(unsigned int i = 0; i < b1.used; i++){
					if(a1.digits[i] + b1.digits[i] + carry >= 10){
						result.digits[i] = (a1.digits[i] + b1.digits[i] + carry)%10;
						carry = (a1.digits[i] + b1.digits[i] + carry)/10;
					}else{
						result.digits[i] = (a1.digits[i] + b1.digits[i] + carry);
						carry = 0;
					}
				}
				for(unsigned long k = b1.used; k < a1.used+1; k++){
					if(k == a1.used){
						if(carry > 0){
							if(result.used+1 > result.capacity){
								result.resize(result.capacity*2);
							}

							result.digits[k] = carry;
							result.used++;
						}
					}else{
						if(a1.digits[k] + carry >= 10){
							result.digits[k] = (a1.digits[k]  + carry)%10;
							carry = (a1.digits[k] + carry)/10;
						}else{
							result.digits[k] = (a1.digits[k]  + carry);
							carry = 0;
						}
					}
				}	

			}else{
				result = b+a;
			}


		}else if(!a.positive && !b.positive){
			BigNum tmp1 = a;
			BigNum tmp2 = b;
			tmp1.positive = true;
			tmp2.positive = true;
			result = tmp1 + tmp2;
			result.positive = false;
		}



		//		result.trim();	

		return result;
	}

	BigNum operator-(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		if(a.positive && !b.positive){
			BigNum tmp = b;
			tmp.positive = true;
			result = a + tmp;
		}else if(!a.positive && b.positive){
			BigNum tmp1 = a;
			tmp1.positive = true;
			result = tmp1 + b;
			result.positive = false;
		}else if(!a.positive && !b.positive){
			BigNum tmp1 = a;
			tmp1.positive = true;
			BigNum tmp2 = b;
			tmp2.positive =true;
			result = tmp2-tmp1;
		}else if(a.positive && b.positive){

			if(a < b){
				result = b-a;
				result.positive = false;		
			}else{
				
				BigNum a1 = a;
				BigNum b1 = b;
				int * aDigits = new int[a.capacity];
				int * bDigits = new int[b.capacity];
				copy(a.digits, a.digits+a.used, aDigits);
				copy(b.digits, b.digits+b.used, bDigits);
				result.used = a.used;
				while(result.used >= result.capacity){
				
					result.resize(result.capacity*2);
				}
				for(unsigned int i = 0; i < b1.used; i++){
					if((aDigits[i] - bDigits[i]) < 0){
						aDigits[i] +=10;
						aDigits[i+1]--;
						result.digits[i] = aDigits[i] - bDigits[i];
					}else{
						result.digits[i] = aDigits[i] - bDigits[i];
					}
				}
				for(unsigned int k = b1.used; k < a1.used; k++){
					if(aDigits[k] < 0){
						aDigits[k] += 10;
						aDigits[k+1]--;
						result.digits[k] = aDigits[k];
					}else{
						result.digits[k] = aDigits[k];
					}

				}
				delete [] aDigits;
				delete [] bDigits;
			}	
		}
		//mini trim
		unsigned int w = result.used-1;
		while(result.digits[w] ==0 && w > 0){
			result.used--;
			w--;
		}

		return result;
	}

	BigNum operator*(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		if(a.used>=b.used){
			//result.used = a.used+b.used;
			result.resize(a.capacity + b.capacity + 1);
			BigNum * tmp ;
			result.clear();
			for(unsigned int i = 0; i < b.used; i++){

				tmp = new BigNum(0);
				tmp->used = a.used+i+1;
				if(tmp->used >= tmp->capacity){
					tmp->resize(tmp->used+2);
				}
				for(unsigned int k = 0; k < tmp->used; k++){
					//this loop is to remove garbage
					tmp->digits[k] = 0;
				}
				bool carried = false;
				for(unsigned int j = 0; j < a.used; j++){
					if(b.digits[i]*a.digits[j] < 10){
						if(carried){
							tmp->digits[j+i] += b.digits[i]*a.digits[j];
						}else{
							tmp->digits[j+i] = b.digits[i]*a.digits[j];
						}
						carried = false;

					}else{
						if(carried){
							tmp->digits[j+i] +=(b.digits[i]*a.digits[j])%10;
						}else{
							tmp->digits[j+i] =(b.digits[i]*a.digits[j])%10;
						}
						carried = true;
						tmp->digits[j+i+1] =(b.digits[i]*a.digits[j])/10;
					}
				}	
				result += *tmp;
				delete tmp;
			}

		}else{
			result = b*a;
		}
		//mini trim
		unsigned int w = result.used-1;
		while(result.digits[w] ==0 && w > 0){
			result.used--;
			w--;
		}
		//sets whether it will be positive or negative
		if(a.positive && b.positive){
			result.positive = true;	
		}else if(!a.positive && !b.positive){
			result.positive = true;	
		}else if(!a.positive && b.positive){
			result.positive = false;
		}else if(a.positive && !b.positive){
			result.positive = false;
		}
		if(a == 0 || b == 0){
			result.positive = true;
		}
		return result;
	}

	BigNum operator / (const BigNum& a, const BigNum& b)
	{
		BigNum result;

		if(b == 0){
			try{
				throw 40;
			}catch(int e){
				cerr << "ERROR:Divide by zero.";
			}	
		}
		if(a == 0){
			return 0;
		}

		BigNum a2 = a;
		BigNum b2 = b;
		b2.positive = true;
		a2.positive = true;



		int numOfDiv =0;
		while(a2 >= 0){
			a2 -= b2;
			numOfDiv++;
		}
		numOfDiv--;
		BigNum result2 = numOfDiv;
		result = result2;



		if(a.positive && b.positive){
			result.positive = true;	
		}else if(!a.positive && !b.positive){
			result.positive = true;	
		}else if(!a.positive && b.positive){
			result.positive = false;
		}else if(a.positive && !b.positive){
			result.positive = false;
		}
		if(a == 0){
			result.positive = true;
		}
		return result;
	}


	BigNum operator%(const BigNum& a, const BigNum& b)
	{
		BigNum result;

		if(b == 0){
			try{
				throw 40;
			}catch(int e){
				cerr << "ERROR:Divide by zero.";
			}
		}
		if(a==0){
			return 0;
		}
		BigNum a2 = a;
		BigNum b2 = b;
		b2.positive = true;
		a2.positive = true;
		while(a2 >= 0){
			result = a2;
			a2 -= b2;

		}
		//%'s result's sign is based soley on 'a'
		if(result == 0){
			result.positive = true;
		}else {
			result.positive = a.positive;
		}

		return result;
	}
	bool operator>(const BigNum& a, const BigNum& b)
	{
		if(a.positive && !b.positive){
			return true;
		}else if(!a.positive && b.positive){
			return false;
		}else if(!a.positive && !b.positive){
			if(a.used < b.used){
				return true;
			}else if(a.used > b.used){
				return false;
			}else if(a.used == b.used){
				int i = a.used;
				while (i > 0) {
					i--;
					if (a.digits[i] == b.digits[i]){
					}
					else if (a.digits[i] < b.digits[i]){
						return true;
					}
					else{
						return false;
					}
				}
			}


		}else if(a.positive && b.positive){
			if(a.used > b.used){
				return true;
			}else if(a.used < b.used){
				return false;
			}else if(a.used == b.used){
				int i = a.used;
				while (i > 0) {
					i--;
					if (a.digits[i] == b.digits[i]){
					}
					else if (a.digits[i] > b.digits[i]){
						return true;
					}
					else{
						return false;
					}
				}

			}


		}





		return false;
	}



	bool operator<(const BigNum& a, const BigNum& b)
	{
		if(a.positive && !b.positive){
			return false;
		}else if(!a.positive && b.positive){
			return true;
		}else if(!a.positive && !b.positive){
			if(a.used > b.used){
				return true;
			}else if(a.used < b.used){
				return false;
			}else if(a.used == b.used){
				int tmp = a.used-1;
				do{

					if(a.digits[tmp] == b.digits[tmp]){
						tmp--;	
					}else if(a.digits[tmp] >  b.digits[tmp]){
						return true;
					}else{
						return false;

					}


				}while(tmp >=0);


			}


		}else if(a.positive && b.positive){
			if(a.used < b.used){
				return true;
			}else if(a.used > b.used){
				return false;
			}else if(a.used == b.used){
				int tmp = a.used-1;
				do{

					if(a.digits[tmp] == b.digits[tmp]){
						tmp--;	
					}else if(a.digits[tmp] <  b.digits[tmp]){
						return true;
					}else{
						return false;

					}


				}while(tmp >=0);


			}


		}






		return false;
	}

	bool operator>=(const BigNum& a, const BigNum& b)
	{
		return (a > b || a == b);
	}


	bool operator<=(const BigNum& a, const BigNum& b)
	{
		return (a < b || a == b);;
	}


	bool operator==(const BigNum& a, const BigNum& b)
	{
		return (!(a<b) && !(a>b));
	}


	bool operator!=(const BigNum& a, const BigNum& b)
	{
		return (!(a == b)); }

	// trim leading zeros
	void BigNum::trim()
	{
		unsigned int w = used-1;
		while(digits[w] ==0 && w > 0){
			used--;
			w--;
		}

	}

	void BigNum::clear(){
		for(unsigned int i = 0; i < capacity; i ++){
			digits[i] = 0;
		}
	}	
	std::ostream& operator<<(std::ostream &os, const BigNum& bignum)
	{
		if(bignum.positive == false){
			os << "-" << "";

		}
		for(int i = bignum.used-1; i >=0; i--){
			os << bignum.digits[i] << "";
		}
		return os;
	}	 

	std::istream& operator>>(std::istream &is, BigNum& bignum)
	{
		string line ;
		is >> line;
		BigNum temp = BigNum(line);
		bignum = temp;
		return is;
	}

	BigNum factorial(const BigNum& a)
	{
		BigNum result = 1;
		if(a > 0){
			for(BigNum i = a; i >1; --i){
				result *= i;
			}
		}else{
			try{
				throw 30;
			}catch(int e){
				cerr << "ERROR: Factorial of negative number.";
			}
		}	
		return result;
	}
}



#endif
