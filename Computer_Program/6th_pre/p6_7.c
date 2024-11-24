/*
 *p6_7.c ファイルへの出力
 */
#include<stdio.h>

int main(){
	FILE *fout;
	char data[]="Aoyama Gakuin";
	
	if((fout=fopen("result6-7.txt", "w"))==NULL){
		printf("Cannot open the file: result6-7.txt\n");
		return 1;
	}
	
	fprintf(fout, "%s\n", data);
	fclose(fout);
	
	return 0;
}