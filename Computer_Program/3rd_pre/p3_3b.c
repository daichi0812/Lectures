/*
 *p3_3b.c　for分の利用 15822108 堀田大智
 */
 #include <stdio.h>
 
 int main(){
	 
	 int i, num;
	 num=10;
	 
	 for(i=0; i<10; i++){
		 
		 printf("%3d",num);
		 num=num-1;
	 }
	 
	 return(0);
 }