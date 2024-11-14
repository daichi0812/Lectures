/*
 *p7_5.c 構造体の定義 15822108 情報テクノロジー　堀田大智
 */
#include<stdio.h>

struct stock_info{
	double close;
	double open;
	double high;
	double low;
};

void print_data(struct stock_info d);

int main(){
	struct stock_info data={21509.03, 21500.89, 21682.94, 21471.12};
	
	print_data(data);
	
	return 0;
}

void print_data(struct stock_info d){
	printf("終値 : %.2f\n", d.close);
	printf("始値 : %.2f\n", d.open);
	printf("高値 : %.2f\n", d.high);
	printf("安値 : %.2f\n", d.low);
}
