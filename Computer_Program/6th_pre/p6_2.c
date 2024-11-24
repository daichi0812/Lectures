/*
 *p6_2.c 15822108 情報テクノロジー 堀田大智
 */
#include<stdio.h>

int main(){
	FILE *fin;
	double data=0.0;
	
	if((fin=fopen("data6-2.txt","r"))==NULL){
		printf("Cannot open the file: data6-2.txt\n");
		return 1;
	}
	
	fscanf(fin, "%lf", &data);
	fclose(fin);
	
	printf("data: %f\n", data);
	
	return 0;
}