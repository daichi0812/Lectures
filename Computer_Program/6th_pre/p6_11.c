/*
 *p6_11.c 15822108 情報テクノロジー　堀田大智
 */
#include<stdio.h>

int main(){
	FILE *fin;
	char buf[1024], fname[]="p6_11.c";
	
	if((fin=fopen(fname, "r"))==NULL){
		printf("Cannot open the file: %s\n", fname);
		return 1;
	}
	
	while(fgets(buf, 1024, fin)!=NULL){
		printf("%s", buf);
	}
	fclose(fin);
	
	return 0;
}