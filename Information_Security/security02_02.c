/*
15822108 堀田大智
拡張ユークリッド互除法
*/
#include<stdio.h>
#include<math.h>

int gcd(int a, int b);

int main(){
    int a, b;

    printf("2つの自然数を大きい順に、カンマで区切って入力してください\n");
    scanf("%d, %d", &a, &b);
    printf("%dと%dの最大公約数は%dです。", a, b, gcd(a,b));

    return 0;
}

int gcd(int a, int b){
    int x0, x1, x2, y0, y1, y2, r0, r1, r2, q;

    r0 = a;
    r1 = b;
    x0 = 1;
    y0 = 0;
    y1 = 1;

    while(r1>0){
        q = floor(r0 / r1);
        r2 = r0 % r1;
        x2 = x0 - q * x1;
        y2 = y0 - q * y1;
        r0 = r1;
        r1 = r2;
        x0 = x1;
        x1 = x2;
        y0 = y1;
        y1 = y2;
    }
    
    return r0;
}