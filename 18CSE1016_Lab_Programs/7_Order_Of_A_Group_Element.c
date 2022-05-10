// Determining the order of a group element
#include<stdio.h>
#include<math.h>

long modular_expo(long int base, long int expo, long int n) {
    long int b = 1;
    if( expo == 0) {
        return b;
    }

    long int A = base;

    if( expo & 1 == 1) {
        b = base;
    }

    expo >>= 1; // right shift (division by 2)

    while ( expo ) { // fix this condition
        A = (A * A) % n;
        if(expo & 1 == 1) {
            b = (A * b) % n;
        }
        expo >>= 1;
    }

    return b;
}

int main() {
    // order => least positive integer for which a^t === 1 (mod n), 
    // check t from {set of divisors of phi(n)} because t | phi(n)
    // phi(n) = n . (1-1/p1) . (...)

    long int n, n_orig, a;

    printf("Enter value for n and a respectively: ");
    scanf("%ld %ld", &n, &a);

    // store original value of n
    n_orig = n;

    



    // 1. Get value of phi(n)
    long int phi = n;

    int k;
    printf("How many unique primes in factorization of n: ");
    scanf("%d", &k);

    for(int i=0; i<k; i++) {
        long int p;
        printf("Enter prime p%d: ", i+1);
        scanf("%ld", &p);
        phi = phi * (p-1) / p; // since 1 - 1/p == (p-1)/p
    }



    printf("Phi(n) = %ld\n", phi);

    // 2. Iterate 2...phi and check if order

    for(long int t = 2; t <= phi; t++) {
        if(phi % t == 0 && modular_expo(a, t, n) == 1) {
            printf("Order for element is %ld\n", t);
            break;
        }
    }

    return 0;
}