/*
 *ex5_2.c 15822108 情報テクノロジー　堀田大智
 */
#include<stdio.h>
#include<string.h>

#define MAXLENGTH 81
#define HALFLENGTH 40

int main(){
	int i;
	char ss[MAXLENGTH];
	char tt[HALFLENGTH];
	char uu[MAXLENGTH];
	
	printf("ローマ字で姓を入力>");
	gets(ss);
	printf("ローマ字で名を入力>");
	gets(tt);
	
	
	for(int i=0; i<MAXLENGTH; i++){
		if(ss[i]=='\0'){
			ss[i]=' ';
			ss[i+1]='\0';
			break;
		}
	}
	for(int i=0; i<strlen(ss); i++){
		uu[i]=ss[i];
	}
	for(int i=strlen(ss); i<MAXLENGTH; i++){
		uu[i]=tt[i-strlen(ss)];
	}
	printf("あなたの名前は %s ですね", uu);
	
	return 0;
}