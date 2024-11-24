/*
 * p5_5.c 15822108 堀田大智
 */
 #include<stdio.h>
 
 int main(){
	int i, j, count=32;
	
	for(i=0; i<12; i++){
		for(j=0; j<8; j++){
			if(count==127){
				return 0;
			}else{
				printf("%3c%3d", count, count);
				count+=1;
			}
		}
		printf("\n");
	}
	
	return 0;
 }