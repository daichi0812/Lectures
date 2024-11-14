/*
 *p10_3.c 15822108 情報テクノロジー 堀田大智
 */
#include<stdio.h>

int main(){
	int a=10, b=20, *p;
	double *q;
	
	printf("aの値 : %d\n", a);
	printf("aのアドレス : %p\n", &a);
	printf("bの値 : %d\n", b);
	printf("bのアドレス : %p\n", &b);
	printf("pの値 : %d\n", &p);
	printf("pのデータサイズ : %d bytes = %2d bits\n", (int)sizeof(p), (int)sizeof(p)*8);
	printf("qのデータサイズ : %d bytes = %2d bits\n", (int)sizeof(q), (int)sizeof(q)*8);
	printf("\n");
	
	p=&a;
	printf("pの値 : %p\n", p);
	printf("pが指すアドレスの内容 : %d\n", *p);
	printf("\n");
	
	*p=*p+100;
	
	printf("pの値 : %p\n", p);
	printf("pが指すアドレスの内容 : %d\n", *p);
	printf("aの値 : %d\n", a);
	printf("\n");
	
	p=&b;
	printf("pの値 : %p\n", p);
	printf("pが指すアドレスの内容 : %d\n", *p);
	printf("\n");
	
	*p=*p+100;
	
	printf("pの値 : %p\n", p);
	printf("pが指すアドレスの内容 : %d\n", *p);
	printf("bの値 : %d\n", b);
	printf("bのアドレス　: %p\n", &b);
	printf("/n");
	
	return 0;
}
	
