// El-Gamal Cryptosystem

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long int lli;
typedef unsigned long long int ulli;

// gcd
lli gcd(lli a, lli b){
    if(a<b){ // a should be bigger , so swap
        lli t = a;
        a = b;
        b = t;
    }
    if(a%b == 0){return b;}
    else{
        return gcd(b, a%b);
    }
}

// Modulus Exponentiation
lli modulusExpo(lli base, lli expo, lli n){
    lli ans = 1;
    base = base % n;

    while(expo > 0){
        if(expo & 1){//odd
            ans = (ans * base) % n;
        }
        expo = expo >> 1;
        base = (base * base) % n;
    }

    return ans;
}

// Miller conditon
// This function is a prerequisite for the Miller-Rabin test
int millerCondition(lli d, lli n){
    lli a = 2 + rand()%(n-4);
    lli x = modulusExpo(a, d, n);
    if(x == 1 || x == n-1){return 1;}

    while(d != n-1){
        x = (x*x)%n;
        d *= 2;
        if(x == 1){return 0;}
        if(x == n-1){return 1;}
    }
    return 0;
}

int millerRabin(lli x, lli iter){
    if(x<=1 || x==4){return 0;}
    if(x<=3){return 1;}

    lli d = x-1;
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

lli getGenerator(lli p, lli *primeFactors, int k)
{
    lli a;
    lli n = p - 1;

    while (1)
    {
        a = rand()%(p-1) + 1; // [1, p-1]
        for (int i = 0; i < k; i++)
        {
            lli b = pow(a, n / primeFactors[i]);
            if (b == 1)
            {
                break;
            }
        }
        return a;
    }
}


lli getkBitInt(int k){
    ulli x = 0;
    while( k > 0 ){
        x |= rand()%2;
        x <<= 1;
        k--;
    }
    x |= 1;
    return x;
}

lli random_search(int k, lli iter){
    lli p;
    int B[] = {3, 5, 7, 11, 13, 17, 19}; // Assume 19 smooth
    int lenB = sizeof(B)/sizeof(B[0]);

    while(1){
        while (1)
        {   
            int passTest = 1;
            p = getkBitInt(k);

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
        
        if(millerRabin(p, iter)){
            printf("Returing from random search %lld\n", p);
            return p;
        }
    }
}

void selectPrimeAndGenerator(int k, lli t, lli *p, lli *alpha){
    lli q;
    while (1)
    {
        q = random_search(k-1, t);
        *p = 2*q+1;
        if(q>t && millerRabin(*p, t)){
            break;
        }

    }
    printf("Selected Prime %lld\n", *p);

    lli n = 2*q;
    while (1)
    {
        *alpha = rand()%(*p-1) + 1; // [1, p-1]
        lli b = pow(*alpha, 2);
        if (b == 1){continue;}

        b = pow(*alpha, q);
        if (b == 1){continue;}

        break;
    }

    printf("Selected generator %lld\n", *alpha);
    printf("test generator %lld\n", modulusExpo(*alpha, n, *p));
} 

void encryption(int m, lli p, lli alpha, lli publicKey, lli *c1, lli *c2){
    lli k;
    do{
        k = rand()%(p-2)+1; // [1, p-2]
    }
    while(gcd(k, p) != 1);

    printf("Private Key for encryption: %lld\n", k);
    *c1 = modulusExpo(alpha, k, p);
    *c2 = (m * modulusExpo(publicKey, k, p)) % p;
}

int decryption(lli c1, lli c2, lli p, lli alpha, lli privateKey){
    lli tmp = modulusExpo(c1, p-1-privateKey, p);
    return (tmp * c2) % p;
}

int main(){
    srand(137);
    int m = 2035;

    /*
    lli p, alpha;
    lli t = 13;
    int k = 16;
    selectPrimeAndGenerator(k, t, &p, &alpha);
    */
    // The above lines were used to generate p and alpha

    lli p = 2357, alpha = 2;
    printf("Initial setup p=%lld and alpha=%lld\n\n", p, alpha);
    
    lli privateKey = 1751;
    lli publicKey = modulusExpo(alpha, privateKey, p);
    printf("Private key of A: %lld \nPublic Key of A %lld\n", privateKey, publicKey);

    lli gamma, delta;
    // gamma = a ^ k mod p
    // delta = m * alpha ^ ak mod p
    printf("\nB Encrypts the message = %d using the public key of A\n", m);
    encryption(m, p, alpha, publicKey, &gamma, &delta);
    printf("Cipher Text: (%lld, %lld)\n", gamma, delta);

    int dm = decryption(gamma, delta, p, alpha, privateKey);
    // m = (gamma ^ (p - 1 - a)) * delta mod p
    printf("\nA decrypts the message using its private key=%lld\n", privateKey);
    printf("Decrypted message = %d\n", dm);
}