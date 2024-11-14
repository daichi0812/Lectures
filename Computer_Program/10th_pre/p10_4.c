/*
 *p10_4.c 15822108 情報テクノロジー 堀田大智
 */
#include<stdio.h>

int main(){
	int a[]={1, 2, 3, 4, 5}, i, *p;
	
	printf("aのアドレス : %p\n", a);
	printf("aのサイズ : %d\n", (int)sizeof(a));
	for(i=0; i<5; i++){
		printf("a[%d]の値 : %d\n", i, a[i]);
		printf("a[%d]のアドレス : %p\n", i, &a[i]);
	}
	
	for(p=a, i=0; i<5; i++){
		printf("p+%d の値 : %p\n", i, p+i);
		printf("p+%d の指すアドレスの内容 : %d\n", i, *(p+i));
	}
	
	for(p=a, i=0; i<5; i++){
		printf("pの値 : %p\n", p);
		printf("pの指すアドレスの内容 : %d\n", *p);
		p++;
	}
	
	return 0;
}