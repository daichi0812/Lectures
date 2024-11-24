/*
 *15822108 堀田大智
 */
 
 #include <stdio.h>
 
 int int_round(int n);
 
 int main() {
	 
	 int x;
	 
	 printf("整数を入力してください : ");
	 scanf("%d", &x);
	 
	 printf("一の位を四捨五入した結果 : %d\n", int_round(x));
	 
	 return 0;
 }
 
 int int_round(int n){
	 
	 int ans;
	 
	 if(n%10>4){
		 
		 int a=n%10;
		 
		 ans=n-a+10;
	 }else{
		 
		 int a=n%10;
		 
		 ans=n-a;
	 }
	 
	 return ans;
 }