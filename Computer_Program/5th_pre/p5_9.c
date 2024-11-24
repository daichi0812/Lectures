/*
 * p5_9.c EOFまでの入力 15822108 堀田大智
 */
 #include<stdio.h>
 
 int main(){
	 int ch;
	 
	 while((ch=getchar())!=EOF){
		 if(ch==10){
			 putchar(ch);
		 }else{
			 printf("%c(%d)", (char)ch, ch);
		 }
	 }
	 
	return 0;
 }