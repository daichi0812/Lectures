/*
 *p3_10.c ローカル変数の確認 15822108　堀田大智
 */
 #include<stdio.h>
 
 void my_func(int m);
 
 int main(){
	 int n=20;
	 
	 printf("n in main(): %d\n",n);
	 my_func(n);
	 
	 return 0;
 }
 
 void my_func(int m){
	 int n;
	 
	 printf("n in my_func(): %d\n", n);
	 printf("m in my_func(): %d\n", m);
 }
 