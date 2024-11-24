/*
 *ex10_2.c 15822108 情報テクノロジー 堀田大智
 */
#include <stdio.h>

void update_value(int *ptr);

int main() {
    int a = 10, b = 20, *p;
    double  *q;

    printf("aの値：%d\n", a);
    printf("aのアドレス：%p\n", &a);
    printf("bの値：%d\n", b);
    printf("bのアドレス：%p\n", &b);
    printf("pの値：%p\n", p);
    printf("pのアドレス：%p\n", &p);
    printf("pのデータサイズ：%d bytes = %2d bits\n", (int)sizeof(p), (int)sizeof(p) * 8);
    printf("qのデータサイズ：%d bytes = %2d bits\n", (int)sizeof(q), (int)sizeof(q) * 8);
    printf("\n");
	
    update_value(&a);
    printf("aの値：%d\n", a);
    printf("aのアドレス：%p\n", &a);
    printf("\n");

    update_value(&b);
    printf("bの値：%d\n", b);
    printf("bのアドレス：%p\n", &b);
    printf("\n");

    return 0;
}

void update_value(int *ptr){
	
	printf("pの値 : %p\n", ptr);
	printf("pが指すアドレスの内容 : %d\n", *ptr);
	printf("\n");
	
	*ptr=*ptr+100;
	
	printf("pの値 : %p\n", ptr);
	printf("pが指すアドレスの内容 : %d\n", *ptr);
}