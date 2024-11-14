/*
 *p3_13.c グロ－バル変数の確認 15822108　堀田大智
 */
 #include<stdio.h>
 
 void my_func(int n);
 int n=10;
 
 int main(){
	 printf("n(global)in main():%d\n",n);
	 my_func(n);
	 printf("n(global) in main():%d\n",n);
	 
	 return 0;
 }
 
 void my_func(int n){
	 n=n-5;
	 printf("n(local) in my_func(): %d\n", n);
 }
 