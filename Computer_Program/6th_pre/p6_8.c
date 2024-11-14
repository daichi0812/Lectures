/*
 *p6_8.c ファイルへの出力(char型配列によるファイル名の指定) 15822108 情報テクノロジー　堀田大智
 */
#include<stdio.h>

int main(){
	FILE *fout;
	char data[]="Aoyama Gakuin";
	char fname[]="result6-8.txt";
	
	if((fout=fopen(fname, "w"))==NULL){
		printf("Cannot open the file : %s\n", fname);
		return 1;
	}
	
	fprintf(fout, "%s/n", data);
	fclose(fout);
	
	return 0;
}