/*
 *p5_8.c 入力文字のチェック 15822108 堀田大智
 */
 #include<stdio.h>
 
 int lower2upper(int c);
 int upper2lower(int c);
 int input_alpha(void);
 
 int main(){
	 int ch;
	 
	 ch=input_alpha();
	 printf("入力された文字 : %c\n", (char)ch);
	 printf("大文字への変換後の文字 : %c\n", (char)lower2upper(ch));
	 printf("小文字への変換後の文字 : %c\n", (char)upper2lower(ch));
	 
	 return 0;
 }
 
 int lower2upper(int c){
	 if(97<=c&&c<=127){
		 return c-32;
	 }
	 return c;
 }
 
 int upper2lower(int c){
	 if(65<=c&&c<=90){
		 return c+32;
	 }
	 return c;
 }
 
 int input_alpha(void){
	 int d;
	 printf("英大文字もしくは英小文字を1文字入力してください　: ");
		 do{
			 d=getchar();
			 if(d==10){
				d=getchar();
			 }			
			if(d<'A' || 'Z'<d&&d<'a' || 'z'<d){
				printf("入力された文字は英大文字・小文字ではありません\n");
				printf("英大文字もしくは英小文字を1文字入力してください　: ");
			}
		 
		 }while(d<'A' || 'Z'<d&&d<'a' || 'z'<d);
		 
		 return d;
 }