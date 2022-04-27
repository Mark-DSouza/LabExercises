#include<bits/stdc++.h>
using namespace std;

// Modulus Exponentiation
long long int moduloExponentiation(long long int base, long long int exponent, long long int n){
  long long int answer = 1;
  base = base%n;

  while(exponent > 0){
    if(exponent & 1){//odd
      answer = (answer * base) % n;
    }
    exponent = exponent >> 1;
    base = (base*base)%n;
  }
  return answer;
}

int millerCondition(long long int d, long long int n){
  long long int a = 2 + rand()%(n-4);
  long long int x = moduloExponentiation(a, d, n);
  if(x == 1 || x == n-1){return 1;}

  while(d != n-1){
      x = (x*x)%n;
      d *= 2;
      if(x == 1){return 0;}
      if(x == n-1){return 1;}
  }
  return 0;
}

int millerTest(long long int x, long long int iter){
    if(x<=1 || x==4){return 0;}
    if(x<=3) {return 1;}

    long long int d = x-1;
    while (d%2==0)
    {
      d/=2;
    }

    while(iter>0){
      if(millerCondition(d, x)==0){return 0;}
      iter--;
    }

    return 1;
}

long long int generateKBitInteger(int k){
  unsigned long long int x = 0;
  while(k > 0){
    x |= rand() % 2;
    x <<= 1;
    k--;
  }
  x |= 1;
  return x;
}

long long int generateKBitPrime(int k, long long int iter){
  //Returns kbit pirme number
  long long int p;
  int B[] = {3, 5, 7, 11, 13, 17, 19}; // Assume 19 smooth
  int lenB = sizeof(B)/sizeof(B[0]);

  while(1){
    while (1) // First check within the Smooth bound
    {   
      int passTest = 1;
      p = generateKBitInteger(k);

      // check the smoothness bound
      for (int i=0; i < lenB; i++)
      {
        if (p % B[i] == 0)
        {   
          passTest = 0;
          break;
        }
      }
      if(passTest){break;}
    }
    
    if(millerTest(p, iter)){
      return p;
    }
  }
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

long long findingE(long long phi)
{
    long long i=1+rand()%phi;
    while(gcd(i,phi)!=1)
    {
        i = 1+rand()%phi;
    }
    return i;
}

long long int extendedGcd(long long int x, long long int y, long long int &a, long long int &b){
  // ax+by = gcd
  if(x==0){
    a = 0;
    b = 1;
    return y;
  }

  long long int a_, b_;
  long long int gcd = extendedGcd(y%x, x, a_, b_);

  a = b_ - (y/x) * a_;
  b = a_;
  return gcd;
}

long long int multiplicativeInverseOfN(long long int a, long long int n){
    long long int x1, y1;
    long long int gcd = extendedGcd(a, n, x1, y1);

    if(gcd == 1){
      // a x1 == 1(mod n) hence x1 is the inverse
      long long int ans = x1 % n;
      if(ans < 0){return (ans+n)%n; }
      return ans;
    }
    else{ // doesn't exist
      return -1;
    }

}

int main()
{
  long long p = generateKBitPrime(16, 10);  //first large, random prime
  long long q = generateKBitPrime(16, 10);  // second large, random prime

  // long long p = generateKBitPrime(30, 10);  //first large, random prime
  // long long q = generateKBitPrime(30, 10);  // second large, random prime
  cout << "p = " << p << "\t" << "q = " << q << endl;
	long long n = p*q;
	long long phi = (p-1)*(q-1);
	long long e = findingE(phi);
	cout<<"\nn: "<<n<<", phi:"<<phi<<", e:"<<e;
	long long d = multiplicativeInverseOfN(e,phi);
	cout<<"\nd: "<< d << endl;
	cout<<"\nA's Public key => ("<<n<<", "<<e<<")";
	cout<<"\nA's Private key => "<<d << endl;
	int message = 7435;
	int c = moduloExponentiation(message,e,n);
	cout<<"\nThe Cipher Text sent to A is => "<<c;
	int recoveredMessage = moduloExponentiation(c,d,n);
	cout<<"\nThe recovered Message is: "<<recoveredMessage << endl;

	return 0;
}