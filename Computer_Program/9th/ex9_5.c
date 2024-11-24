/*
 *ex9_5.c 15822108 情報テクノロジー　堀田大智
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 128

void get_input(char msg[], char n[]);
int get_year(void);
int is_int(char n[]);

int main() {
    int year;
	
    year = get_year();
    printf("西暦：%d\n", year);
		
    return 0;
}

int get_year(void){
	char buf[BUFSIZE];
	int y;
	
	while(1){
	get_input("整数値を入力してください：", buf);
	if(is_int(buf)){
		y=atoi(buf);
		return y;
	}else{
	}
	}
}
		
	

void get_input(char msg[], char n[]){
	printf("%s", msg);
	gets(n);
}


int is_int(char n[]){
	int i=0;
	int ans;
	
	while(1){
		if(47<n[i]&&n[i]<58){
			if(n[i+1]=='\0'){
				ans=1;
				break;
			}
			i++;
		}else if(n[i]=='.'){
			for(int j=0; j<i; j++){
				if(47<n[j]&&n[j]<58){
					ans=1;
				}else{
					ans=0;
					break;
				}
			}
			for(int k=i+1; n[k]!='\0'&&k<BUFSIZE; k++){
				if(n[k]=='0'){
					ans=1;
				}else{
					ans=0;
					break;
				}
			}
			break;
		}else{
			ans=0;
			break;
		}
	}
	
	return ans;
}