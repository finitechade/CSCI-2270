// FILENAME: BigNum.cxx // This is the implementation file of the BigNum class 
#ifndef HW3_BIGNUM_CXX 
#define HW3_BIGNUM_CXX 
#include <algorithm>   // Provides copy function #include <cstdlib> #include <iostream> #include <string>
#include <cstring>
#include <cassert>
#include "BigNum.h"
using namespace std;

namespace HW3
{
	BigNum::BigNum()
	{ capacity = DEFAULT_CAPACITY;
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
			result = a-b;
		}else if(!a.positive && b.positive){
			result = b-a;
		}else if(a.positive && b.positive){
			int carry =0;
			BigNum b1 = b;
			BigNum a1 = a;
			
			if(a>=b){
				result.used = a1.used;
				result.resize(a.capacity+1);
				for(unsigned int i = 0; i < b1.used; i++){
					if(a1.digits[i] + b1.digits[i] + carry >= 10){
						result.digits[i] = (a1.digits[i] + b1.digits[i] + carry)%10;
						carry = (a1.digits[i] + b1.digits[i] + carry)/10;
					}else{
						result.digits[i] = (a1.digits[i] + b1.digits[i] + carry);
						carry = 0;
					}
				}
				for(unsigned int k = b1.used; k < a1.used+1; k++){
					if(k == a1.used){
						result.digits[k] = carry;
						result.used++;
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

		
		
		result.trim();	
		
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
			result = b-a;
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
					if(k == a1.used-1){
						if(aDigits[k] == 0){
							result.used--;
						}
					}else{
						if(aDigits[k] < 0){
							aDigits[k] += 10;
							aDigits[k+1]--;
							result.digits[k] = aDigits[k];
						}else{
							result.digits[k] = aDigits[k];
						}
					}


				}

			}	
		}

		
		
		
			return result;
	}
      
	BigNum operator*(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		result.used = a.used * b.used;
		if(a.positive && b.positive){
			result.positive = true;
		}else{
			if(!a.positive && !b.positive) {
				result.positive = true;
			}
			else {
				result.positive = false;
			}
		}
		BigNum tmp = 1;
		for(BigNum i = 0; i < b; i += tmp){
			result += a;
		}
		result.trim();
		cout << result;
		return result;
	}

	BigNum operator / (const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}


	BigNum operator%(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}

	bool operator>(const BigNum& a, const BigNum& b)
	{
		//if a is positive and b is negative return true
		if(a.positive && !b.positive){
			return true;
		}else{
			//if a is negative and b is positive return false
			if(!a.positive && b.positive){
				return false;
			}else{

				//if a is positive and b is negative find which one is larger
				if(a.positive && b.positive){
					//if a has more digis than b, return true
					if(a.used > b.used){
						return true;
					}else{
						//otherwise return false
						if(a.used < b.used){
							return false;
						}else{
							//if they have the same digits, compare each digit with the opposite number's equivelant 
							unsigned int count = a.used;
							do{
								count--;
								if(a.digits[count] > b.digits[count]){
									return true;
								}
							}while(count >=0);
						}
					}
				}else{
					if(!a.positive && !b.positive){
						//if a has less digits than b, return true
						if(a.used < b.used){
							return true;
						}else{
						//otherwise return false
							if(a.used > b.used){
								return false;
							}else{
								//if they have the same number of digits, compare each digit with the opposite number's equivelant 
								unsigned int count = a.used;
								do{
									count--;
									if(a.digits[count] < b.digits[count]){
										return true;
									}	
								}while(count >0);
							}
						}
					}
				}
			}
		}
		return false;
	}


	bool operator>=(const BigNum& a, const BigNum& b)
	{
		return (a > b || a == b);
	}


	bool operator<(const BigNum& a, const BigNum& b)
	{

		//if a is positive and b is negative return false
		if(a.positive && !b.positive){
			return false;
		}else{
			//if a is negative and b is positive return true
			if(!a.positive && b.positive){
				return true;
			}else{

				//if a is positive and b is positive find which one is smaller
				if(a.positive && b.positive){
					//if a has more digis than b, return true
					if(a.used < b.used){
						return true;
					}else{
						//otherwise return false
						if(a.used > b.used){
							return false;
						}else{
							//if they have the same digits, compare each digit with the opposite number's equivelant 
							unsigned int count = a.used;
							do{
								count--;
								if(a.digits[count] < b.digits[count]){
									return true;
								}
							}while(count >0);
						}
					}
				}else{
					if(!a.positive && !b.positive){
						//if a has less digits than b, return true
						if(a.used > b.used){
							return true;
						}else{
						//otherwise return false
							if(a.used < b.used){
								return false;
							}else{
								//if they have the same number of digits, compare each digit with the opposite number's equivelant 
								unsigned int count = a.used;
								do{
									count--;
									if(a.digits[count] > b.digits[count]){
										return true;
									}	
								}while(count >0);
							}
						}
					}
				}
			}
		}
		return false;
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
		if(used == 1 && digits[used]==0){
			
		}else{
			while(digits[used-1] == 0){
				used--;
				
			}
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
		BigNum result;
		return result;
    }
  }



#endif



