/*
 * p4_10.c 多次元配列の初期化+マクロ定数+2次元配列の関数引数 15822108 堀田大智
 */
 
 #include<stdio.h>
 
 #define ROWS 3
 #define COLS 4
 
 void print_matrix(int data[][COLS]); //2次元配列を因数で渡す場合2次元目の要素数は明示する
 
 int main(){
	 int i, j;
	 int data1[ROWS][COLS]={{1,2,3,4},{11,12,13,14},{21,22,23,24}};
	 int data2[ROWS][COLS]={{1,2,3,4}};
	 int data3[ROWS][COLS]={};
	 
	 printf("data1\n"); print_matrix(data1);
	 printf("data2\n"); print_matrix(data2);
	 printf("data3\n"); print_matrix(data3);
	 
	 return 0;
 }
 
 void print_matrix(int data[][COLS]){
	 int i, j;
	 
	 for(i=0; i<ROWS; i++){
		 for(j=0; j<COLS; j++)
			 printf("%3d",data[i][j]);
		 printf("\n");
	 }
 }