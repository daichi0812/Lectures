#include <stdio.h>
#include <math.h>

int main(){
    int i;
    double n, a1, a2, a3;

    for(i = 1; i <= 6; i++ ){
        n = pow(10, i);
        a1 = pow(n, 1.2);
        a2 = log2(pow(n, n));
        a3 = pow(1.01, n);

        printf("%.3f, %.3f,  %.3f,  %.3f\n", 5 * n, a1, a2, a3);
        printf("\n");

    }

    return 0;
}