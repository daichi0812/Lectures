/*
 * ex4_1.c 15822108 堀田大智
 */
 #include<stdio.h>
 
 #define DIM 5
 
 void print_vec(int v[]);
 int dot(int v[], int w[]);
 
 int main(){
	 int v[]={1, 2, 3, 4, 5};
	 int w[]={6, 7, 8, 9, 10};
	 
	 print_vec(v);
	 print_vec(w);
	 printf("内積 : %d\n", dot(v, w));
	 
	 return 0;
 }
 
 void print_vec(int v[]){
	 
	 int i;
	 
	 printf("(");
	 
	 for(i=0; i<DIM; i++){
		 if(i==DIM-1){
			 printf("%d)\n", v[i]);
		 }
		 else {
			 printf("%d, ", v[i]);
		 }
	 }
 }
 
 int dot(int v[], int w[]){
	 
	 int i, ans=0;
	 
	 int d[DIM];
	 
	 for(i=0; i<DIM; i++){
		 
		 d[i]=v[i]*w[i];
		 
		 ans=ans+d[i];
	 }
	 
	 return ans;
 }