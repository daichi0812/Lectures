#include <stdio.h>
#include <math.h>

/* 2分法 */
double bisection( double a, double b, double eps );
/* 関数の定義 */
double f( double x );

int main(void)
{
  double a, b, x, h, y1, y2, eps = pow(2.0, -30.0);
  int n;
  FILE *fout;
  char fname[] = "output41.csv";

  printf("初期区間[a,b]を入力してください--->a b\n");
  scanf("%lf %lf", &a, &b );
  printf("区間の分割数nを入力してください--->n\n");
  scanf("%d", &n );  

  if((fout = fopen(fname, "w")) == NULL )
  {
		printf("Cannot open file：%s\n", fname);
		return 1;
  }

  /* 対象区間を探索しながら2分法を適用 */
  //さらに対象区間のデータをファイルへ出力(x=aはfor文には含まれないので個別出力)
  fprintf(fout, "%f, %f\n", a,f(a));
  h = (b-a)/n;  y1 = f(a);
  for ( x = a+h ; x <= b ; x += h)
  {
    fprintf(fout, "%f, %f\n", x,f(x));
    y2 = f(x); 
    if ( y1*y2 < 0.0 )  
    {
      printf("求める答えはx=%fです\n", bisection(x-h, x, eps) );
    }
    y1 = y2;
  }

  fclose(fout);

  return 0;
}

/* 2分法 */
double bisection( double a, double b, double eps )
{
  double c;

  do
  {
    c = (a+b)/2.0; 
    if ( f(a)*f(c) < 0 )  
      b = c;
    else 
      a = c; 
  }while( fabs(b-a) >= eps );
  
  c = (a+b)/2.0; 

  return c;
}

/* 関数の定義 */
double f( double x )
{
  return( pow(x,5.0) - 5.0*pow(x,3.0) + 4.0*x );
}

