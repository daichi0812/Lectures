/*
 *ex7_4.c 15822108 情報テクノロジー　堀田大智
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 30
#define BUFSIZE 256

typedef struct{
	double close;
	double open;
	double high;
	double low;
}stock_info;

void print_data(stock_info d[], int n);
int read_data(stock_info d[]);

int main(){
	int num;
	stock_info data[MAXNUM];
	
	num=read_data(data);
	print_data(data, num);
	
	return 0;
}

void print_data(stock_info d[], int n){
	int i;
	
	for(i=0; i<n; i++){
		printf("%d日目の株価\n", i+1);
		printf("終値 : %.2f\n", d[i].close);
		printf("始値 : %.2f\n", d[i].open);
		printf("高値 : %.2f\n", d[i].high);
		printf("安値 : %.2f\n", d[i].low);
	}
}

int read_data(stock_info d[]){
	int i=0;
	int count=0;
	FILE *fin;
	char buf[BUFSIZE];
	char fname[BUFSIZE];

	printf("データファイルのファイル名を入力してください: ");
	scanf("%s", &fname);
	
	if((fin=fopen(fname, "r"))==NULL){
		printf("Cannot open the file: %s\n", fname
		);
		exit (1);
	}
	
	while(fscanf(fin, "%lf,%lf,%lf,%lf", &d[i].close, &d[i].open, &d[i].high, &d[i].low)!=EOF){
		count++;
		i++;
	}
	
	fclose(fin);
	
	return count;
}
	
	
	