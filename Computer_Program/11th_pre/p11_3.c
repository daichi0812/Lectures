/*
 *p11_3.c 15822108 情報テクノロジー 堀田大智
 */
#include<stdio.h>
#include<stdlib.h>

int *mem_alloc(int n);

int main(){
	int *a;
	
	printf("a の内容 : %p\n", a);
	printf("a のアドレス : %p\n\n", &a);
	
	a=mem_alloc(0);
	
	printf("a の内容　: %p\n", a);
	printf("a のアドレス　: %p\n", &a);
	printf("a が指すアドレスの内容 : %d\n\n", *a);
	
	a=mem_alloc(1);
	
	printf("a の内容　: %p\n", a);
	printf("a のアドレス　: %p\n", &a);
	printf("a が指すアドレスの内容 : %d\n\n", *a);
	
	return 0;
}

int *mem_alloc(int n){
	int *p;
	
	if(n==0){
		p=(int *)malloc(sizeof(int));
	}else if(n==1){
		p=(int *)calloc(1, sizeof(int));
	}else{
		p=NULL;
	}
	
	if(p !=NULL){
		printf("p の内容 : %p\n", p);
		printf("p のアドレス : %p\n", &p);
		printf("p が指すアドレスの内容 : %d\n\n", *p);
		
		*p=10;
		printf("p が指すアドレスの内容 : %d\n\n", *p);
	}else{
		printf("メモリ領域の確保ができていません\n\n");
	}
	
	return p;
}
		