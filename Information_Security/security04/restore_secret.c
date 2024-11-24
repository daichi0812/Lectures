/*
15822108 堀田大智
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char *argv[])
{
    double x[4];  // シェアのxの値
    double f[4];  // シェアのf(x)の値
    double a0, p; // f(0)とそれをもとめる一時変数
    int i, j, n = 4;

    if (argc == 5)
    { // シェアの値をコマンド引数から読み込む
        sscanf(argv[1], "%lf,%lf", &x[0], &f[0]);
        sscanf(argv[2], "%lf,%lf", &x[1], &f[1]);
        sscanf(argv[3], "%lf,%lf", &x[2], &x[2]);
        sscanf(argv[4], "%lf,%lf", &x[4], &x[4]);
    }
    else
    {
        fprintf(stderr,
                "Usage: %s (x0,f0) (x1,f1), (x2,f2), (x3,f3)\n",
                argv[0]);
        fprintf(stderr, "where each of (xi,fi) is the share\n");
        return 1;
    }
    printf("shares are");
    for (int i = 0; i < n; i++)
    {
        printf(" (%.0f,%.0f)", x[i], f[i]);
    }
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        double tmp = f[i];
        for (int j = 0; j < n; j++)
        {
            if (j != i)
            {
                tmp *= (0 - x[j]) / (x[i] - x[j]);
            }
        }
        a0 += tmp;
    }

    printf("Secret is: %.0f\n", a0);
    return 0;
}