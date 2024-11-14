/*
 *ex8_2.c 情報テクノロジー　15822108 堀田大智
 */
#include<stdio.h>

#define ARRAYSIZE 10

void print_array_reverse(int d[], int n);

int main() {
    int data[ARRAYSIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    print_array_reverse(data, ARRAYSIZE - 1);

    return 0;
}

void print_array_reverse(int d[], int n){
	if(n>=0){
		printf("%d\n", d[n]);
		print_array_reverse(d, n-1);
	}
}