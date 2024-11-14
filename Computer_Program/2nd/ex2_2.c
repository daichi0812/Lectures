/*
 *15822108 堀田大智
 */
 #include <stdio.h>
 
 int is_multiple(int a, int b);
 
 int main(){
	 
	 int result;
	 
	 int num1, num2;
	 
	 printf("2つの整数値カンマで区切って入力してください : ");
	 
	 scanf("%d,%d", &num1, &num2);
	 
	 result = is_multiple(num1, num2);
	 
	 if(result == 1){
		 
		 printf("%dは%dの倍数です", num1, num2);
	 
	 } else{
		 printf("%dは%dの倍数ではありません", num1, num2);
	 }
	 
	 return(0);
 }


 int is_multiple(int a, int b){
	 
	 int ans, c, d;
	 
	 c=a/b;
	
	 d=c*b; //aをbで割った時の商とbを掛けた積がaと同値であればaはbの倍数である。ということになる。
	 
	 if(a == d){
		 ans = 1;
	 }else{
		 ans = 0;
	 }
	 
	 return ans;
 }
		 