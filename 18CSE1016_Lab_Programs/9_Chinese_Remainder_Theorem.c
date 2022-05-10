// Chinese Remainder Theorem
#include<stdio.h>
#include<stdlib.h>

struct triplet {
    long int x;
    long int y;
    long int d;
};

struct triplet extended_euclidean(long int a, long int b) {
    
    struct triplet ans;

    if ( a < 0 || b < 0 || a < b) {
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

int main() {
    // r equations
    int r;

    printf("Enter the number of equations: ");
    scanf("%d", &r);

    long int *x_arr = malloc(r*sizeof(long int));
    long int *a_arr = malloc(r*sizeof(long int));
    long int *n_arr = malloc(r*sizeof(long int));

    long int *N_arr = malloc(r*sizeof(long int));
    long int *X_arr = malloc(r*sizeof(long int));


    long int n = 1;

    for(int i=0; i<r; i++) {
        printf("Enter ai and ni for equation %d: ", i+1);
        scanf("%ld %ld", &a_arr[i], &n_arr[i]);
        n *= n_arr[i];
    }


    for(int i=0; i<r; i++) {
        N_arr[i] = n / n_arr[i];
        long int inv;
        if(n_arr[i] > N_arr[i]) {
            inv = extended_euclidean(n_arr[i], N_arr[i]).y;
        } else {
            inv = extended_euclidean(N_arr[i], n_arr[i]).x;
        }
        
        X_arr[i] = (inv+ n_arr[i]) %  n_arr[i];

    }



    // finally, compute the solution

    long int ans = 0;

    for(int i=0; i<r; i++) {
        ans += a_arr[i] * N_arr[i] * X_arr[i];
    }

    if(ans > 0) {
        ans = ans % n;
    } else {
        ans += n * -(ans/n);
    }

    printf("Final answer is %ld\n", ans);




}