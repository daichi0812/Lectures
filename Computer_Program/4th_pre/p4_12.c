/*
 * p4_12.c 15822108 堀田大智
 */
 
 #include<stdio.h>
 #include<stdlib.h>
 
 int main(){
	 int i;
	 
	 printf("乱数の生成\n");
	 for(i=0; i<10; i++){
		 printf("%d\n", rand());
	 }
	 printf("RAND_MAX:%d\n", RAND_MAX);
	 return 0;
 }