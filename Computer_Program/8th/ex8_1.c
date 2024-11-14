/*
 *ex8_1.c 15822108 情報テクノロジー　堀田大智
 */
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#define BUFSIZE 256

int factorial(int n); //再帰関数として実装
int get_value(void);
void get_input(char msg[], char n[]);
int is_int(char n[]);

int main() {
    int n;

    n = get_value();
    printf("%d の階乗は %d です\n", n, factorial(n));
    return 0;
}

int get_value(void){
    char input[BUFSIZE];
    int valid = 0;
    int value;

    while(!valid){
        get_input("階乗を求めたい整数値を入力してください：", input);
        valid = is_int(input);
        if(!valid){
            printf("%s は非負の整数値ではありません\n", input);
        }
    }
    value = atoi(input);
    return value;
}

void get_input(char msg[], char n[]){
    printf("%s", msg);
    fgets(n, BUFSIZE, stdin);
    if(n[strlen(n) - 1] == '\n'){
        n[strlen(n) - 1] = '\0';
    }
}

int is_int(char n[]){
    int i;
    for(i = 0; i < strlen(n); i++){
        if(!isdigit(n[i])){
            return 0;
        }
    }
    return 1;
}

int factorial(int n){
	if(n>1){
		return n*factorial(n-1);
	}else{
		return 1;
	}
}