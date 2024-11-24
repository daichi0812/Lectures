/*
 *ex11_3.c 15822108 情報テクノロジー 堀田大智
 */
#include <stdio.h>
#include <stdlib.h>

int **read_matrix(char *fname, int *s);

int main(){
	int **mat, size, i, j;
	
	mat =read_matrix("data_ex11_3.txt", &size);
	
	//対称行列の表示
	printf("  ");
	for(i=0; i<size; i++){
		printf("%2d", i+1);
	}
	printf("\n");
	for(i=0; i<size; i++){
		printf("%2d", i+1);
		for(j=0; j<size; j++){
			printf("%2d", mat[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}

int **read_matrix(char *fname, int *s){
	int i, n;
	FILE *fin;
	int **matrix;
	int **reader;
	
	//ファイルのオープン
	if((fin=fopen(fname, "r"))==NULL){
		printf("Cannot open the file: %s\n" ,fname);
		exit (1);
	}
	
	//行数、列数の入力
	fscanf(fin, "%d", s);
	
	//行数、列数の代入
	n=*s;
	
	//領域確保
	if((matrix=(int **)calloc(n, sizeof(int *)))==NULL){
		printf("メモリの確保に失敗しました\n");
		exit(1);
	}
	for(i=0; i<n; i++){
		if((matrix[i]=(int *)calloc(n, sizeof(int)))==NULL){
			printf("メモリの確保に失敗しました\n");
			exit(1);
		}
	}
	
	if((reader=(int **)calloc(n*n/2, sizeof(int *)))==NULL){
		printf("メモリの確保に失敗しました\n");
		exit(1);
	}
	for(i=0; i<n*n/2; i++){
		if((reader[i]=(int *)calloc(3, sizeof(int)))==NULL){
			printf("メモリの確保に失敗しました\n");
			exit(1);
		}
	}
	
	//行列の要素の読み取り
	for(i=0; i<n*n/2; i++){
		fscanf(fin, "%d %d %d", &reader[i][0], &reader[i][1], &reader[i][2]); 
		if(reader[i][1]==0){
			reader[i][1]='\0';
			break;
		}
	}
	
	//各要素をmatに代入
	for(i=0; reader[i][1]!='\0'; i++){
		matrix[reader[i][0]][reader[i][1]]=reader[i][2];
		matrix[reader[i][1]][reader[i][0]]=reader[i][2];
	}
	
	return matrix;
}
	