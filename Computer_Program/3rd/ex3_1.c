/*
 * ex3_1 15822108　堀田大智
 */
 #include <stdio.h>
 
 int is_prime(int n);
 
 int main(){
	 
	 int num;
	 int a;
	 
	 printf("正の整数値を入力してください :");
	 scanf("%d", &num);
	 
	 a=num;
	 
	 if(is_prime(a)==1){
		 printf("%dは素数ではありません", num);
		 }else{
			 printf("%dは素数です", num);
		 }
	 
	 return(0);
 }
 
 int is_prime(int n){
	 
	 int i,ans;
	 ans=0;
	 
	 for(i=2; i<n; i++){
		 
		 if(n%i==0){
			 ans=1;
		 }
	 }
	 return ans;
 }
	 
	 