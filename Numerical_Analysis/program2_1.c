#include <stdio.h>

#define N 3
#define M 2

int main(){
	
	double a[N][M],b[N][M];
	
	int i,j;
	
	for(i=0; i<N; i++){
		for(j=0; j<M; j++){
			
			a[i][j]=(double)2.0*((i+1)+(j+1));
			b[i][j]=(double)3.0*((i+1)+(j+1));
		}
	}
			
	for(i=0; i<N; i++){
		for(j=0; j<M; j++){
			
			printf("%4.1f  ", a[i][j]+b[i][j]);
		}
		printf("\n");
	}
	
	return(0);
}