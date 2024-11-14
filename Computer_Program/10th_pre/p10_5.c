/*
 *p10_5.c
 */
#include<stdio.h>

void pass_by_value(int a);
void pass_by_address(int *a);

int main(){
	int a=100;
	
	printf("a の値 (in main) : %d\n", a);
	printf("a のアドレス　(int main) : %p\n\n", &a);
	
	pass_by_value(a);
	
	printf("Returned to main\n\n");
	printf("a の値 (in main) : %d\n", a);
	printf("a のアドレス　(int main) : %p\n\n", &a);
	
	pass_by_address(&a);
	
	printf("Returned to main\n\n");
	printf("a の値(in main) : %d\n", a);
	printf("a のアドレス (in main) : %p\n", &a);
	
	return 0;
}

void pass_by_value(int a){
	printf("Enter_pass_by_value\n\n");
	printf("a の値 (in_pass_by_value) : %d\n", a);
	printf("a のアドレス (in pass_by_value) : %p\n", &a);
	
	a += 10;
	
	printf("a の値 (in pass_by_value) : %d\n", a);
	printf("a のアドレス (in pass_by_value) : %p\n\n", &a);
}

void pass_by_address(int *a){
	printf("Enter pass_by_address\n\n");
	printf("a の値(in pass_by_address) : %p\n", a);
	printf("a のアドレス (in pass_by_address) : %p\n", &a);
	printf("a の指すアドレスの内容 (in pass_by_address) : %d\n", *a);
	
	*a+=10;
	
	printf("a の値(in pass_by_address): %p\n", a);
	printf("a のアドレス (in pass_by_address) : %p\n", & a);
	printf("a の指すアドレスの内容 (in pass_by_address) : %d\n\n", *a);
}