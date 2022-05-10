// Computing Multiplicative Inverses
#include<stdio.h>

struct triplet {
    long int x;
    long int y;
    long int d;
};

struct triplet extended_euclidean(long int a, long int b) {
    
    struct triplet ans;

    if ( a < 0 || b < 0 || a >= b) {
        printf("Invalid input. a, b >= 0 and a >= b\n");
        ans.x = ans.y = ans.d = 0;
        return ans;
    }

    long int a_org = a, b_org = b;

    if ( b == 0 ) {
        printf("d = %ld, x = %d, y = %d\n", a, 1, 0);
        ans.x = 1;
        ans.y = 0;
        ans.d = a;
        return ans;
    }

    long int x2 = 1, x1 = 0, y2 = 0, y1 = 1;

    while (b > 0) {
        long int q = a / b;
        long int r = a - q*b;
        long int x = x2 - q*x1;
        long int y = y2 - q*y1;

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

    ans.x = x;
    ans.y = y;
    ans.d = d;

    return ans;
}

int main() {

    long int a, n;

    printf("Enter a and n: ");
    scanf("%ld %ld", &a, &n);

    struct triplet ans = extended_euclidean(a, n);

    if (ans.d > 1) {
        printf("Inverse for %ld does not exist in Z<%ld>\n", a, n);
    } else {
        printf("Inverse for %ld in Z<%ld> is %ld\n", a, n, (ans.x+n)%n);
    }
    
}
