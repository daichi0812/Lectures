/*
 *ex10_1.c 15822108 情報テクノロジー 堀田大智
 */
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 64

void print_string(char *s);

int main() {
    char string[BUFSIZE] = "Aoyama Taro";
	
    print_string(string);
	
    return 0;
}

void print_string(char *s){
	int i=0;
	
	for(i=0; *s!='\0'; i++){
		printf("%c", *s);
		s=s+1;
	}
}