/*
 * p5_2.c 半角文字の入出力(getchar() purchar()の利用　15822108 堀田大智
 */
 #include<stdio.h>
 
 int main(){
	 int ch;
	 
	 printf("半角文字を入力してください\n");
	 ch=getchar();
	 putchar(ch);
	 
	 return 0;
 }