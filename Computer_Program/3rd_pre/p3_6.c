/*
 *p3_6.c while文の利用　15822108 堀田大智
 */
 #include <stdio.h>
 
 int main(){
	 int num;
	 double cm,a;
	 num=-1;
	 cm=2.54;
	 
	 while(num!=0){
		 printf("インチ (0で終了) :");
		 scanf("%d", &num);
		 a=num*cm;
		 printf("センチ:%.2f\n",a);
	 }
	 return 0;
 }