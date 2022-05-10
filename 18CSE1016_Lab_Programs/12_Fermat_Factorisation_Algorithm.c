// Fermat's Factorisation Algorithm
#include<stdio.h>
#include<math.h>

int main() {
    // even = 2 * (even/2)
    // odd = (a+b)*(a-b)

    long int n;
    printf("Enter an integer for factorizing: ");
    scanf("%ld", &n);

    if ( n & 1 == 0) {
        // last bit 0 => even
        printf("A factor is 2");
    } else {
        // odd

        // first guess for a = ceil of sqrt of number
        // next guess = a+1, then a+2, ...

        long int a = ceil(sqrt(n));


        while(1) {
            printf("Guess for a: %ld  ", a);

            long int b_sqr = a*a - n;
            // printf("Resulting b_sqr: %ld\n", b_sqr);

            // if b_sqr is perfect square, then we found factors a+b, a-b

            long int b = sqrt(b_sqr) +0.5; // ensures proper rounding to nearest integer
            printf("Resulting b: %ld\n", b);


            if ( b*b == b_sqr) {
                printf("A factor of %ld: %ld\n", n,  a+b);
                return 0;
            }

            a++;

        }



    }
}