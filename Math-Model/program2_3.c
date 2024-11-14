#include <stdio.h>

int main(void){
	
	int a;
	
	for (a=1; a<=20; a++){
		
		if((a%5==0)&&(a%3==0)){
			printf("%dは3の倍数で5の倍数\n", a);
		}else if(a%5==0){
			printf("%dは5の倍数\n",a);
		}else if(a%3==0){
			printf("%dは3の倍数\n", a);
		}
	}
}