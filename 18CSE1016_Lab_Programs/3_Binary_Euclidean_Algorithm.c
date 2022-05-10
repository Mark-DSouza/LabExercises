// Binary Euclidean algorithm to find the GCD of two large integers.
#include<stdio.h>
#include<stdlib.h>

int main() {
    long int x, y;

    printf("Enter x and y: ");
    scanf("%ld %ld", &x, &y);

    if ( x < 0 || y < 0 || x < y) {
        printf("Invalid input. x, y >= 0 and x >= y\n");
        return 0;
    }

    long int x_org = x, y_org = y;

    long int g = 1;

    // while x and y are both even
    while ( x % 2 == 0 && y % 2 == 0) {
        x = x/2;
        y = y/2;
        g = 2*g;
    }

    while(x != 0) {

        while(x%2 == 0) {
            x = x/2;
        }

        while(y%2 == 0) {
            y = y/2;
        }

        long int t = abs(x-y)/2;

        if(x>=y) {
            x = t;
        } else {
            y = t;
        }
    }

    printf("GCD(%ld, %ld) = %ld\n", x_org, y_org,  g*y);

    return 0;
    
}