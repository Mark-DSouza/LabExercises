#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>

using namespace std;

// gcd
long long int gcd(long long int a, long long int b){
    if(a<b){ // a should be bigger , so swap
      swap(a, b);
    }

    if(a%b == 0){return b;}
    
    else{
      return gcd(b, a%b);
    }
}

// Modulus Exponentiation
long long int modulusExponentiation(long long int base, long long int exponent, long long int n){
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

// miller conditon
int millerCondition(long long int d, long long int n){
  long long int a = 2 + rand()%(n-4);
  long long int x = modulusExponentiation(a, d, n);
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

void selectPrimeAndGenerator(int k, long long int t, long long int &p, long long int &alpha){
  //We want p-1 to have a large prime factor q
  long long int q;
  while (1)
  {  
    // q would be k-1 bit to a k bit integer
    q = generateKBitPrime(k-1, t);
    p = 2*q+1;

    // q should be greater than t(security parameter)
    if(q>t && millerTest(p, t)){
        break;
    }
  }
  cout << "Selected Prime " << p << endl;

  // The factors of p-1 are 2 and q
  long long int n = 2*q;
  while (1)
  {   
    // Generate a rand no between 1 and p-1
    alpha = rand()%(p-1) + 1; // [1, p-1]

    // for each factor compute b=pow(alpha, n/pi)
    
    //factor q, n/q == 2
    long long int b = pow(alpha, 2);
    if (b == 1){continue;}
    //factor 
    b = pow(alpha, q);
    if (b == 1){continue;}

    break;
  }

  cout << "Selected generator " << alpha << endl;
} 

void encryption(int m, long long int p, long long int alpha, long long int publicKey, long long int &c1, long long int &c2){
  long long int k;
  do{
      k = rand()%(p-2)+1; // [1, p-2]
  }
  while(gcd(k, p) != 1);

  cout << "Private Key for encryption: " << k << endl;
  c1 = modulusExponentiation(alpha, k, p);
  c2 = (m * modulusExponentiation(publicKey, k, p)) % p;
}

int decryption(long long int c1, long long int c2, long long int p, long long int alpha, long long int privateKey){
  long long int tmp = modulusExponentiation(c1, p-1-privateKey, p);
  return (tmp * c2) % p;
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

void signMessage(int m, long long int privateKey, long long int &r, long long int &s, long long int p, long long int alpha){ 
    //Input: m, A's private key
    //Output: r, s
    
    long long int k;
    do{
        k = rand()%(p-2) + 1; // [1, p-2];
    }
    while(gcd(k, p-1) != 1);

    //compute r
    r = modulusExponentiation(alpha, k, p);

    //compute k inverse
    long long int k_inv = multiplicativeInverseOfN(k, p-1);

    long long int ts = ((m - (privateKey * (r)))) % (p-1);
    ts = (ts + p-1) % (p-1);
    ts = k_inv * (ts);

    s = ts;
}

bool verify(int m, long long int publicKey, long long int r, long long int s, long long int p, long long int alpha){
    // input: (r, s) on m
    // output: true or false

    if(r >= 1 && r <= p-1){
        long long int v1 = (modulusExponentiation(publicKey, r, p) * modulusExponentiation(r, s, p)) % p;
        long long int v2 = modulusExponentiation(alpha, m, p);
        return (v1 == v2);
    }
    else{
        return false;
    }

}

int main(){
  srand(time(0));
  long long int p, alpha;
  long long int t = 13;
  int k = 16;
  cout << "Selecting Prime and Generator" << endl;
  selectPrimeAndGenerator(k, t, p, alpha);
  
  cout << "Setup prime is " << p << " and alpha is " << alpha << endl << endl;
  
  long long int privateKey = rand()%(p-2) + 1; // private key belongs to [1, p-2];
  long long int publicKey = modulusExponentiation(alpha, privateKey, p);
  cout << "Private key of A: " << privateKey << endl;
  cout << "Public Key of A (" << p << ", " << alpha << ", " <<  publicKey << ")" << endl;

  int message = 2049; // message

  long long int r, s;
  signMessage(message, privateKey, r, s, p, alpha);
  cout << "Signature of A : (" << r << ", " << s << ")" << endl;

  // Verifying that A is the actual sender of the message
  bool ans = verify(message, publicKey, r, s, p, alpha);
  if(ans){
    cout << "Verified" << endl;
  }
  else{
    cout << "Not verified" << endl;
  }
}