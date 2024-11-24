/*
 * ex4_2.c 15822108 堀田大智
 */
 #include<stdio.h>
 
 #define DIM 2
 
 void print_sqmat(int v[][DIM]);
 void sqmat_multi(int m1[][DIM], int m2[][DIM], int ans[][DIM]);
 
 int main(){
	 int m1[DIM][DIM]={{2,5},{1,3}};
	 int m2[DIM][DIM]={{3,-5},{-1,2}};
	 int e[DIM][DIM]={{1,0},{0,1}};
	 int ans[DIM][DIM]={};
	 
	 print_sqmat(m1);
	 print_sqmat(m2);
	 sqmat_multi(m1, e, ans);
	 print_sqmat(ans);
	 sqmat_multi(m2, e, ans);
	 print_sqmat(ans);
	 sqmat_multi(m1, m2, ans);
	 print_sqmat(ans);
	 
	 return 0;
 }
 
 void print_sqmat(int v[][DIM]){
	 
	 printf("%dx%d行列\n", DIM, DIM);
	 for(int i=0; i<DIM; i++){
		 for(int j=0; j<DIM; j++){
			 printf("%3d", v[i][j]);
		 }
		 printf("\n");
	 }
 }
 
 void sqmat_multi(int m1[][DIM], int m2[][DIM], int ans[][DIM]){
	 
	 int d[DIM][DIM]={};
	 
	 for(int i=0; i<DIM; i++){
		 for(int j=0; j<DIM; j++){
			 for(int k=0; k<DIM; k++){
				 d[i][j]=d[i][j]+m1[i][k]*m2[k][j];
			 }
			 ans[i][j]=d[i][j];
		 }
	 }
 }