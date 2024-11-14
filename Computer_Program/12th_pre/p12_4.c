/*
 *p12_4.c 15822108 情報テクノロジー 堀田大智
 */
#include<stdio.h>
#include<stdlib.h>

#define BUFSIZE 256

void print_file(char *fname);
void check_argnum(int min, int max, int arg_num, char *cmd);
void print_usage(char *cmd);

int main(int argc, char **argv){
	
	check_argnum(2, 2, argc, argv[0]);
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

void print_usage(char *cmd){
	printf("Usage\n");
	printf("%s 'file_name'\n", cmd);
}

void check_argnum(int min, int max, int arg_num, char *cmd){
	if(!(min<=arg_num&&arg_num<=max)){
		printf("Too %s arguments!\n", (arg_num < min)? "few" : "many");
		print_usage(cmd);
		exit(1);
	}
}