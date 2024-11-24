/*
 *p6_3.c 15822108 堀田大智
 */
#include<stdio.h>

int main(){
	FILE *fin;
	double data=0.0;
	
	if((fin=fopen("data6-3.txt", "r"))==NULL){
		printf("Cannot open the file: data6-3.txt\n");
		return 1;
	}
	
	fscanf(fin, "%lf",  &data);
	fclose(fin);
	
	printf("data: %f\n", data);
	
	return 0;
}