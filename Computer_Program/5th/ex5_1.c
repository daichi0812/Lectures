/*
 * ex5_1.c 15822108 情報テクノロジー　堀田大智
 */
 #include<stdio.h>
 
 int lower2upper(int c);
 int upper2lower(int c);
 
 int main(){
	 int ch;
	 
	 while((ch=getchar())!=EOF){
		if(97<=ch&&ch<=122){
			ch=lower2upper(ch);
			printf("%c", (char)ch);
		}else if('A'<=ch&&ch<='Z'){
			ch=upper2lower(ch);
			printf("%c", (char)ch);
		}else if(ch==10){
			putchar(ch);
		}else{
			ch='*';
			printf("%c", (char)ch);
		}
	 }
	 return 0;
 }
 
 int lower2upper(int c){
	 if(97<=c&&c<=122){
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