/*
 * p4_15.c 15822108 堀田大智
 */
 
 #include<stdio.h>
 #include<stdlib.h>
 #include<time.h>
 
 int main(){
	 int i, n, c;
	 
	 srand((unsigned)time(NULL));
	 printf("サイコロを振る回数を入力してください : ");
	 scanf("%d", &n);
	 for(i=0, c=0; i<n; i++){
		 if((rand()%6+1)==1){			 //rand()%6+1で1~6の整数を生成
			 c++;
		 }
	 }
		 printf("1の出る確率 : %.4f\n", (double)c/(double)n);
		 
		 return 0;
 }