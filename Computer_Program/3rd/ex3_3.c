/*
 * ex3_3 15822108　堀田大智
 */
 #include <stdio.h>
 
 int main(){
	 
	 /*1行目の記述*/
	 
	 for(int i=0; i<11; i++){
		 
		 if(i==0){
			 printf("   ");
			 
		 }else if(i==1){
				 printf("|");
				 
		 }else{
			 printf("%3d",i-1);
		 }
	 }
	 printf("\n");
	 
	 /*2行目の記述*/
	 for(int i=0; i<11; i++){
		 
		 if(i==0){
			 printf("---");
			 
		 }else if(i==1){
			 printf("|");
			 
		 }else{
			 printf("---");
		 }
	 }
	 printf("\n");
	 
	 /*3行目以降の記述*/
	 int j=0;
	 
	 for(int h=0; h<9; h++){
		 for(int i=0; i<11; i++){
			 
			 if(i==0){
				 printf("%3d",(j+1)*(i+1));
				 
			 }else if(i==1){
				printf("|");
				
			 }else{
				 printf("%3d",(j+1)*(i-1));
			 }
		 }
		 j++;
		 printf("\n");
	 }
	 
	 return(0);
 }