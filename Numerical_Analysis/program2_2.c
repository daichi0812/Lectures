#include <stdio.h>

#define N 3
#define M 2
#define n 2
#define m 3

int main(){
	
	double a[N][M],b[n][m];
	
	int i,j;
	
	for(i=0; i<N; i++){
		for(j=0; j<M; j++){
			
			a[i][j]=2.0*((i+1)+(j+1));
		}
	}
	
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			
			b[i][j]=3.0*((i+1)+(j+1));
		}
	}
	
	for(i=0; i<m; i++){
		for(j=0; j<m; j++){
			
			printf("%6.1f  ",a[i][0]*b[0][j]+a[i][1]*b[1][j]);
		}
		printf("\n");
	}
			
	return(0);
}