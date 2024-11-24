/*
 *p3_11.c ローカル変数の確認 15822108　堀田大智
 */
 #include<stdio.h>
 
 void my_func(int n);
 
 int main(){
	 int n=20;
	 
	 printf("n in main(): %d\n",n);
	 my_func(n);
	 printf("n in main(): %d\n",n);
	 
	 return 0;
 }
 
 void my_func(int n){
	 n=n-5;
	 printf("n in my_func(): %d\n", n);
 }
 