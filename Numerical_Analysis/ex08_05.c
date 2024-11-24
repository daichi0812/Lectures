/*
 *ex08_05.c 15822108 情報テクノロジー　堀田大智
 */
#include <stdio.h>
#include <math.h>

#define EPS  pow(10.0,-8.0)   /* epsilonの設定 */
#define NMAX 20             /* 最大反復回数 */

void secant( double x0, double x1 );    /* 割線法 */
double f(double x);         /* f(x)の計算 */

int main(void)
{
  double x, x0, x1;
  FILE *fout;
  char fname[]="ex08_05.csv";
  
  if((fout=fopen(fname, "w"))==NULL){
	  printf("Cannot open the file: %s", fname);
	  return 1;
  }
  for(x=-3; x<=3; x+=0.1){
	  fprintf(fout, "%lf,%lf\n", x, f(x));
  }
  fclose(fout);
  
  printf("初期値x0とx1を入力してください\n");
  scanf("%lf %lf", &x0, &x1);

  secant( x0, x1 );
  
  printf("初期値x0とx1を入力してください\n");
  scanf("%lf %lf", &x0, &x1);
  
  secant(x0, x1);
  
  printf("初期値x0とx1を入力してください\n");
  scanf("%lf %lf", &x0, &x1);
  
  secant( x0, x1);

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
  return( x*x*x-2*x*x-2*x+1);
}
