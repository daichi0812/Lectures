/*
 * p4_4.c 配列の利用(宣言と同時に初期化+初期値のない要素あり) 15822108 堀田大智
 */
 
 #include<stdio.h>
 
 int main(){
	 int i, height[5]={165,167,155};
	 
	 for(i=0;i<5;i++){
		 printf("%d番目の身長 : %dcm\n", i+1,height[i]);
	 }
	 
	 return 0;
 }