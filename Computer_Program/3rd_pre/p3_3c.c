/*
 *p3_3c.c　for分の利用 15822108 堀田大智
 */
 #include <stdio.h>
 
 int main(){
	 
	 int i, num, a;
	 a=1;
	 
	 printf("正の整数値を入力してください : ");
	 scanf("%d",&num);
	 
	 for(i=0; i<num; i++){
		 
		 a=a*(i+1);
	 }
	 
	 printf("%d!=%d", num, a);
	 
	 return(0);
 }