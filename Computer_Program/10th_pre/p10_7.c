/*
 *p10_7.c 15822108 情報テクノロジー　堀田大智
 */
#include<stdio.h>
#include<string.h>

void change_name(char *s);

int main(){
	char name[20]="Aoyama";
	
	printf("name の内容 (int main) : %s\n", name);
	printf("name のアドレス　(in main) : %p\n\n", name);
	printf("name のサイズ (in main) : %d\n\n", (int)sizeof(name));
	
	change_name(name);
	
	printf("name の内容 (in main) : %s/n", name);
	printf("name のアドレス (in main) : %p\n", name);
	printf("name のサイズ (in main); %d\n", (int)sizeof(name));
	
	return 0;
}

void change_name(char *s){
	printf("s の内容　(change_name) : %s\n", s);
	printf("s のアドレス (change_name) :%p\n", s);
	printf("s のサイズ (change_name) : %d\n", (int)sizeof(s));
	
	strcat(s, " Taro");
	
	printf("s の内容 (change_name) : s\n", s);
	printf("s のアドレス　(change_name) : %p\n", s);
	printf("s のサイズ (change_name) : %d\n\n", (int)sizeof(s));
}