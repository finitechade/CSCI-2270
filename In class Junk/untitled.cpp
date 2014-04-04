/*
 * untitled.cxx
 * 
 * Copyright 2014 Unknown <joey@arch>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>
#include <algorithm>
using namespace std;
void bleach(int lol)
{
	cout << lol << endl;
}



int main()
{
	int myButtHole = 69;
	int* a = new int[10];

	a[0] = 1;
	int* newthing = new int[20];
	copy(a,a+10,newthing);
	delete [] a;
	bleach(newthing[0]);
	bleach(myButtHole);
	
}



