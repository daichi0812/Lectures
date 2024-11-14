/*
 *p13_4.c 15822108 情報テクノロジー 堀田大智
 */
#include <stdio.h>
#include <string.h>

void remove_nl(char *s);

int main(){
    char buf[1024];
    int n, m;

    printf("文字列を入力してください : ");
    fgets(buf, sizeof(buf), stdin);
    remove_nl(buf);
    printf("%s\n", buf);

    printf("半角カンマで区切って2つの整数を入力してください : ");
    fgets(buf, sizeof(buf), stdin);
    remove_nl(buf);
    sscanf(buf, "%d,%d", &n, &m);
    printf("n = %d\n", n);
    printf("m = %d\n", m);

    return 0;
}

void remove_nl(char *s){
    int i;

    for(i=0; i<1024||s[i]=='\0'; i++){
        if(s[i]==10){
            s[i]='\0';
            break;
        }
    }
}