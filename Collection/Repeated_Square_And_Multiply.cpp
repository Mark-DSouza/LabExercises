// Repeated square and multiply
#include<stdio.h>
#include <iostream>
using namespace std;
long exponentiation(long a, long b)
{
	long temp = 1L;
	for(;b>0; b/=2)
	{
		if (b%2!=0)
			temp = (temp * a) % 1234;

		a = (a * a) % 1234;
	}
	
	return temp % 1234;
}

int main()
{
	long a = 5;
	long b = 596;
  // long a, b;
  // cout << "Enter base: ";
  // cin >> a;
  // cout << "Enter Exponent: ";
  // cin >> b;
	long modulo = exponentiation(a,b);
	printf("\nThe modulo: %ld", modulo);
}

