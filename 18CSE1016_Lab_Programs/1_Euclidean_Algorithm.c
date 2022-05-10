// Euclidean algorithm for finding the Greatest Common Divisor of two large integers.
#include<stdio.h>

int main() {
    long int a, b;

    printf("Enter a and b: ");
    scanf("%ld %ld", &a, &b);

    if ( a < 0 || b < 0 || a < b) {
        printf("Invalid input. a, b >= 0 and a >= b\n");
        return 0;
    }

    long int a_org = a, b_org = b;

    while (b != 0)
    {
        long int r = a % b;
        a = b;
        b = r;
    }

    printf("GCD(%ld,%ld) = %ld\n", a_org, b_org, a);
    
}