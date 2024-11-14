/*
15822108 堀田大智
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char* argv[]){
    double a3, a2, a1, a0;      //f(x)の秘密の係数
    double x, fx;               //c, f(x)の値
    int i, n=5;

    srand((unsigned int)time(NULL));

    if(argc == 5){              //もしコマンド引数に4個の数値が与えられたら
        a3 = atof(argv[1]);     //それを秘密の係数に使う
        a2 = atof(argv[2]);
        a1 = atof(argv[3]);
        a0 = atof(argv[4]);
    }  
    else if(argc == 1){         //コマンド引数がなければ乱数で発生させる
        a3 = round(((double)random() / (double)RAND_MAX) * 10.0 + 1.0);
        a2 = round(((double)random() / (double)RAND_MAX) * 20.0 - 10.0);
        a1 = round(((double)random() / (double)RAND_MAX) * 20.0 - 10.0);
        a0 = round(((double)random() / (double)RAND_MAX) * 20.0 - 10.0);
    }
    else{
        fprintf(stderr,"Usage: %s a3 a2 a1 a0\nwhere a0,...,a3 are secret number\n", argv[0]);
        return 1;
    }
    //1発生した秘密の係数を表示する
    printf("secrets are %.0f, %.0f, %.0f, %.0f\n", a3, a2, a1, a0);
    printf("shares are");

    //適当にxの値を増やしながらf(x)を計算し出力する
    for(i = 0, x = 0.0; i < n; i++){
        x += round(((double)random() / (double)RAND_MAX) * 10.0 + 1.0);
        fx = (((a3 * x) + a2) * x +a1) * x + a0;
        printf("%.0f, %.0f", x, fx);
    }
    printf("\n");
    return 0;
}