/*
 *p12_2.c 15822108 情報テクノロジー 堀田大智
 */
#include<stdio.h>

int main(int argc, char **argv){
	int i;
	
	printf("引数の数: %d\n", argc);
	for(i=0; i<argc; i++){
		printf("%d番目の引数: %s\n", i+1, argv[i]);
	}
	
	return 0;
}