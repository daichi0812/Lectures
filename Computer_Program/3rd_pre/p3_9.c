/*
 *p3_9.c ローカル変数の確認 15822108　堀田大智
 */
 #include<stdio.h>
 
 void my_func(void);
 
 int main(){
	 int n=20;
	 
	 printf("n in main(): %d\n",n);
	 my_func();
	 
	 return 0;
 }
 
 void my_func(void){
	 int n;
	 
	 printf("n in my_func(): %d\n", n);
 }
 