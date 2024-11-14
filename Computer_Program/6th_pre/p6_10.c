/*
 *p6_10.c 15822108 情報テクノロジー 堀田大智
 */
#include<stdio.h>

int main(){
	FILE *fout;
	char kuku[9][9];
	char fname[]="result6-10.txt";
	int i, j;
	
	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
			kuku[i][j]=(i+1)*(j+1);
		}
	}
	
	if((fout=fopen(fname, "w"))==NULL){
		printf("Cannot open the file: %s\n", fname);
		return 1;
	}
	
	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
			fprintf(fout, "%3d", kuku[i][j]);
		}
		fprintf(fout, "\n");
	}
	fclose(fout);
	
	return 0;
}