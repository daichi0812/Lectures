#include <stdio.h>

#define N 2
#define M 3

void add(int a[N][M], int b[N][M]);

int main(){
	
	int a[N][M]={{1,2,3},{4,5,6}};
	int b[N][M]={{1,2,3},{4,5,6}};
	
	add(a,b);
	
	int c[N][M]={{10,15,20},{25,30,35}};
	int d[N][M]={{30,20,10},{5,15,20}};
	
	add(c,d);

	
	return(0);
}

void add(int a[N][M], int b[N][M]){
	
	int ans[N][M];
	
	if(a[0][0]==1){
		printf("a+b=\n");
		for(int i=0; i<N; i++){
			for(int j=0; j<M; j++){
				ans[i][j]=a[i][j]+b[i][j];
				printf("%3d", ans[i][j]);
			}
			printf("\n");
		}
		
	}else{
		printf("c+d=\n");
		for(int i=0; i<N; i++){
			for(int j=0; j<M; j++){
				ans[i][j]=a[i][j]+b[i][j];
				printf("%3d", ans[i][j]);
			}
			printf("\n");
		}
	}
}
	