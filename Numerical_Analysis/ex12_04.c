/*
 *ex12_04.c 15822108 情報テクノロジー 堀田大智
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 関数の定義 */
double func(double x, double y);
/* ホイン法 */
void heun(double x, double y, double a, double b, int n, 
                              double (*f)(double, double) );
//真の解
double true_f(double x);

int main(void)
{
  int n;

  printf("分割数を入力してください--->");
  scanf("%d",&n);

  heun( 0.0, 1.0, 0.0, 1.0, n, func );

  return 0;
}

/* ホイン法 */
void heun(double x, double y, double a, double b, int n, 
                              double (*f)(double, double) )
{
  double k1, k2, h;
  int i;
  FILE *fout;
  char fname[]="ex12_04.csv";
  
  if((fout=fopen(fname, "w"))==NULL){
	  printf("Cannot open the file; %s\n", fname);
	  exit(1);
  }

  h = 0.025;

  for ( i = 0 ; i < (b-a)/h ; i++)
  {
    k1 = f(x,y); k2 = f(x+h, y+h*k1);
    y = y + h/2.0 * ( k1 + k2 );
    x += h;
	fprintf(fout, "%f,%f,%f,%f \n", x, y, true_f(x), fabs(y-true_f(x)) );
	printf("x=%f \t y=%f ( オイラー) \t y=%f ( 真)　\t %f ( 誤差) \n", x, y, true_f(x), fabs(y-true_f(x)));
  }

}

/* 関数の定義 */
double func(double x, double y)
{
  return( x*x*y );
}

//真の解
double true_f(double x){
	return(1*exp(x*x*x/3));
}
