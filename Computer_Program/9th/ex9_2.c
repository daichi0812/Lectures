/*
 *ex9_2.c　15822108 情報テクノロジー 堀田大智
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 128

int get_value(char msg[]);
void get_input(char msg[], char n[]);
int is_int(char n[]);
void print_kuku(int n);

int main() {
    int n;
	
    n = get_value("1から9までの整数値を入力してください： ");
    print_kuku(n);
	
    return 0;
}

int get_value(char msg[]){
	int i;
	int d;
	
	char m[BUFSIZE];
	
	while(1){
		get_input(msg, m);
	
		if(is_int(m)){
			i=atoi(m);
			if(0<i&&i<10){
				d=i;
				break;
			}else{
			}
		}else{
		}
	
	}
	
	return d;
}

void get_input(char msg[], char n[]){
	printf("%s", msg);
	gets(n);
}

void print_kuku(int n){
	int i,j;
	
	for(i=1; i<=n+1; i++){
		for(j=1; j<=n+1; j++){
			if(i==1&&j==1){
				printf("  ");
			}else if(i==1){
				printf("%2d", j-1);
			}else if(j==1){
				printf("%2d", j);
			}else{
				printf("%2d", (j-1)*(i-1));
			}
		}
		printf("\n");
	}
}

int is_int(char n[]){
	int i=1;
	int ans;
	
	if(47<n[0]&&n[0]<58||n[0]=='-'){
		while(1){
			if(47<n[i]&&n[i]<58){
				if(n[i+1]=='\0'){
				ans=1;
				break;
			}
			i++;
			}else if(n[i]=='.'){
				for(int j=1; j<i; j++){
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
		if(n[1]=='\0'){
			ans=1;
		}
	}else{
		ans=0;
	}
	return ans;
}