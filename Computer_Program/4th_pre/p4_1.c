/*
 * p4_1.c 配列の利用(宣言、代入、参照) 15822108 堀田大智
 */
 
 #include <stdio.h>
 
 int main(){
	 int i, height[5];
	 
	 height[0]=165;
	 height[1]=167;
	 height[2]=155;
	 height[3]=170;
	 height[4]=178;
	 
	 for(i=0;i<5;i++){
		 printf("%d番目の身長 : %dcm\n",i+1,height[i]);
	 }
	 
	 return 0;
 }