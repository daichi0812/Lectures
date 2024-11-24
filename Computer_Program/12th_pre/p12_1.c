/*
 *p12_1.c 15822108 情報テクノロジー 堀田大智
 */
#include<stdio.h>
#include<stdlib.h>

int **get_2d_array(int n, int m);
void print_2d_array(int **p, int n, int m);
void set_2d_array(int **p, int n, int m);

int main(){
	int **d;
	int n, m;
	
	n=m=5;
	d=get_2d_array(n, m);
	set_2d_array(d, n, m);
	print_2d_array(d, n, m);
	
	return 0;
}

void print_2d_array(int **p, int n, int m){
	int i, j;
	
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			printf("(%2d, %2d)=%2d\n", i, j, p[i][j]);
		}
	}
}

int **get_2d_array(int n, int m){
	int **p, i;
	
	if((p=(int **)calloc(n, sizeof(int *)))==NULL){
		printf("Memory allocation error!\n");
		exit(1);
	}
	for(i=0; i<n; i++){
		if((p[i]=(int *)calloc(m, sizeof(int)))==NULL){
			printf("Memory allocation erro!\n");
			exit(1);
		}
	}
	return p;
}

void set_2d_array(int **p, int n, int m){
	int i, j, c =0;
	
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			p[i][j]=c++;
		}
	}
}