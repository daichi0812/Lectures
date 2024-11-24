/*
*p13_1.c 15822108 情報テクノロジー 堀田大智
*/
#include <stdio.h>

int main(){
    int i;
    char buf[1024];
    char *s="Aoyama";

    setbuf(stdout, buf);
    printf("OK\n");
    fflush(stdout);

    for(i=0; i<10; i++){
        s[i]=i;
    }

    return 0;
}