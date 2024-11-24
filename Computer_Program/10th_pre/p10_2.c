/*
 *p10_2.c 15822108 情報テクノロジー 堀田大智
 */
#include<stdio.h>

typedef struct{
	int a;
	int b;
}my_data;

int main(){
	my_data d={10, 20};
	
	printf("int型のデータサイズ :		   	%d bytes = %2d bits\n", (int)sizeof(int), (int)sizeof(int)*8);
	printf("unsigned int型のデータサイズ : 	%d bytes = %2d bits\n", (int)sizeof(unsigned int), (int)sizeof(unsigned int)*8);
	printf("char型のデータサイズ : 		   	%d bytes = %2d bits\n", (int)sizeof(char), (int)sizeof(char)*8);
	printf("long型のデータサイズ :			%d bytes = %2d bits\n", (int)sizeof(long), (int)sizeof(long)*8);
	printf("float型のデータサイズ : 		%d bytes = %2d bits\n", (int)sizeof(float), (int)sizeof(float)*8);
	printf("double型のデータサイズ : 		%d bytes = %2d bits\n", (int)sizeof(double), (int)sizeof(float)*8);
	printf("my_data型のデータサイズ : 		%d bytes = %2e bits\n", (int)sizeof(my_data), (int)sizeof(my_data)*8);
	
	printf("d のアドレス : %p\n", &d);
	printf("d.a のアドレス : %p\n", &d.a);
	printf("d.b のアドレス : %p\n", &d.b);
	
	return 0;
}