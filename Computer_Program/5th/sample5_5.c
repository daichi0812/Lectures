/*
 *sample5_5.c 15822108 情報テクノロジー　堀田大智
 */
#include<stdio.h>
#include<stdlib.h>

#define BUFSIZE 128

void print_msg(char n[]);

int main(){
	char buf[BUFSIZE];
	int n;
	
	print_msg("整数値を入力してください : ");
	gets(buf);
	n=atoi(buf);
	printf("入力値 : %d\n", n);
	
	return 0;
}

void print_msg(char n[]){
	printf("%s", n);
}