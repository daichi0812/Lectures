/*
 *p11_1.c 15822108 情報テクノロジー 堀田大智
 */
#include<stdio.h>
#include<stdlib.h>

int *mem_malloc(void);

int main(){
	int *a;
	
	printf("a の内容 : %p\n", a);
	printf("a のアドレス : %p\n\n", &a);
	
	a=mem_malloc();
	printf("a の内容 : %p\n", a);
	printf("a のアドレス : %p\n\n", &a);
	
	a=mem_malloc();
	
	printf("a の内容 : %p\n", a);
	printf("a のアドレス : %p\n", &a);
	printf("a が指すアドレスの内容 : %d\n", *a);
	
	return 0;
}

int *mem_malloc(void){
	int *p;
	
	p=(int *)malloc(sizeof(int));
	
	printf("a の内容 : %p\n", p);
	printf("a のアドレス : %p\n", &p);
	printf("a が指すアドレスの内容 : %d\n", *p);
	
	*p=10;
	printf("p が指すアドレスの内容 : %d\n\n", *p);
	
	return p;
}