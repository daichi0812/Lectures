/*
 * p5_10.c 文字列の入出力 15822108 堀田大智
 */
 #include<stdio.h>
 
 int main(){
	 char ss[80];
	 
	 printf("半角の文字列(空白なし)を入力してください\n");
	 scanf("%s", ss);
	 printf("%s\n", ss);
	 
	 return 0;
 }