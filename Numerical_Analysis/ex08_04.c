/*
 *ex08_04.c 15822108 情報テクノロジー　堀田大智
 */
#include <stdio.h>
#include <math.h>

#define EPS  pow(10.0,-8.0)   /* epsilonの設定 */
#define NMAX 20             /* 最大反復回数 */

void secant( double x0, double x1 );    /* 割線法 */
double f(double x);         /* f(x)の計算 */

int main(void)
{
  double x0;
  FILE *fout;
  char fname[]="ex08_04.csv";
  
  if((fout=fopen(fname, "w"))==NULL){
	  printf("Cannot open the file: %s\n", fname);
	  return 1;
  }
  for(x0=-6.0; x0<=6.0; x0+=0.1){
	  fprintf(fout, "%lf,%lf\n", x0, f(x0));
  }
  fclose(fout);
  
 

  

  return 0;
}

/* 割線法 */
void secant( double x0, double x1 )
{
  int n=1; double d=x1-x0, y0=f(x0), y1;

  do
  {
    y1 = f(x1);
    d = -d * y1 / (y1 - y0);
    x1 = x1 + d;
    y0 = y1; 
    n ++;
  }while( fabs(d) > EPS && n < NMAX);

  if ( n == NMAX )
  {
    printf("答えが見つかりませんでした\n");
  }
  else
  {
    printf("答えはx=%fです\n",x1);
  }

}

double f(double x)
{
  return( x-cos(x) );
}
