#include <stdio.h>
 
 #define N 5
 
 int main(void){
	 
	 double a[N];
	 int i;
	 
	 for(i=0; i<N; i++){
		 a[i]=i/2.0;
		 printf("a[%d]=%.3f \n", i, a[i]);
	 }
	 
	 return(0);
 }