/*
 * p4_14.c 15822108 堀田大智
 */
 
 #include<stdio.h>
 #include<stdlib.h>
 #include<time.h>
 
 int main(){
	 int i;
	 
	 srand((unsigned)time(NULL));
	 printf("乱数の生成\n");
	 for(i=0; i<10; i++){
		 printf("%d\n",rand());
	 }
	 return 0;
 }