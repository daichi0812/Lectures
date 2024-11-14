#include <stdio.h>

#define n 2
#define m 3

int max(int a[n][m]);

int main(){
	
	int a[n][m]={{10,13,29},{12,30,23}};
	
	printf("max %d", max(a));
	
	return(0);
}

int max(int a[n][m]){
	
	int max=0;
	
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(max<a[i][j]){
				max=a[i][j];
			}
		}
	}
	return max;
}
		