// DllImprimir.cpp : Defines the exported functions for the DLL application.
//

#include "DllImprimir.h"

#include <iostream>

using namespace std;

int printSinF(string str)
{
	cout << str << endl;

	return 0;
}


int makeOperation(int a, int b)
{
	return a + b;
}