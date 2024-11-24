/*
 * p5_1.c 半角文字の入力
 */
 
 #include<stdio.h>
 
 int main(){
	 char moji;
	 
	 printf("半角文字を入力してください\n");
	 scanf("%c", &moji);
	 printf("%c\n", moji);
	 
	 return 0;
 }