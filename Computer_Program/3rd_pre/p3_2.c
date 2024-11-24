/*
 *p3_2.c　for分の利用 15822108 堀田大智
 */
 #include <stdio.h>
 
 int main(){
	 
	 int i,j,num=1;
	 
	 for(i=1; i<=20; i++){
		 for(j=0; j<5; j++){
			 
		 printf("%5d",num);
		 num=num+1;
		 
		 }
		 printf("\n");
	 }
	 
	 return(0);
 }