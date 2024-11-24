/*
 *p6_6.c ファイルからの入力(キーボードからのファイル名指定)
 */
#include<stdio.h>

int main(){
	FILE *fin;
	char data[100];
	char fname[100];
	
	printf("ファイル名を入力してください: ");
	scanf("%s", fname);
	if((fin=fopen(fname, "r"))==NULL){
		printf("Cannot open the file: %s\n", fname);
		return 1;
	}
	
	fscanf(fin, "%s", data);
	fclose(fin);
	
	printf("data: %s\n", data);
	
	return 0;
}