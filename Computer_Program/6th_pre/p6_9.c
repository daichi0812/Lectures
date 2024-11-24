/*
 *p6_9.c ファイルへの出力(キーボードからのファイル名の指定)
 */
#include<stdio.h>

int main(){
	FILE *fout;
	char data[]="Aoyama Gakuin";
	char fname[100];
	
	printf("ファイル名を入力してください :");
	scanf("%s", fname);
	if((fout=fopen(fname, "w"))==NULL){
		printf("Cannot open the file: %s\n", fname);
		return 1;
	}
	
	fprintf(fout, "%s\n", data);
	fclose(fout);
	
	return 0;
}