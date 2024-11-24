/*
 *p6_4.c ファイルからの入力(文字列) 15822108 情報テクノロジー　堀田大智
 */
#include<stdio.h>

int main(){
	FILE *fin;
	char data[100];
	
	if((fin=fopen("data6-4.txt", "r"))==NULL){
		printf("Cannot open the file: data6-4.txt\n");
		return 1;
	}
	
	fscanf(fin, "%s", data);
	fclose(fin);
	
	printf("data: %s\n", data);
	
	return 0;
}