// Fermat's Primality Test
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

long int modular_expo(long int base, long int expo, long int n) {
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

int main() 
{
    long int n, t;
    printf("Enter an odd integer n to be tested for primality (n>=3): ");
    scanf("%ld", &n);

    printf("Enter security parmater t (t>=1): ");
    scanf("%ld", &t);


    srand(time(NULL));

    for(long int i=0; i<t; i++) {
        // choose random intger a in [2,n-2]
        long int  a = rand() % (n-3) + 2;    // [0,n-4] + 2

        // if a^(n-1) === 1 mod n, then composite
        if ( modular_expo(a, n-1, n) != 1L) {
            printf("Composite\n");
            return 0;
        }


    }

    printf("Prime\n");

}