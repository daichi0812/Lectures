/*
 * program4_14 15822108 堀田大智
 */
 
#include<stdio.h>

int main(){
	int n=1000000000;
	float sum1=0.0;
	float sum2=0.0;
	
	for(int i=1; i<=n; i++){
		sum1=sum1+1.0/i;
	}
	
	for(int i=n; i>=1; i--){
		sum2=sum2+1.0/i;
	}
	
	printf("昇順 sum(n=%d)=%f\n", n, sum1);
	printf("降順 sum(n=%d)=%f\n", n, sum2);
	
	return 0;
}