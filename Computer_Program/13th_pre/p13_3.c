/*
 *p13_3.c 15822108 情報テクノロジー 堀田大智
*/
#include <stdio.h>

int main(){
    char buf[1024];
    int n, m;

    printf("文字列を入力してください : ");
    fgets(buf, sizeof(buf), stdin);
    printf("%s\n", buf);

    printf("半角カンマで区切って2つの整数を入力してください : ");
    fgets(buf, sizeof(buf), stdin);
    sscanf(buf, "%d,%d", &n, &m);
    printf("n = %d\n", n);
    printf("m = %d\n", m);

    return 0;
}