/*
 *p10_1.c 変数のアドレスとサイズの確認 15822108 情報テクノロジー 堀田大智
 */
#include<stdio.h>

int main(){
	int n=10;
	
	printf("n の値 : %d\n", n);
	printf("n の値を保存しているメモリのアドレス : %p\n", &n);
	printf("n の値を保存しているメモリ領域のサイズ : %d\n", (int)sizeof(n));
	
	return 0;
}