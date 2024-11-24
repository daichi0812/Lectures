/*
 *p5_4.c データ型の変換　15822108 堀田大智
 */
 #include<stdio.h>
 
 int main(){
	 int ch, i, j;
	 double ans;
	 
	 ch='A';
	 printf("変換仕様%%dでの表示 : %d\n", ch);
	 printf("変換仕様%%cでの表示 : %c\n", (char)ch);
	 i=2;
	 j=3;
	 ans=(i+j)/2;
	 printf("%dと%dの平均値%f\n", i, j, ans);
	 ans=((double)i+(double)j)/2;
	 printf("%dと%dの平均値%f\n", i, j, ans);
	 ans=(i+j)/2.0;
	 printf("%dと%dの平均値%f\n", i, j, ans);
	 
	 return 0;
 }