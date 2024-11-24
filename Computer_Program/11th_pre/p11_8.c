/*
 *p11_8.c 15822108 情報テクノロジー 堀田大智
 */
#include<stdio.h>
#include<stdlib.h>

int **get_2d_array(int n, int m);
void print_2d_array(int **p, int n, int m);
void set_2d_array(int **p, int n, int m);

int main(){
	int **d;
	
	d=get_2d_array(5, 5);
	print_2d_array(d, 5, 5);
	set_2d_array(d, 5, 5);
	print_2d_array(d, 5, 5);
	
	return 0;
}

int **get_2d_array(int n, int m){
	int **p, i;
	
	p=(int **)calloc(n, sizeof(int *));
	for(i=0; i<n; i++){
		p[i]=(int *)calloc(m, sizeof(int));
	}return p;
}

void print_2d_array(int **p, int n, int m){
	int i, j;
	
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			printf("(%2d, %2d)=%2d\n", i, j, p[i][j]);
		}
	}
	printf("\n");
}

void set_2d_array(int **p, int n, int m){
	int i, j, c =1;
	
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			p[i][j]=c++;
		}
	}
}