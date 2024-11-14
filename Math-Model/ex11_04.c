/*
 *ex11_04.c 15822108 情報テクノロジー 堀田大智
 */
#include <stdio.h>
#include <math.h>

/* 関数の定義 */
double func1(double x);

/* 台形公式 */
double trapezoidal( double a, double b, int n, double (*f)(double) );

int main(void)
{
  int n=100;

  printf("2.0*sqrt(1-x*x)を[-1,1]で積分します。分割数は%dです\n", n);
  printf("結果は%20.15fです\n",trapezoidal(-1.0, 1.0, n, func1) );
  
  return 0;
}

/* 台形公式 */
double trapezoidal( double a, double b, int n, double (*f)(double) )
{
  double T, h; 
  int i;
 
  h = ( b - a ) /n ;  /* 刻み幅の指定 */

  /* 台形公式 */
  T = ( (*f)(a) + (*f)(b) ) / 2.0; 
  for ( i = 1; i < n; i++) T += (*f)( a + i*h ); 
  T *= h;

  return T;
}

/* 関数の定義 */
double func1(double x)
{ 
  return( 2.0*sqrt(1-x*x) );
}

