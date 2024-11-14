/*
 * p4_13.c
 */
 
 #include<stdio.h>
 #include<stdlib.h>
 
 int main(){
	 int i, seed;
	 
	 printf("整数値を入力してください : ");
	 scanf("%d", &seed);
	 srand(seed);
	 printf("乱数の生成\n");
	 for(i=0; i<10; i++){
		 printf("%d\n",rand());
	 }
	 
	 return 0;
 }