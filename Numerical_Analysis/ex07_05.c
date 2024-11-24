#include <stdio.h>
#include <math.h>

#define EPS  pow(10.0,-8.0)   /* epsilonの設定 */
#define NMAX 200             /* 最大反復回数 */

void newton( double x );    /* Newton法 */
double f(double x);         /* f(x)の計算 */
double df(double x);        /* f'(x)の計算 */

int main(void)
{
  double x;
  printf("初期値x0を入力してください\n");
  scanf("%lf",&x);

  newton( x );

  return 0;
}

/* Newton法 */
void newton( double x )
{
  int n=0; double d;
  FILE *fout;
  char fname[] = "ex07_05.csv";

  if((fout = fopen(fname, "w")) == NULL )
  {
		printf("Cannot open file：%s\n", fname);
  }

  do
  {
    fprintf(fout, "%f, %f\n", x, f(x));
    d = -f(x)/df(x);
    x = x + d;
    n ++;
  }while( fabs(d) > EPS && n < NMAX);

  fclose(fout);

  if ( n == NMAX )
  {
    printf("答えが見つかりませんでした\n");
  }
  else
  {
    printf("答えはx=%fです\n",x);
  }

}

double f(double x)
{
  return( exp(-x)-x );
}

double df(double x)
{
  return( -exp(-x)-1 );
}
