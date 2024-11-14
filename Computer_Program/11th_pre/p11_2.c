/*
 *p11_2.c 15822108 情報テクノロジー 堀田大智
 */
#include<stdio.h>
#include<stdlib.h>

int *mem_calloc(void);

int main(){
	int *a;
	
	printf("a の内容 : %p\n", a);
	printf("a のアドレス : %p\n\n", &a);
	
	a=mem_calloc();
	
	printf("a の内容 : %p\n", a);
	printf("a のアドレス : %p\n", &a);
	printf("a が指すアドレスの内容 : %d\n\n", *a);
	
	return 0;
}

int *mem_calloc(void){
	int *p;
	
	p=(int *)calloc(1, sizeof(int));
	
	printf("p の内容 : %p\n", p);
	printf("p のアドレス : %p\n", &p);
	printf("p　が指すアドレスの内容 : %d\n", *p);
	
	*p=10;
	printf("p が指すアドレスの内容 : %d\n", *p);
	
	return p;
}