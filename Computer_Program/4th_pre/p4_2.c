/*
 *p4_2.c 配列の利用(宣言と同時に初期化) 15822108 堀田大智
 */

#include<stdio.h>

int main(){
	int i, height[5]={165,167,155,170,178};
	
	for(i=0;i<5;i++){
		printf("%d番目の身長 : %dcm\n",i+1,height[i]);
	}
	
	return 0;
}