/*
 *p2_8.c 
 *情報テクノロジー学科 堀田大智
 */
 #include <stdio.h>
 
 int main(){
	 
	 int num;
	 
	printf("整数値を入力してください : ");
	
	scanf("%d", &num);
	
	if(num%5==0){
		printf("5の倍数です");
	}else{
		printf("5の倍数ではありません");
	}
	 
	 return(0);
 }
	 