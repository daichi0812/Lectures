/*
 *ex8_4.c 15822108 情報テクノロジー　堀田大智
 */
#include<stdio.h>

int gcd(int c, int y);

int main(){
	int x, y;
	int ans;
	
	printf("2つの自然数をカンマで区切って入力してください : ");
	scanf("%d,%d", &x, &y);
	
	ans=gcd(x, y);
	printf(" %d と %d の最大公約数は %d です", x, y, ans);
	
	return 0;
}

int gcd(int c, int y){
	printf("gcd(%d, %d)\n", c, y);
	if(y==0){
		return c;
	}else{
		return gcd(y, c%y);
	}
}
	