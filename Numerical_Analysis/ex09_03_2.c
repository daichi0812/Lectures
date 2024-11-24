/*
 *ex09_03_2.c 15822108　情報テクノロジー 堀田大智
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS  pow(10.0, -8.0)      /* epsilonの設定 */
#define KMAX 100                  /* 最大反復回数 */

/* 行列の入力 */ //行列の次数Nを追加
void input_matrix( double **a, char c, FILE *fin, FILE *fout, int N);
/* ベクトルの入力 */ //ベクトルの次数Nを追加
void input_vector( double *b, char c, FILE *fin, FILE *fout, int N);
/* 行列の領域確保 */
double **dmatrix(int nr1, int nr2, int nl1, int nl2);
/* 行列の領域解放 */
void free_dmatrix(double **a, int nr1, int nr2, int nl1, int nl2);
/* ベクトル領域の確保 */
double *dvector(int i, int j);  
/* 領域の解放 */
void free_dvector(double *a, int i); 
/* 比較関数 */
int double_comp( const void *s1 , const void *s2 );
/* 最大値ノルムの計算 a[m...n] */
double vector_norm_max( double *a, int m, int n );
/* ヤコビ法 */ //次数Nを追加
double *jacobi_lin(double **a, double *b, double *x, int N);

int main(void)
{
  FILE *fin, *fout;
  double **a, *b, *x; 
  int i, N;

  /* ファイルのオープン */
  if ( (fin = fopen( "ex09_03_2_input.dat", "r")) == NULL )
  {
      printf("ファイルが見つかりません : ex09_03_2_input.dat \n");
      exit(1);
  }
  if( (fout = fopen( "ex09_03_2_output.dat", "w")) == NULL )
  {
    printf("ファイルが作成できません : ex09_03_2_output.dat \n");
    exit(1);
   }
   
     fscanf(fin, "%d", &N);

  /* 行列およびベクトルの領域確保 */
  a = dmatrix(1, N, 1, N); /* 行列 a[1...N][1...N] */
  b = dvector(1,N); /* b[1...N] */
  x = dvector(1,N); /* x[1...N] */

  input_matrix( a, 'A', fin, fout, N );    /* 行列Aの入出力 */  
  input_vector( b, 'b', fin, fout, N );    /* ベクトルbの入出力 */
  input_vector( x, 'x', fin, fout, N );    /* 初期ベクトルx0の入出力 */
  x = jacobi_lin( a, b, x, N );             /* ヤコビ法 */

  /* 結果の出力 */
  fprintf( fout, "Ax=bの解は次の通りです\n");
  for( i = 1 ; i <= N ; i++)
  {
    fprintf(fout, "%f\n", x[i]);
  }

  fclose(fin); fclose(fout);  /* ファイルのクローズ */

  /* 領域の解放 */
  free_dmatrix( a, 1, N, 1, N ); free_dvector( b, 1 ); free_dvector( x, 1 );

  return 0;
}

double *jacobi_lin(double **a, double *b, double *x, int N)
{
  double eps, *xn; 
  int i, j, k=0; 

  xn = dvector(1,N); /* xn[1...N] */

  /* x <- x_k,  xn <- x_{k+1} */
  do
  { 
    for(i = 1; i <= N; i++)
    {
      xn[i] = b[i]; 
      for ( j = 1; j <= N; j++)
      {
        xn[i] -= a[i][j]*x[j];
      }
      xn[i] += a[i][i]*x[i];    /* 余分に引いた分を加える */
      xn[i] /= a[i][i];  //元に戻す
   }
    for( i = 1; i <= N; i++)  x[i] = xn[i]-x[i];
    eps = vector_norm_max(x, 1, N);
    for( i = 1; i <= N; i++)  x[i] = xn[i]; /* 値を更新 */
    k++;
 }while(eps > EPS && k < KMAX);

  free_dvector( xn, 1 ); /* 領域の解放 */
  if ( k == KMAX )
  {
    printf("答えが見つかりませんでした\n");
    exit(1);
  }
  else
  {
    printf("反復回数は%d回です\n", k); /* 反復回数を画面に表示 */
    return x;
  }
}


/* a[1...N][1...N]の入力 */
void input_matrix( double **a, char c, FILE *fin, FILE *fout, int N)
{
  int i,j;

  fprintf( fout, "行列%cは次の通りです\n", c);
  for( i = 1 ; i <= N ; i++)
  {
    for( j = 1 ; j <= N ; j++)
    {
      fscanf(fin, "%lf", &a[i][j]);
      fprintf(fout, "%5.2f\t", a[i][j]);
    }
    fprintf( fout, "\n");
  }
}

/* b[1...N]の入力 */
void input_vector( double *b, char c, FILE *fin, FILE *fout, int N)
{
  int i;

  fprintf( fout, "ベクトル%cは次の通りです\n", c);
  for( i = 1 ; i <= N ; i++)
  {
    fscanf(fin, "%lf", &b[i]);
    fprintf(fout, "%5.2f\t", b[i]);
    fprintf( fout, "\n");
  }
}


double **dmatrix(int nr1, int nr2, int nl1, int nl2)
{
  int i, nrow, ncol; 
  double **a; 

  nrow = nr2 - nr1 + 1 ; /* 行の数 */
  ncol = nl2 - nl1 + 1 ; /* 列の数 */

  /* 行の確保 */
  if ( ( a=(double **)malloc( nrow*sizeof(double *) ) ) == NULL ) 
  {
    printf("メモリが確保できません(行列a)\n");
    exit(1);
  }
  a = a - nr1; /* 行をずらす */
  /* 列の確保 */
  for( i=nr1; i<=nr2; i++) a[i] = (double *)malloc(ncol*sizeof(double)); 
  for( i=nr1; i<=nr2; i++) a[i] = a[i]-nl1;             /* 列をずらす */
  
  return(a);
}

void free_dmatrix(double **a, int nr1, int nr2, int nl1, int nl2)
{
  int i;

  /* メモリの解放  */
  for ( i = nr1 ; i <= nr2 ; i++) free((void *)(a[i]+nl1));
  free((void *)(a+nr1));
}


double *dvector(int i, int j) /* a[i]〜a[i+j]の領域を確保 */
{
  double *a;

  if ( (a=(double *)malloc( ((j-i+1)*sizeof(double))) ) == NULL )
  {
    printf("メモリが確保できません(from dvector) \n");
    exit(1);
  }  

  return(a-i);
}

void free_dvector(double *a, int i)
{
  free( (void *)(a + i) );  /* (void *)型へのキャストが必要 */
}

/* 最大値ノルムの計算 a[m...n] */
double vector_norm_max( double *a, int m, int n )
{
  int i, tmp;
  tmp = n-m+1 ; /* 全要素数の計算 */

  for ( i = m ; i <= n; i++) a[i] = fabs(a[i]);

  /* 並べ換え:先頭アドレスがmだけずれていることに注意 */
  qsort(a+m, tmp, sizeof(a[0]), double_comp); 

  /*  for(i=m;i<=n;i++) printf("a[%d]=%f\n",i,a[i]);*/

  return a[n];
}


int double_comp( const void *s1 , const void *s2 )
{
  const double a1 = *((double *)s1); /* (double *)へキャスト */
  const double a2 = *((double *)s2); /* (double *)へキャスト */

  if( a1 < a2 )
  {
    return -1;
  } 
  else if( a1 == a2 )
  {
    return 0;
  } 
  else
  {
    return 1;
  }
}
