/*
 * 15822108 堀田大智
 */
 
 #include <stdio.h>
 
 int main(){
	 
	 int num1;
	 
	 printf("年を入力>");
	 scanf("%d", &num1);
	 
	 if(num1%100==0&&num1%400==0){
		 printf("%dはうるう年です\n", num1);
		 
	 }else if(num1%100==0){
		 printf("%dはうるう年ではありません\n", num1);
		 
	 }else if(num1%4==0){
		 printf("%dはうるう年です\n", num1);
		 
	 }else{
		 printf("%dはうるう年ではありません\n", num1);
	 }
		 
	 
	 return(0);
 }