/*
 *p2_9.c 
 *情報テクノロジー学科 堀田大智
 */
 #include <stdio.h>
 
 int main(){
	 
	 int x,y;
	 
	 printf("整数を入力してください : ");
	 scanf("%d", &x);
	 if((y=x%10)>4){
		 x=x-y+10;
	 }
	 
	 printf("一の位を5以上で切り上げた結果 :%d\n", x);
	 
	 return(0);
 }
	 