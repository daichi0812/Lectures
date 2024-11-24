/*
 * p4_16.c 15822108 堀田大智
 */
 #include<stdio.h>
 #include<stdlib.h>
 #include<time.h>
 
 int main(){
	 int i, n, count;
	 double x, y, r;
	 
	 printf("円の半径の入力してください : ");
	 scanf("%lf", &r);
	 printf("生成する点の数を入力してください : ");
	 scanf("%d", &n);
	 
	 count=0;
	 
	 for(i=0; i<n; i++){
		 
		 x=(double)rand()/RAND_MAX*r;	 //0以上r以下の乱数x
		 y=(double)rand()/RAND_MAX*r;	 	//0以上r以下の乱数y
		 
		 if(x*x+y*y<r*r){
			 count++;
		 }
	 }
		 printf("円の面積の理論値(円周率3.14の場合） : %.3lf\n", 3.14*r*r);
		 printf("%d 回のシミュレーション結果 : %.3lf\n", n, r*r*4*(double)count/(double)n);
	 
	 return 0;
 }