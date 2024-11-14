/*
 *p11_7.c 15822108 情報テクノロジジー 堀田大智
 */
#include<stdio.h>
#include<stdlib.h>

int *get_array(int n);
void print_array(int *p, int n);
void set_array(int *p, int *q, int n);

int main(){
	int *d, i;
	int sample[10]={1,2,3,4,5};
	
	d=get_array(10);
	print_array(d, 10);
	set_array(d, sample, 10);
	print_array(d, 10);
	
	return 0;
}

int *get_array(int n){
	return (int *)calloc(n, sizeof(int));
}

void print_array(int *p, int n){
	int i;
	
	for(i=0; i<n; i++){
		printf("%3d: %d\n", i, p[i]);
	}
	printf("\n");
}

void set_array(int *p, int *q, int n){
	int i;
	
	for(i=0; i<n; i++, p++, q++){
		*p=*q;
	}
}