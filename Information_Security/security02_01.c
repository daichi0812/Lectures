/*
15822108 堀田大智
ユークリッド互除法
*/
#include<stdio.h>

int gcd(int a, int b);

int main(){
    int a, b;

    printf("2つの自然数をカンマで区切って入力してください\n");
    scanf("%d, %d", &a, &b);
    printf("%dと%dの最大公約数は%dです。", a, b, gcd(a,b));

    return 0;
}

int gcd(int a, int b){
    int c;

    while(b!=0){
        c=a%b;
        a=b;
        b=c;
    }
    
    return a;
}

