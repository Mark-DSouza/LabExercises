#include<bits/stdc++.h>
using namespace std;

// fucntion to find (a^k)mod n
long long int moduloExponentiation(long long int a, long long int k, long long int n){
    long long int k_bits = log(k)/log(2) + 1, temp, i = 0, b = 1, A;
    long long int k_bits_array[k_bits];

    if(k==0){
        return b;
    }

    temp = k;

    while(temp>0){
        k_bits_array[i] = temp&1;
        temp = temp>>1;
        i++;
    }

    A = a;

    if(k_bits_array[0]==1){
        b = a;
    }

    for(i=1;i<k_bits;i++){
        A = (A*A)%n;

        if(k_bits_array[i]==1){
            b = (A*b)%n;
        }
    }

    return b;
}

long long int miller_rabin(long long int d, long long int n)
{
    long long int a, x;
    a = 2 + rand()%(n-4);
    x = moduloExponentiation(a,d,n);


    if(x == 1 || x == n-1){
        return 1;
    }

    while(d != n-1)
    {
        x = (x*x)%n;
        d *= 2;

        if(x == 1){
            return 0;
        }

        if(x == n-1){
            return 1;
        }
    }

    return 0;
}

long long int prime_test(long long int n, long long int t)
{
    if(n <= 1 || n == 4){
        return 0;
    }

    if(n <= 3){
        return 1;
    }

    long long int d = n-1, i;

    while((d&1) == 0){
        d = d>>1;
    }

    for(i=0; i<t; i++)
    {
        if(!miller_rabin(d,n))
            return 0;
    }

    return 1;
}

long long int generatePrime()
{
    long long int num = 0, t = 11, flag = 0;

    while(!flag)
    {
        num = 2 + rand()%10000;
       
        flag = prime_test(num,t);
    }

    return num;
}

long long int gcd(long long int a, long long int b){
    if(a<b)
    { // a should be bigger , so swap
        long long int t = a;
        a = b;
        b = t;
    }
    if(a%b == 0)
    {
	    return b;
	}
    else
    {
        return gcd(b, a%b);
    }
}

int findingE(int phi)
{
    int i=1+rand()%phi;
    while(gcd(i,phi)!=1)
    {
        i = 1+rand()%phi;
    }
    return i;
}

// Function for extended Euclidean Algorithm
int gcdExtended(int a, int b, int* x, int* y);

// Function to find modulo inverse of a
int moduloInverse(int a, int m)
{
	int x, y;
	int g = gcdExtended(a, m, &x, &y);
	if (g != 1)
		return -1;
	else
	{
		
		// m is added to handle negative x
		int res = (x % m + m) % m;
		return res;
	}
}

// Function for extended Euclidean Algorithm
int gcdExtended(int a, int b, int* x, int* y)
{
	if (a == 0)
	{
		*x = 0, *y = 1;
		return b;
	}
	int x1, y1;
	int gcd = gcdExtended(b % a, a, &x1, &y1);

	*x = y1 - (b / a) * x1;
	*y = x1;

	return gcd;
}



int main()
{
	// long long p = generatePrime();  // first large, random prime
	// long long q = generatePrime();  // second large, random prime
  long long p = 2357;
  long long q = 2551;
	long long n = p*q;
	int phi = (p-1)*(q-1);
	int e = findingE(phi);
	cout<<"\nn: "<<n<<", phi:"<<phi<<", e:"<<e;
	int d = moduloInverse(e,phi);
	cout<<"\nd: "<< d << endl;
	cout<<"\nA's Public key => ("<<n<<", "<<e<<")";
	cout<<"\nA's Private key => "<<d << endl;
	int message = 5234673;
	int c = moduloExponentiation(message,e,n);
	cout<<"\nThe Cipher Text sent to A is => "<<c;
	int recoveredMessage = moduloExponentiation(c,d,n);
	cout<<"\nThe recoveredMessage is: "<<recoveredMessage << endl;

	return 0;
}