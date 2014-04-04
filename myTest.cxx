#include <iostream>
#include <cstdlib>
#include "BigNum.h"
#include <cstdio>
#include <cstdlib>
#include <signal.h>
#include <fstream>
#include <cstring>

using namespace std;
using namespace HW3;

void tester1(){
	BigNum a, b;
        
        cout << "Let's talk about comparisons: " << endl;
        cout << "This one tests greater/less than, and equality!" << endl;	
        cout << "Please input a number (Test for istream): ";
		cin >> a;
		cout << "Please put in another number: ";
        cin >> b;
        
        cout << "These are your two numbers right? (Test for ostream): ";
        cout << a << " " << b << endl;
        
        cout << endl;
        
        if(a > b)
			cout << "The first number is bigger!" << endl;
		else if(b < a)
			cout << "The second number is bigger!" << endl;
		else if(a == b)
			cout << "The two numbers are equal!" << endl;
		else
			cout << "Something went wrong!" << endl;
		
		cout << endl;
		
		cout << "This one tests greater than or equal to!" << endl;	
		cout << "Now give me a new number: ";
		cin >> a;
		cout << "And another one please: ";
        cin >> b;
        
        cout << endl;
        
        if(a >= b)
			cout << "The first number is bigger or equal!" << endl;
		else
			cout << "The second number is smaller!" << endl;
			
		cout << endl;
		
		cout << "This one tests less than or equal to!" << endl;	
		cout << "Now give me a new number: ";
		cin >> a;
		cout << "And another one please: ";
        cin >> b;
        
        cout << endl;
        
        if(a <= b)
			cout << "The first number is smaller or equal!" << endl;
		else 
			cout << "The first number is bigger!" << endl;
		
		cout << endl;
		
		cout << "This one tests non-equality!" << endl;
		cout << "Now give me a new number: ";
		cin >> a;
		cout << "And another one please: ";
        cin >> b;
        
        cout << endl;
        
        if(a == b)
			cout << "The two numbers are equal!" << endl;
		else if(a != b)
			cout << "They aren't equal!" << endl;
		else
			cout << "Something went wrong!" << endl;
		
}
int main()
{
    
	tester1();

    return 0;
}
