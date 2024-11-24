/*
 *p3_3d.c　for分の利用 15822108 堀田大智
 */
 #include <stdio.h>
 
 int main(){
	 
	 int i, j;
	 
	 printf("(i, j)=\n");
	 
	 for(int j=0; j<5; j++){
		 for(int i=0; i<5; i++){
			 
			 printf("(%2d,%2d) ",j,i);
		 }
		 printf("\n");
	 }
	 
	 return(0);
 }