// Rabin Cryptosystem

#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;

long long int moduloExponentiation(long long int a, long long int n, long long int p){
  long long int ans = 1;
  while(n>0){
      if(n&1){
          ans = (ans*a)%p;
      }
      n = n >> 1;
      a = (a*a)%p;
  }
  return ans;
}

int millerTest(long long int n ,long long int t){
  long long int r = n-1, s = 0;

  while(r%2 == 0){
    r = r/2;
    s++;
  }

  while(t--){
      int a = (rand() % (n-3)) + 2;
      int y = moduloExponentiation(a, r, n);
      if(y != 1 && y != (n-1)){
        int j = 1;
        while(j <= (s-1) && y != (n-1)){
          y = (y * y) % n;
          if(y == 1)
          return 0;
          j++;
        }
        if(y != (n-1))
        return 0;
      }
  }

  return 1;
}

long long int extendedEuclideanAlgo(
  long long int a, 
  long long int b, 
  long long int &x, 
  long long int &y
){
  if(a == 0){
    x = 0;
    y = 1;
    return b;
  }

  long long int temp=0 , temp1=0 ,temp2=0;
  temp = extendedEuclideanAlgo(b%a, a, temp1, temp2);
  x = temp2 - (b/a)*temp1;
  y = temp1;
  return temp;
}

long long int randomPrimeGenerator(long long int k , long long int t){
  long long int ans = 1 << (k-1);
  ans++;

  long long int temp = 1<<k;
  long long int diff = temp - ans;
  int rand_val = rand() % (diff+1);
  ans = ans | rand_val;
  int b[6] = {3 ,5 ,7, 11, 13, 17};
  for(int i = 0; i <= 5 ;i++){
      if(ans % b[i] == 0)
      return randomPrimeGenerator(k,t);
  }

  if(ans % 4 != 3) {
    return randomPrimeGenerator(k,t);
  }

  if(millerTest(ans,t)){
      cout << "The prime is " << ans << endl;
      return ans;
  }

  return randomPrimeGenerator(k,t);
}

void findingSquareRoots(long long int a, long long int p, long long int q, long long int n){
  long long int r = moduloExponentiation(a,(p+1)/4,p);
  long long int s = moduloExponentiation(a,(q+1)/4,q);
  long long int c = 0 , d = 0;
  long long int gcd = extendedEuclideanAlgo(p, q, c, d);
  long long int x = (r*d*q + s*c*p)%n;
  long long int y = (r*d*q - s*c*p)%n;
  long long int m1 = (x+n) % n;
  long long int m2 = (-x+n) % n;
  long long int m3 = (y+n) % n;
  long long int m4 = (-y+n) % n;
  cout << "The message is one of the following => " <<  m1 << " or " <<  m2 << " or " << m3 << " or " << m4;
}

int main(){
   
  // Generate two large random (and distinct) primes p and q
  long long int p = 0 , q = 0 ;
  srand(time(0));
  p = randomPrimeGenerator(7,5);
  q = randomPrimeGenerator(7,5);
  while(p == q){
      q = randomPrimeGenerator(7,5);
  }

  // A's public key is n
  long long int n = p*q;
  long long int message = 0;
  cout << "the public key is " << n << ", enter message to send (must be a number): ";
  cin >> message;
  
  // encryption 
  long long int c = (message*message) % n; // encrypted message (ciphertext)
  cout << "The ciphertext is " << c << endl;

  // decryption 
  findingSquareRoots(c, p, q, n);
  return 0;
}