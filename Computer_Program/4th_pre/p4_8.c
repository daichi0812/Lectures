/*
 * p4_8.c 配列の利用(二次元配列) 15822108 堀田大智
 */
 
 #include<stdio.h>
 
 int main(){
	 int i, j, kuku[9][9];
	 
	 for(i=0; i<9; i++){
		 for(j=0; j<9; j++){
			 kuku[i][j]=(i+1)*(j+1);
		 }
	 }
	 
	 for(i=0; i<9; i++){
		 for(j=0; j<9; j++)
			 printf("%3d",kuku[i][j]);
		 printf("\n");
	 }
	 
	 return 0;
 }