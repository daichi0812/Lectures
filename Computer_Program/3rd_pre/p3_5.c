/*
 *p3_5.c while文の利用　15822108 堀田大智
 */
 #include <stdio.h>
 
 int main(){
	 int num,total;
	 num=-1;
	 total=0;
	 
	 while(num!=0){
		 printf("整数値を入力 (0で終了) :");
		 scanf("%d", &num);
		 total=total+num;
		 printf("現合計:%d\n",total);
	 }
	 return 0;
 }