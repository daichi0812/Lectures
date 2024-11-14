/*
 *p3_7.c do while 文の利用
 */
 #include<stdio.h>
 
 int main(){
	 int num,total;
	 total=0;
	 
	 do{
		 printf("整数値を入力 (0で終了) :\n");
		 scanf("%d",&num);
		 total=total+num;
		 printf("現合計:%d\n",total);
	 }while(num!=0);
	 return 0;
 }