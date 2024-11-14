/*
 *p3_8.c while文の利用　15822108 堀田大智
 */
 #include <stdio.h>
 
 int main(){
	 int num;
	 double cm,a;
	 num=-1;
	 cm=2.54;
	 
	 while(1){
		 printf("インチ (0で終了) :");
		 scanf("%d", &num);
		 
		 if(num!=0){
		 a=num*cm;
		 printf("センチ:%.2f\n",a);
		 }else{
			 printf("終了します");
			 break;
		 }
	 }
		 
	 return 0;
 }