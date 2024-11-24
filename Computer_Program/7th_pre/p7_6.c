/*
 *p7_6.c 構造体の利用(ファイルからの読み込み) 15822108 情報テクノロジー　堀田大智
 */
#include<stdio.h>
#include<stdlib.h>	//関数exit()利用のため

struct stock_info{
	double close;
	double open;
	double high;
	double low;
};

void print_data(struct stock_info d);
struct stock_info read_data(char fname[]);

int main(){
	struct stock_info data;
	char fname[64]="data7-6.csv";
	
	data=read_data(fname);
	print_data(data);
	
	return 0;
}

void print_data(struct stock_info d){
	printf("終値 : %.2f\n", d.close);
	printf("始値 : %.2f\n", d.open);
	printf("高値 : %.2f\n", d.high);
	printf("安値 : %.2f\n", d.low);
}

struct stock_info read_data(char fname[]){
	FILE *fin;
	struct stock_info data;
	
	if((fin=fopen(fname, "r"))==NULL){
		printf("Cannot opnen the file: %s\n", fname);
		exit (1);
	}
	
	fscanf(fin, "%lf,%lf,%lf,%lf", &data.close, &data.open, &data.high, &data.low);
	
	fclose(fin);
	
	return data;
}