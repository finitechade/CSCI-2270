#include "MyClass.cxx"


// Pass by value
void fun1(MyClass a)
{
	a.setX(1);
}


// Pass by reference
void fun2(MyClass& a)
{
	a.setX(2);
}



// Pass by pointer
void fun3(MyClass* a)
{
	a->setX(3);
}


// Using double pointers! Coz why stop at single pointers? :)
void fun4(MyClass** a)
{
	(*a)->setX(4);
}



int main() 
{
	MyClass a;
	MyClass* b;
	MyClass** c;
	
	cout << endl << "----Calling fun1----" << endl;
	
	fun1(a); 
	a.printX(); // Explaining output (1 point)	

	//This output is '0' because the method 'fun1' takes in 'a' by value. So, when the 'setX()' method is called in the fun1 method the object that is changed is 
	//destroyed once the method ends. In addition, it is zero because the default constructor of the object sets the value of x  to 0 




	cout << endl << "----Calling fun2----" << endl;	
	
	fun2(a); 
	a.printX(); // Explaining output (1 point)
	//This output is 2 because the method is changing the object a by reference, meaning that is changes the value of x in the memory location of the object 'a'

	
	cout << endl << "----Calling fun3----" << endl;
	
	b = &a;     // Fixing compile error (1 point)
	fun3(b);   
	a.printX(); // Explaining output (1 point)
	//Since b is referencing the location, and as a result the value, of 'a', we are essentially throwing a into the method 'fun3.' fun3 gets the value of 'a' by applying the '->'
	// operator on the pointer parameter. 
	//b->setX(3) is the same thing as (*b).setX(3). What this is doing is it is dereferencing the value of b to get the value of a and it then changes a's value of x to 3. 


	cout << endl << "----Calling fun4----" << endl;
	
	c = &b;    // Fixing compile error (1 point)
	fun4(c);    
	a.printX(); // Explaining output (1 point)
	// c now has the address of b which is pointing to a.  So c is a pointer to a pointer. C essentially has the value of a now, eventhough it appears that c it being assigned to the address of b.
	//Inside of the 'fun4' method, the first portion of the statement (*a) is getting the value of the a, which in this situation is the pointer b. Then the second portion, ->setX(4), 
	//is dereferencing the value of b to get the value of 'a' and then setting the value of 'a' 's  x value to 4
	
	//Dereferencing using single pointer
	cout << "\n\nTwo ways of dereferencing, \n1. Using '.' operator\n2. Using '->' operator\n\n";
	
	
	 (*b).printX();          // Fixing compile error (1 point)
	 b->printX();      // Fixing compile error (1 point) 
	
	// These two lines do the same thing. (*b) dereferences the value of b. Also using the -> operator dereferences the object that is using the operator. So that means that (*b).printX() == b->printX()
	

	cout << "\n\n----Understanding arrays as pointers----" << endl;
	MyClass arr[5];
	
	arr[0].setX(10);
	arr[1].setX(20);
	arr[2].setX(30);
	arr[3].setX(40);
	arr[4].setX(50);
	
	cout << "----Running for loop for array variable 'arr' with 5 slots----" << endl << endl;
	
	//Explaining for loop (2 points)




	for (unsigned int i=0; i<5; i++) //this loops from 0 through 4
	{
		cout << "i = " << i << endl; //This line prints out the value of 'i'. 'i' can be [0,1,2,3,4]
		cout << "memory location (arr + i) = " << arr+i << endl; //This line prints out the memory location of each value of the array using pointer arithmetic. (The address of the array + the incrementation of i (4 because i is 4 bytes))
		cout << "  (*(arr + i)).printX() prints "; //Prints "(*(arr + i)).printX() prints"
		(*(arr+i)).printX(); //This prints out the value of X at the memory location of arr+i
		cout << "        arr[i].printX() prints "; // Prints "        arr[i].printX() prints "
		arr[i].printX(); //Prints out the value of X at the array location 'i'
		cout << endl; //Prints end line
	}
	
	
	
	return 0;


}

