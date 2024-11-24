/*
 *p6_5.c ファイルからの入力(char型配列によるファイル名の指定) 15822108 情報テクノロジー　堀田大智
 */
#include<stdio.h>

int main(){
	FILE *fin;
	char data[100];
	char fname[]="data6-4.txt";
	
	if((fin=fopen(fname, "r"))==NULL){
		printf("Cannot open the file: %s\n", fname);
		return 1;
	}
	
	fscanf(fin, "%s", data);
	fclose(fin);
	
	printf("data: %s\n", data);
	
	return 0;
}