/*
 *ex08_03 15822108　情報テクノロジー 堀田大智
 */
#include <stdio.h>
#include <math.h>

#define EPS  pow(10.0,-8.0)   /* epsilonの設定 */
#define NMAX 100            /* 最大反復回数 */

void newton1( double x );    /* Newton法(重複次数つき) */
double f(double x);         /* f(x)の計算 */
double df(double x);        /* f'(x)の計算 */

int main(void)
{
  double x;
  FILE *fout;
  char fname[]="ex08_03.csv";
  if((fout=fopen(fname, "w"))==NULL){
	  printf("Cannot open the file: %s\n", fname);
	  return 1;
  }
  for(x=-3.0; x<=3.0; x+=0.1){
	  fprintf(fout, "%lf,%lf\n", x, f(x));
  }
  fclose(fout);
  
  printf("初期値x0を入力してください\n");
  scanf("%lf",&x);
  
  newton1( x );
  
  printf("初期値x1を入力してください\n");
  scanf("%lf",&x);

  newton1( x );

  return 0;
}

/* Newton法(重複次数つき) */
void newton1( double x )
{
  int n=0; double d, x0=x, x1=x, x2=x, m; /* xでx0,x1,x2を初期化 */

  do
  {
    d = -f(x)/df(x);
    x = x + d;
    n ++;
    x0 = x1; x1 = x2; x2 = x; 
  }while( fabs(d) > EPS && n < NMAX);

  m = (x0 - x1)/(x0 - 2.0*x1 + x2) ; /* 重複次数の計算 */
  if ( n == NMAX )
  {
    printf("答えが見つかりませんでした\n");
  }
  else
  {
    printf("答えはx=%fで,重複次数は%fです\n",x, m);
  }

}

/* 関数の定義 */
double f(double x)
{
  return( x*x*x - 3.0*x  - 2.0 );
}

/* 導関数の定義 */
double df(double x)
{
  return( 3.0*x*x - 3.0 );
}


