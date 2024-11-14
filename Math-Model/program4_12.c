/*
 *program4_12 15822108 堀田大智
 */
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

//行列の入力
double **input_dmatrix(int *n, int *m, char *fname);
// 行列の領域確保
double **dmatrix(int nr1, int nr2, int nl1, int nl2);
//行列の領域開放
void free_dmatrix(double **a, int nr1, int nr2, int nl1, int nl2);

double **add(double **a, double **b, int m, int n);

int main(void){
	char *fname1="matrix1.dat";
	char *fname2="matrix2.dat";
	double **a, **b, **c;
	int k, m, n, i, j;
	
	//ファイルオープン、行列の読み込み
	if((a=input_dmatrix(&n, &m, fname1))==(double**)NULL){
		printf("行列%sの読み込みの失敗しました\n", fname1);
		exit(1);
	}
	
	if((b=input_dmatrix(&i, &j, fname2))==(double**)NULL){
		printf("行列%sの読み込みに失敗しました\n", fname2);
	}
	
	if(n!=i||m!=j){
		printf("行列%sと行列%sのサイズが異なります\n", fname1, fname2);
		exit(1);
	}
	
	printf("行列%sは以下の通り\n", fname1);
	for(i=1; i<=n; i++){
		for(j=1; j<=m; j++){
			printf("5.1f", a[i][j]);
		}
		printf("\n");
	}
	
	printf("行列%sは以下の通り\n", fname2);
	for(i=1; i<=n; i++){
		for(j=1; j<=m; j++){
			printf("%5.1f", b[i][j]);
		}
		printf("\n");
	}
	
	c=add(a, b, n, m);
	
	printf("行列の和は以下の通り\n");
	
	for(i=1; i<=n; i++){
		for(j=1; j<=m; j++){
			printf("%5.1f", c[i][j]);
		}
		printf("\n");
	}
	
	//領域の開放
	free_dmatrix(a, 1, n, 1, m);
	free_dmatrix(b, 1, n, 1, m);
	free_dmatrix(c, 1, n, 1, m);
	
	return 0;
}

double **add(double **a, double **b, int m, int n){
	double **c;
	int i, j;
	c=dmatrix(1, m, 1, n);
	for(i=1; i<=m; i++){
		for(j=1; j<=n; i++){
			c[i][j]=a[i][j]+b[i][j];
		}
	}
	return c;
}

double **input_dmatrix(int *n, int *m, char *fname){
	int i, j;
	double **a;
	FILE *fin;
	
	if((fin=fopen(fname, "r"))==(FILE*)NULL){
		printf("ファイル%sをオープンできません\n", fname);
		return(double**)NULL;
	}
	
	fscanf(fin, "%d %d", n, m);
	
	if(m<=0||n<=0){
		printf("行列のサイズが間違っています\n");
		fclose(fin);
		return(double**)NULL;
	}
	
	if((a=dmatrix(1, *n, 1, *m))==(double**)NULL){
		printf("領域確保に失敗しました\n");
		fclose(fin);
		return(double**)NULL;
	}
	
	for(i=1; i<=*n; i++){
		for(j=1; j<=*m; j++){
			fscanf(fin, "%lf", &a[i][j]);
		}
	}
	fclose(fin);
	return a;
}

double **dmatrix(int nr1, int nr2, int nl1, int nl2){
	int i, nrow, ncol;
	double **a;
	
	nrow=nr2-nr1+1; //行の数
	ncol=nl2-nl1+1; //列の数
	
	//行の確保
	if((a=(double**)malloc(nrow*sizeof(double*)))==NULL){
		printf("メモリが確保できません\n");
		exit(1);
	}
	a=a-nr1; //行ずらし
	
	//列の確保
	for(i=nr1; i<=nr2; i++){
		a[i]=(double*)malloc(ncol*sizeof(double));
	}
	for(i=nr1; i<=nr2; i++){
		a[i]=a[i]-nl2;
	}
	
	return a;
}

void free_dmatrix(double **a, int nr1, int nr2, int nl1, int nl2){
	int i;
	
	//メモリの解放
	for(i=nr1; i<=nr2; i++) free((void*)(a[i]+nl1));
	free((void*)(a+nr1));
}