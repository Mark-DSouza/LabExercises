// Miller Rabin Primality Test
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

    // n-1 = 2^s * r
    long int r = n-1, s = 0;
    while(  (r & 1) == 0) {
        r >>= 1;
        s++;
    }


    srand(time(NULL));

    for(long int i=0; i<t; i++) {
        // choose random intger a in [2,n-2]
        long int  a = rand() % (n-3) + 2;    // [0,n-4] + 2

        long int y = modular_expo(a, r, n);
        y = (y+n) % n;

        if ( y != 1 && y != n-1) {
            long int j = 1;
            while( j<=s-1 && y != n-1) {
                y = modular_expo(y,2,n);
                y = (y+n) % n;

                if(y == 1) {
                    printf("Composite\n");
                    return 0;
                }

                j++;
            }

            if( y != n-1 ) {
                printf("Composite\n");
                return 0;
            }
        }

    }

    printf("Prime\n");

}