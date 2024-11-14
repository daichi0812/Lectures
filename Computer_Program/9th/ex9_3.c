/*
 *ex9_3.c 15822108 情報テクノロジー　堀田大智
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BUFSIZE 128

void get_input(char msg[], char n[]);
int is_real(char n[]);

int main() {
    char buf[BUFSIZE];
	
    get_input("非負の実数値を入力してください：", buf);
    if (is_real(buf))
        printf("%s は非負の実数値です\n", buf);
    else
        printf("%s は非負の実数値ではありません\n", buf);
	
    return 0;
}

void get_input(char msg[], char n[]){
	printf("%s", msg);
	gets(n);
}

int is_real(char n[]){
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
				if(47<n[k]&&n[k]<58){
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
	
	if(n[0]=='.'){
		ans=0;
	}
	
	return ans;
}