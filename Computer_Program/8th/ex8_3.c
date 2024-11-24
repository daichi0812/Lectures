/*
 *ex8_3.c 15822108 情報テクノロジー　堀田大智
 */
#include<stdio.h>

#define ARRAYSIZE 10

void print_array(int d[], int n);

int main() {
    int data[ARRAYSIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    print_array(data, ARRAYSIZE - 1);

    return 0;
}

void print_array(int d[], int n){
	if(n>=0&&n<ARRAYSIZE){
		print_array(d, n-1);
		printf("%d\n", d[n]);
	}
}