/*
 * ex4_4.c 15822108 堀田大智
 */
 #include<stdio.h>
 #include<stdlib.h>
 #include<time.h>
 
 double estimate_circle_area(int r, int n);
 
 int main(){
	
	int a=100;
	
	for(int i=0; i<5; i++){
		printf("%d 個の点による円周率の推定値 : %.6lf\n", a, estimate_circle_area(1.0, a));
		a=10*a;
	}
	
	return 0;
 }
 
 double estimate_circle_area(int r, int n){
	 double x, y;
	 int count=0;
	 double ans=0.0;
	 double b=0.0;
	 
	 for(int s=0; s<100; s++){
		 count=0;
		for(int i=0; i<n; i++){
			x=(double)rand()/RAND_MAX*r;	//0以上r以下の乱数x
			y=(double)rand()/RAND_MAX*r;	//0以上r以下の乱数y
		 
			if(x*x+y*y<r*r){
				count++;
			}
		}
		b=b+4.0*(double)count/(double)n;
	 }
	 
	 
	 ans=b/100;
	 
	 return ans;
 }