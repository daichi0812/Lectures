#include <stdio.h>
 
 #define N 5
 
 int main(void){
	 
	 double a[N],b[N],mul[N],sum=0;
	 int i;
	 
	 for(i=0; i<N; i++){
		 a[i]=(double)i/20;
		 b[i]=(double)i/10;
		 mul[i]=a[i]*b[i];
		 sum=mul[i]+sum;
	 }
	 
	 printf("a,bの内積は\n");
	 printf("%.3f\n", sum);
	 
	 return(0);
 }