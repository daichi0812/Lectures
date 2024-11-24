#include <stdio.h>
 
 #define N 5
 
 int main(void){
	 
	 double a[N],b[N],sum[N];
	 int i;
	 
	 for(i=0; i<N; i++){
		 a[i]=(double)i/20;
		 b[i]=(double)i/10;
		 sum[i]=a[i]+b[i];
	 }
	 
	 printf("a + b =\n");
	 
	 for(int j=0; j<N; j++){
		 printf("%.2f\n", sum[j]);
	 }
	 
	 return(0);
 }