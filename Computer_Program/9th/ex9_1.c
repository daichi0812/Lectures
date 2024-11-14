/*
 *ex9_1.c 15822108 情報テクノロジー　堀田大智
 */
#include <stdio.h>
#include <ctype.h>   // 数字の判定に利用
#include <string.h>  // 文字列長の取得に利用

#define BUFSIZE 128

void get_input(char msg[], char n[]);
int is_int(char n[]);

int main() {
    char buf[BUFSIZE];
	
    get_input("整数値を入力してください：", buf);
    if (is_int(buf))
        printf("%s は整数値です\n", buf);
    else
        printf("%s は整数値ではありません\n", buf);
	
    return 0;
}

void get_input(char msg[], char n[]){
	printf("%s", msg);
	gets(n);
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