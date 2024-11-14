/*
 *ex12_06.c 15822108 情報テクノロジー 堀田大智
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double *dvector(long i, long j);      /* ベクトル領域の確保 */
void free_dvector(double *a, long i); /* 領域の解放 */
double func(double x, double y);      /* 関数の定義 */
/* ルンゲ・クッタ法 */
double *rk4( double y0, double *y, double a, double b, int n, 
                                   double (*f)(double, double) );
//真の解
double true_f(double x);

int main(void)
{
  double *y, h, a=0.0, b=1.0, y0=1.0 ;
  int i, n;
  FILE *fout;
  char fname[]="ex12_06.csv";
  
  if((fout=fopen(fname, "w"))==NULL){
	  printf("Cannot open the file: %s\n", fname);
	  exit(1);
  }

  printf("分割数を入力してください--->");
  scanf("%d",&n);

  h = 0.025;             /* 刻み幅 */
  
  y = dvector( 0, (b-a)/h );                /* 領域の確保 */
  y = rk4( y0, y, a, b, (b-a)/h, func );  /* ルンゲ・クッタ法 */
  
  //結果の表示
  for ( i = 0 ; i <= (b-a)/h ; i++)
  {
    printf("x=%lf \t y=%lf ( ルンゲ・クッタ法) \t y=%lf ( 真) \t %lf ( 誤差) \n", a+i*h, y[i], true_f(a+i*h), fabs(y[i]-true_f(a+i*h)));
	fprintf(fout, "%lf, %lf, %lf, %lf\n", a+i*h, y[i], true_f(a+i*h), fabs(y[i]-true_f(a+i*h)));
  }

  free_dvector( y, 0 ); /* 領域の解放 */
  return 0;
}

/* ルンゲ・クッタ法 */
double *rk4( double y0, double *y, double a, double b, int n, 
                                   double (*f)(double, double) )
{
  double k1, k2, k3, k4, h, x;
  int i;

  h = 0.025;
  /* 初期値の設定 */
  y[0] = y0; x = a;    

  /* ルンゲ・クッタ法 */
  for ( i = 0 ; i < (b-a)/h ; i++)
  {
    k1 = f(x,y[i]); k2 = f(x+h/2.0, y[i]+h*k1/2.0);
    k3 = f(x+h/2.0, y[i]+h*k2/2.0);
    k4 = f(x+h, y[i]+h*k3);
    y[i+1] = y[i] + h/6.0 * ( k1 + 2.0*k2 + 2.0*k3 + k4 );
    x += h;
  }

  return y;
}

/* 関数の定義 */
double func(double x, double y)
{
  return( x*x*y );
}

//真の解
double true_f(double x){
	return (1*exp(x*x*x/3));
}

double *dvector(long i, long j) /* a[i]〜a[i+j]の領域を確保 */
{
  double *a;

  if ( (a=(double *)malloc( ((j-i+1)*sizeof(double))) ) == NULL )
  {
    printf("メモリが確保できません(from dvector) \n");
    exit(1);
  }  

  return(a-i);
}

void free_dvector(double *a, long i)
{
  free( (void *)(a + i) );  /* (void *)型へのキャストが必要 */
}

