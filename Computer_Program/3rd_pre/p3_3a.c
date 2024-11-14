/*
 *p3_3a.c　for分の利用 15822108 堀田大智
 */
 #include <stdio.h>
 
 int main(){
	 
	 int i,sum,num;
	 sum=50;
	 num=50;
	 
	 for(i=0; i<50; i++){
		 
		 num=num+1;
		 sum=sum+num;
	 }
	 
		 printf("50から100までの数の総和 : %d", sum);
	 
	 return(0);
 }