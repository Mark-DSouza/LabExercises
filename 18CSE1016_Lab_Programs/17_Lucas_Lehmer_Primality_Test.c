// Lucas-Lehmer primality test
#include<stdio.h>
#include<math.h>

int main() 
{
    long int s;
    printf("Enter 's' for a Mersenne number n = 2^s - 1 (s>=3): ");
    scanf("%ld", &s);

    long int n = (2 << s - 1) -1;

    printf("%ld\n", n);

    long int sqrt_s = sqrt(s);

    for(long int i=2; i<=sqrt_s; i++) {
        if( s % i == 0 ) {
            printf("Composite\n");
            return 0;
        }
    }

    // printf("s is prime\n");


    long int u = 4;
    for(long int k=1; k<=s-2; k++ ) {
        u = (u*u - 2) % n;
    }

    if(u==0) {
        printf("Prime\n");
    } 
    else {
        printf("Composite\n");
    }
}