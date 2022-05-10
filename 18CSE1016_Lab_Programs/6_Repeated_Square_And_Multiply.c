// Repeated Square and Multiply
#include<stdio.h>

int main() {
    long int base, expo, n;

    printf("Enter the base(a), exponent(k) and n respectively: ");
    scanf("%ld %ld %ld", &base, &expo, &n);

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

    printf("Answer: %ld\n", b);
}