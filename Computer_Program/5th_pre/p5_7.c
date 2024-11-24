/*
 *p5_7.c 大文字から小文字への変換
 */
 #include<stdio.h>
 
 int lower2upper(int c);
 int upper2lower(int c);
 
 int main(){
	 int ch;
	 
	 printf("半角の英数字を入力してください : ");
	 ch=getchar();
	 printf("入力された文字 : %c\n", (char)ch);
	 printf("大文字への変換後の文字 : %c\n", (char)lower2upper(ch));
	 printf("小文字への変換後の文字 : %c\n", (char)upper2lower(ch));
	 
	 return 0;
 }
 
 int lower2upper(int c){
	 if('a'<=c&&c<='z'){
		 return c-32;
	 }
	 return c;
 }
 
 int upper2lower(int c){
	 if('A'<=c&&c<='Z'){
		 return c+32;
	 }
	 return c;
 }