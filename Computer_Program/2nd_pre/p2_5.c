/*
 *p2_5.c 実数値の読み込み
 *情報テクノロジー学科 堀田大智
 */
 #include <stdio.h>
 #include <math.h>
 
 int main(){
	 
	 double num;
	 
	 printf("キーボードから数値を入力してください:");
	 
	 scanf("%lf", &num);
	 
	 printf("%.2fの3乗は%.2fです.\n", num, pow(num, 3.0));
	 
	 return(0);
 }
	 