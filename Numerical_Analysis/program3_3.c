#include <stdio.h>

double innerproduct(int a[3], int b[3]);

int main(){
	
	int a[3]={1,2,3};
	int b[3]={6,4,4};
	printf("a・b=%.1f\n",innerproduct(a,b));
	
	int c[3]={10,20,5};
	int d[3]={6,5,10};
	printf("c・d=%.1f\n",innerproduct(c,d));
	
	return 0;
}

double innerproduct(int a[3], int b[3]){
	
	double ans=0.0;
	
	for(int i=0; i<3; i++){
		ans=ans+a[i]*b[i];
	}
	return ans;
}
	
	