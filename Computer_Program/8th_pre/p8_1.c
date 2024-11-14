/*
 *p8_1.c 再帰関数による階乗の計算 15822108 情報テクノロジー　堀田大智
 */
#include<stdio.h>

int factorial(int n);

int main(){
	int n;
	
	printf("階乗を求めたい整数値を入力してください: ");
	scanf("%d", &n);
	printf("%dの階乗は%dです\n", n, factorial(n));
	return 0;
}

int factorial(int n){
	if(n>1){
		return n*factorial(n-1);
	}
	else{
		return 1;
	}
}
 