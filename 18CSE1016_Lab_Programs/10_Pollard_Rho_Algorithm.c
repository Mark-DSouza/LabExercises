// Pollard Rho Algorithm for Factoring Integers
#include<stdio.h>
#include<stdlib.h>

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

int main() {
    long int n;
    printf("Enter a composite integer that is not a prime power: ");
    scanf("%ld", &n);

    long int a = 2, b = 2;
    long int c = 1;

    int i = 1;
    while(1) {
        a = (a*a + c) % n;
        b = (b*b + c) % n;
        b = (b*b + c) % n;

        long int d = gcd(a-b, n);

        if( 1 < d && d < n) {
            printf("A non-trivial factor of %ld: %ld\n", n, d);
            return 0;
        }

        if( d == n) {
            printf("Algorithm failed to find a non-trivial factor of %ld\n", n);
            return 0;
        }

        i++;
    }
}