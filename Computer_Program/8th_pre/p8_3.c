/*
 *p8_3.c ハノイの塔の解法　15822108　情報テクノロジー　堀田大智
 */
#include<stdio.h>

void hanoi_solver(int n, char from, char to, char tmp);

int main(){
	int n;
	
	printf("Aに置く円盤の枚数を入力してください : ");
	scanf("%d", &n);
	hanoi_solver(n, 'A', 'C', 'B');
	
	return 0;
}

void hanoi_solver(int n, char from, char to, char tmp){
	if(n==1){
		return printf("円盤1を%cから%cに移動\n", from, to);
	}
	else{
		hanoi_solver(n-1, from, tmp, to);
		printf("円盤%dを%cから%cに移動\n", n, from, to);
		hanoi_solver(n-1, tmp, to, from);
	}
}
		