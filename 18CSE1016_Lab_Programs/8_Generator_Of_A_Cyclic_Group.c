// Finding the generator of a Cyclic Group
#include<stdio.h>
#include<math.h>

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
        // printf("d = %ld, x = %d, y = %d\n", a, 1, 0);
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

    // printf("d = %ld, x = %ld, y = %ld\n", d, x, y);

    ans.x = x;
    ans.y = y;
    ans.d = d;

    return ans;
}

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

long int calculate_phi(long int n) {

    long int phi = n;

    int k;
    printf("How many unique primes in factorization of n: ");
    scanf("%d", &k);

    for(int i=0; i<k; i++) {
        long int p;
        printf("Enter prime p%d: ", i+1);
        scanf("%ld", &p);
        phi = phi * (p-1) / p; // since 1 - 1/p == (p-1)/p
    }

    return phi;
}


int main() {
    // order => least positive integer for which a^t === 1 (mod n), 
    // check t from {set of divisors of phi(n)} because t | phi(n)
    // phi(n) = n . (1-1/p1) . (...)

    long int n;

    printf("Enter value for n: ");
    scanf("%ld", &n);

    // 1. Get value of phi(n)
    long int phi = calculate_phi(n);

    // check for every possible a (i.e. element of Zn*)
    for(int a = 1; a < n; a++) {
        // if a is not part of Zn*, ignore
        struct triplet ans = extended_euclidean(a, n);
        if (ans.d > 1) {
            continue;
            // printf("Inverse for %ld does not exist in Z<%ld>\n", a, n);
        } 

        // 2. Iterate 2...phi and check if order
        for(long int t = 2; t <= phi; t++) {
            if(phi % t == 0 && modular_expo(a, t, n) == 1) {
                // t here is the order.
                if( t == phi) {
                    printf("%d is a generator\n", a);
                } 
                break;
            }
        }
    }

    return 0;
}