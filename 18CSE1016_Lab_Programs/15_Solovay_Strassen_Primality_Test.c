// Solovay-Strassen Primality Test
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

int jacobi(long int a, long int n) {
    // n >= 3, 0 <= a < n

    if ( a == 0 || a == 1) {
        return a;
    }

    long int a1 = a, e = 0;
    while(  (a1 & 1) == 0) {
        a1 >>= 1;
        e++;
    }

    // printf("a:%ld a1:%ld e:%ld\n", a, a1, e);

    long int s;
    
    if(e % 2 == 0) {
        s = 1;
    }
    else if( n % 8 == 1 || n % 8 == 7) {
        s = 1;
    } 
    else {
        s = -1;
    }

    if( n%4 == 3 && a1%4 == 3) {
        s = -s;
    }

    long int n1 = n % a1;

    if(a1 == 1) {
        return s;
    }
    
    return s * jacobi(n1, a1);

}

int main() 
{
    long int n, t;
    printf("Enter an odd integer n to be tested for primality (n>=3): ");
    scanf("%ld", &n);

    printf("Enter security parmater t (t>=1): ");
    scanf("%ld", &t);


    // Making separate case so that choosing random number doesn't cause problem below
    if ( n == 3) {
        printf("Prime\n");
        return 0;
    }

    srand(time(NULL));

    for(long int i=0; i<t; i++) {
        // choose random intger a in [2,n-2]
        long int  a = rand() % (n-3) + 2;    // [0,n-4] + 2

        long int r = modular_expo(a, (n-1)/2, n);

        r = (r+n) % n;

        if( r != 1 && r != n-1 ) {
            printf("Composite\n");
            return 0;
        }

        long int s = jacobi(a,n);
        s = (s+n)%n;

        // printf("a:%ld r:%ld  s:%ld\n", a, r, s);

        if ( r != s) {
            printf("Composite\n");
            return 0;
        }


    }

    printf("Prime\n");
    return 0;

}