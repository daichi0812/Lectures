/*
 *p12_3.c
 */
#include<stdio.h>
#include<stdlib.h>

#define BUFSIZE 256

void print_file(char *fname);

int main(int argc, char **argv){
	int i;
	
	printf("引数の数: %d\n", argc);
	for(i=0; i<argc; i++){
		printf("%d番目の引数: %s\n", i+1, argv[i]);
	}
	
	print_file(argv[1]);
	
	return 0;
}

void print_file(char *fname){
	FILE *fin;
	char buf[BUFSIZE];
	
	if((fin=fopen(fname, "r"))==NULL){
		printf("Can't open the file %s\n", fname);
		exit(1);
	}
	while(fgets(buf, BUFSIZE, fin)!=NULL){
		printf("%s", buf);
	}
}