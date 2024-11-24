/*
 *p11_6.c 15822108 情報テクノロジー 堀田大智
 */
#include<stdio.h>
#include<stdlib.h>

typedef struct{
	char c;
	int num;
}my_data;

int main(){
	my_data d={'a', 10}, *p;
	
	printf("dのアドレス : %p\n", &d);
	printf("dのサイズ : %d\n", (int)sizeof(d));
	printf("d.c のアドレス : %p\n", &d.c);
	printf("d.c のサイズ : %d\n", (int)sizeof(d.c));
	printf("d.c の値 : %c\n", d.c);
	printf("d.num のアドレス : %p\n", &d.num);
	printf("d.num のサイズ : %d\n", (int)sizeof(d.num));
	printf("d.num の値 : %d\n\n", d.num);
	
	p=(my_data *)calloc(1, sizeof(my_data));
	p->c='p';
	p->num=100;
	printf("pのアドレス : %p\n", &p);
	printf("pのサイズ : %d\n", (int)sizeof(p));
	printf("p の値 : %p\n", p);
	printf("p のメンバ変数 c　の値 : %c\n", p->c);
	printf("p のメンバ変数 num の値 : %d\n", p->num);
	
	return 0;
}