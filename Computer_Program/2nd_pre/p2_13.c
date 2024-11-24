/*
 *p2_13.c
 */
 #include <stdio.h>
 
 int power(int a, int b);
 
 int main(){
	 
	 int result;
	 
	 result=power(2,3);
	 printf("%d\n", result);
	 printf("%d\n", power(3,4));
	 
	 return(0);
 }
 
 int power(int a, int b){
	 
	 int n, ans;
	 
	 ans = 1;
	 for(n=1;n<=b;n++){
		 ans = ans * a;
	 }
	 
	 return ans;
 }