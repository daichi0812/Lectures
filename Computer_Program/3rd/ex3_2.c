/*
 * ex3_2 15822108　堀田大智
 */
 #include <stdio.h>
 
 int is_prime(int n);
 int get_positive_integer(void);
 
 int main(){
	 
	 int num;
	 int a;
	 
	 printf("正の整数値を入力してください :");
	 
	 num=get_positive_integer();
	 
	 if(is_prime(num)==1){
		 printf("%dは素数ではありません",num);
		 }else{
			 printf("%dは素数です",num);
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
 
 int get_positive_integer(){
	 
	 int num;
	 
	 scanf("%d", &num);
	 
	 while(num<=0){
		 printf("%dは正の整数値ではありません\n");
		 printf("正の整数値を入力してください: ");
		 scanf("%d",&num);
	 }
	 return num;
 }
	 
	 
	 
	 