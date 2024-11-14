/*
 *p8_2.c　配列の表示　15822108　情報テクノロジー　堀田大智
 */
#include<stdio.h>

#define ARRAYSIZE 10

void print_array(int d[], int index, int size);

int main(){
	int data[ARRAYSIZE]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	
	print_array(data, 0, ARRAYSIZE);
	
	return 0;
}

void print_array(int d[], int index, int size){
	if(index<size){
		printf("%d\n", d[index]);
		return print_array(d, index+1, size);
	}
	else{
		return 1;
	}
}