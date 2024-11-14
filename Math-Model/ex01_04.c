#include <stdio.h>
#include <math.h>
 
 #define N 5
 
 int main(void){
	 
	 double a[N],a2[N],sum=0;
	 int i;
	 
	 for(i=0; i<N; i++){
		 a[i]=(double)i/20;
		 a2[i]=(double)a[i]*a[i];
		 sum=sum+a2[i];
	 }
	 
	 printf("%f\n", sqrt(sum));
	 
	 return(0);
 }