/*
 * program4_10 15822108 堀田大智
 */
 
#include<stdio.h>
#include<stdlib.h>

#define M 2	/*行の要素数*/
#define N 3	/*列の要素数*/

/*行列の領域確保*/
double **dmatrix(int nr1, int nr2, int nl11, int nl2);
/*行列の領域解放*/
void free_dmatrix(double **a, int nr1, int nr2, int nl1, int nl2);
/*add関数*/
void add(double **ans, double **h1, double **h2, int nr1, int nr2, int nl1, int nl2);

int main(void){
	double **a, **b, **c, **d, **ans;
	int i, j;
	
	/*メモリの確保*/
	a=dmatrix(1, M, 1, N); 
	b=dmatrix(1, M, 1, N);
	c=dmatrix(1, M, 1, N);
	d=dmatrix(1, M, 1, N);
	
	/*要素の代入*/
	a[1][1]=1; a[1][2]=2; a[1][3]=3; a[2][1]=4; a[2][2]=5; a[2][3]=6;
	b[1][1]=1; b[1][2]=2; b[1][3]=3; b[2][1]=4; b[2][2]=5; b[2][3]=6;
	c[1][1]=10; c[1][2]=15; c[1][3]=20; c[2][1]=25; c[2][2]=30; c[2][3]=35;
	d[1][1]=30; d[1][2]=20; d[1][3]=10; d[2][1]=5; d[2][2]=15; d[2][3]=20;
	
	printf("a+b=\n");
	add(ans, a, b, 1, M, 1, N);
	for(i=1; i<=M; i++){
		for(j=1; j<=N; j++){
			printf("%3.0f", (double)ans[i][j]);
		}
		printf("\n");
	}
	
	printf("c+d=\n");
	add(ans, c, d, 1, M, 1, N);
	for(i=1; i<=M; i++){
		for(j=1; j=N; j++){
			printf("%3.0f", (double)ans[i][j]);
		}
		printf("\n");
	}
	
	/*メモリの解放*/
	free_dmatrix(a, 1, M, 1, N);
	free_dmatrix(b, 1, M, 1, N);
	free_dmatrix(c, 1, M, 1, N);
	free_dmatrix(d, 1, M, 1, N);
	return 0;
}

double **dmatrix(int nr1, int nr2, int nl1, int nl2){
	int i, nrow, ncol;
	double **a;
	
	nrow=nr2-nr1+1; /*行の数*/
	ncol=nl2-nl1+1;	/*列の数*/
	
	/*行の確保*/
	if((a=malloc(nrow*sizeof(double *)))==NULL){
		printf("メモリが確保できません(行列a)\n");
		exit(1);
	}
	a=a-nr1; /*行をずらす*/
	
	/*列の確保*/
	for(i=nr1; i<=nr2; i++){
		a[i]=malloc(ncol*sizeof(double));
	}
	for(i=nr1; i<=nr2; i++){
		a[i]=a[i]-nl1;	/*列をずらす*/
	}
	return a;
}

void free_dmatrix(double **a, int nr1, int nr2, int nl1, int nl2){
	int i;
	
	/*メモリの解放*/
	for(i=nr1; i<=nr2; i++){
		free((void *)(a[i]+nl1));
	}
	free((void *)(a+nr1));
}

void add(double **ans, double **h1, double **h2, int hr1, int hr2, int hl1, int hl2){
	int i, j;
	for(i=hr1; i<=hr2; i++){
		for(j=hl1; j<=hl2; j++){
			ans[i][j]=h1[i][j]+h2[i][j];
		}
	}
}