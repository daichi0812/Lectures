/*
 *p5_18.c 数値文字列の入力 15822108 堀田大智
 */
 #include<stdio.h>
 #include<stdlib.h>
 
 int main(){
	 char input1[10], input2[20];
	 int a;
	 double b;
	 
	 printf("1つめの数値(整数)を入力:");
	 gets(input1);
	 printf("2つめの数値(実数)を入力: ");
	 gets(input2);
	 
	 printf("1つめの数値:%d\n", a=atoi(input1));
	 printf("2つめの数値:%f\n", b=atof(input2));
	 printf("%d+%.3f=%.3f\n", a, b, a+b);
	 
	 return 0;
 }