/*
 * p4_7.c 配列の利用(関数にすべての要素を渡す) 15822108 堀田大智
 */
 
 #include<stdio.h>
 
 int get_max(int data[]);
 int get_min(int data[]);
 
 int main(){
	 
	 int height[5]={165,167,155,178,170};
	 
	 printf("最大の身長 : %d\n", get_max(height));
	 printf("最小の身長 : %d\n", get_min(height));
	 
	 return 0;
 }
 
 int get_max(int data[]){
	 int i,max;
	 
	 for(i=1,max=data[0]; i<5; i++){
		 if(max<data[i]){
			 max=data[i];
		 }
	 }
	 
	 return max;
 }
 
 int get_min(int data[]){
	 int i, min;
	 
	 for(i=1, min=data[0]; i<5; i++){
		 if(min>data[i]){
			 min=data[i];
		 }
	 }
	 
	 return min;
 }