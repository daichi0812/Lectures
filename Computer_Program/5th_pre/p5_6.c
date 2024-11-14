/*
 *p5_6.c 小文字から大文字への変換
 */
 #include<stdio.h>
 
 int lower2upper(int c);
 
 int main(){
	 int ch;
	 
	 printf("半角文字を入力してください : ");
	 ch=getchar();
	 printf("入力された文字 : %c\n", (char)ch);
	 printf("大文字への変換後の文字 : %c\n", (char)lower2upper(ch));
	 
	 return 0;
 }
 
 int lower2upper(int c){
	 if(97<=c&&c<=122){
		 return c-32;
	 }
	 return c;
 }