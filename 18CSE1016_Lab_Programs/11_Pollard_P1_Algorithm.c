// Pollard's p-1 Algorithm for Factoring Integers
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

long int gcd(long int a, long int b) {

    a = abs(a);
    b = abs(b);

    // swap if necessary
    if ( a < b) {
        long int temp = a;
        a = b;
        b = temp;
    }

    long int a_org = a, b_org = b;

    while (b != 0)
    {
        long int r = a % b;
        a = b;
        b = r;
    }

    // printf("GCD(%ld,%ld) = %ld\n", a_org, b_org, a);
    return a;
    
}

// trivial method
int is_prime(long int n) {
    long int lim = sqrt(n);

    for(long int i=2; i<= lim; i++) {
        if(n%i == 0) {
            return 0;
        }
    }

    return 1;
}

// repeated square and multiply 
long int modular_expo(long int base, long int expo, long int n) {

    long int b = 1;
    if( expo == 0) {
        printf("Answer: %ld\n", b);
        return 0;
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
    long int n;
    printf("Enter a composite integer that is not a prime power: ");
    scanf("%ld", &n);

    long int B = 19; // smoothness bound ( >= largest prime in factorization)

    printf("Enter the smoothness bound B (>= largest prime in factorization): ");
    scanf("%ld", &B);

    // seed the random number generator
    srand(time(NULL));

    // range for a => [ 0 to n-3 ] + 2 => [ 2 to n-1 ]
    long int a = (rand() % (n - 2)) + 2;

    printf("Chosen a: %ld\n", a);

    
    long int d = gcd(a, n);

    if( d >= 2) {
        printf("A non-trivial factor of %ld: %ld\n", n,  d);
        return 0;
    }


    for(long int q = 2; q <= B; q++) {
        if(is_prime(q)) {
            long int l = log(n) / log(q);

            long int expo = (long int) ( pow(q, l) + 0.5 ); // +0.5 and then automatic floor due to truncation
                                                            // ensures rounding to nearest integer
            a = modular_expo(a, expo, n);

            printf("q: %ld l: %ld, a: %ld\n", q, l, a);
        }
    }

    d = gcd(a-1, n);

    if( d == 1 || d == n) {
        printf("Algorithm failed to find a non-trivial factor of %ld\n", n);
    } else {
        printf("A non-trivial factor of %ld: %ld\n", n,  d);
    }

    return 0;

}