// Implement Diffie-Hellman Key Agreement Protocol

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

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

// modexp
lli mod_exp(lli b, lli e, lli n){
    lli ans = 1;
    b = b%n;

    while(e>0){
        if(e&1){//odd
            ans = (ans*b)%n;
        }
        e = e>>1;
        b = (b*b)%n;
    }
    return ans;
}

// miller conditon
int millercondition(lli d, lli n){
    lli a = 2 + rand()%(n-4);
    lli x = mod_exp(a, d, n);
    if(x == 1 || x == n-1){return 1;}

    while(d != n-1){
        x = (x*x)%n;
        d *= 2;
        if(x == 1){return 0;}
        if(x == n-1){return 1;}
    }
    return 0;
}
int millerrabbin(lli x, lli iter){
    if(x<=1 || x==4){return 0;}
    if(x<=3){return 1;}

    lli d = x-1;
    while (d%2==0)
    {
        d/=2;
    }

    while(iter>0){
        if(millercondition(d, x)==0){return 0;}
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


lli getkbitInt(int k){
    ulli x = 0;
    while(k>0){
        // printf("%d : %d\n", k, rand()%2);
        x |= rand()%2;
        x <<= 1;
        k--;
    }
    x |= 1;
    // printf("x=%d\n", x);
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
            p = getkbitInt(k);

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
        
        if(millerrabbin(p, iter)){
            // printf("Returing from random search %lld\n", p);
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
        if(q>t && millerrabbin(*p, t)){
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
    // printf("test generator %lld\n", mod_exp(*alpha, n, *p));
}


int main(){
    lli p, alpha;
    lli t = 13;
    int k = 12;
    selectPrimeAndGenerator(k, t, &p, &alpha);

    // lli p = 2357; 
    // lli a = 2;
    printf("Initial setup: p=%lld and a=%lld\n\n", p, alpha);

    lli x = rand() % (p-3) + 1; // pick x in range [1, p-2]
    lli ka = mod_exp(alpha, x, p);
    printf("A send %lld to B\n", ka);

    lli y = rand() % (p-3) + 1; // pick y in range [1, p-2]
    lli kb = mod_exp(alpha, y, p);
    printf("B send %lld to A\n", kb);

    lli kab = mod_exp(kb, x, p);
    printf("A computes shared key: %lld\n", kab);

    lli kba = mod_exp(ka, y, p);
    printf("B computes shared key: %lld\n", kba);

    return 0;
}