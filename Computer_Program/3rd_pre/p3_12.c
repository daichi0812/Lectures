/*
 *p3_12.c グロ－バル変数の確認 15822108　堀田大智
 */
 #include<stdio.h>
 
 void my_func(void);
 int n;
 
 int main(){
	 n=10;
	 printf("n(global)in main():%d\n",n);
	 my_func();
	 printf("n(global) in main():%d\n",n);
	 
	 return 0;
 }
 
 void my_func(void){
	 n=n-5;
	 printf("n(global) in my_func(): %d\n", n);
 }
 