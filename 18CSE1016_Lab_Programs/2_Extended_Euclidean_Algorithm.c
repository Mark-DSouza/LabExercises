// Extended Euclidean algorithm for finding the GCD of two large integers.
#include <stdio.h>

int main() {
    long int a, b;

    printf("Enter a and b: ");
    scanf("%ld %ld", &a, &b);

    // a = bq + r

    if ( a < 0 || b < 0 || a < b) {
        printf("Invalid input. a, b >= 0 and a >= b\n");
        return 0;
    }

    int a_org = a, b_org = b;

    if ( b == 0 ) {
        printf("d = %ld, x = %ld, y = %ld\n", a, 1L, 0L);
        return 0;
    }

    int x2 = 1, x1 = 0, y2 = 0, y1 = 1;

    while (b > 0) {
        int q = a / b;
        int r = a - q*b;
        int x = x2 - q*x1;
        int y = y2 - q*y1;

        a = b;
        b = r;
        x2 = x1;
        x1 = x;
        y2 = y1;
        y1 = y;
    }

    long int d = a;
    long int x = x2;
    long int y = y2;

    printf("d = %ld, x = %ld, y = %ld\n", d, x, y);

    // =12*5*7 = 420
    // =12*13*22 = 3432

    return 0;

}