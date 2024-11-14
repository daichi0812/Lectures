/*
 *p6_1.c 15822108 情報テクノロジー 堀田大智
 */
#include<stdio.h>

int main(){
	FILE *fin;
	int data=0;
	
	if((fin=fopen("data6-1.txt","r"))==NULL){
		printf("Cannnot open the file: data6-1.txt\n");
		return 1;
	}
	
	fscanf(fin, "%d", &data);
	fclose(fin);
	
	printf("data: %d\n", data);
	
	return 0;
}